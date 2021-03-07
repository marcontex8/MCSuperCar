#include "world_viewer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


// Used to correctly include STB image library
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<map>

#include "DrawersFactory.h"
#include "AssimpFactory.h"
#include "Diagnostics.h"

#include <chrono>

extern Diagnostics diagnostics;

WorldViewer::WorldViewer(std::atomic<bool>* terminationFlag, simulation::SimulatedWorld* world): terminationFlag(terminationFlag), world(world), window(nullptr) {
    diagnostics.log("WorldViewer | constructor", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
    std::cout << "WorldViewer | constructor" << std::endl;
}


WorldViewer::~WorldViewer(){
    std::cout << "WorldViewer | destructor" << std::endl;
}

void WorldViewer::runView() {
    std::cout << "WorldViewer | operator()" << std::endl;
    diagnostics.log("WorldViewer | operator()", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
    using namespace std::chrono_literals;
    setupWindow();
    //getOpenGLInfo();


    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // define camera position
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // define camera projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    DrawersFactory drawersFactory;
    AssimpFactory assimpFactory;

    SimpleScenarioDrawer* scenario = drawersFactory.newSimpleScenarioDrawer();
    std::vector<ElementDrawer*> elementsDrawer;
    while (!glfwWindowShouldClose(window) && !(*terminationFlag))
    {
        std::this_thread::sleep_for(10ms);

        static int i = 0;
        diagnostics.monitor("VIEWER LOOP \t", std::to_string( i++));

        processInput();
        // refresh background
        //glClearColor(0.2f, 0.53f, 0.3f, 1.0f);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

        //scenario->draw(model, view, projection);

        world->applyToElements(
            [&assimpFactory, &drawersFactory, &elementsDrawer, &view, &projection](simulation::SimulationElement* element) {
                if (element == nullptr) {
                    diagnostics.log("This element is nullptr", Diagnostics::Topic::Viewer);
                    return;
                }
                ElementDrawer* currentElement = nullptr;
                if (element->id >= elementsDrawer.size()) {
                    currentElement = assimpFactory.getNewSimpleCarDrawer();
                    //currentElement = drawersFactory.newBoxDrawer();
                    elementsDrawer.insert(elementsDrawer.begin() + element->id, currentElement);
                    diagnostics.log("Added new element to elementsDrawer",Diagnostics::Topic::Viewer);
                }
                else
                {
                    currentElement = elementsDrawer[element->id];
                    if (currentElement == nullptr) {
                        diagnostics.log("This shoud not happen!!", Diagnostics::Topic::Viewer,Diagnostics::Verbosity::Error);
                        return;
                    }
                }
                // define object position
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(element->getPosition()[0], element->getPosition()[1], element->getPosition()[2]));
                /*std::cout << "x: " << element->getPosition()[0]
                    << "y: " << element->getPosition()[1]
                    << "z: " << element->getPosition()[2]
                    << std::endl;
                */
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(0.0001f, 0.0001f, 0.0001f));

                currentElement->draw(model, view, projection);
                
            }
        );
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void WorldViewer::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int WorldViewer::setupWindow() {
    //initialize window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->window = glfwCreateWindow(800, 600, "World Viewer", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height);});


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cerr << "GLAD initialized" << std::endl;

    return 0;
}


void WorldViewer::getOpenGLInfo() {
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}