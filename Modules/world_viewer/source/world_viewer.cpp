#include "world_viewer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


// Used to correctly include STB image library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<map>

WorldViewer::WorldViewer(simulation::SimulatedWorld* world):world(world), window(nullptr) {
    std::cout << "WorldViewer | constructor" << std::endl;
}


WorldViewer::~WorldViewer(){
}

void WorldViewer::operator()() {
    std::cout << "WorldViewer | operator()" << std::endl;
    setupWindow();
    //getOpenGLInfo();

    ElementOpenGLDefinitions* openglElements = new ElementOpenGLDefinitions();

    glEnable(GL_DEPTH_TEST);
    
    // define camera position
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // define camera projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //std::map<int, ElementDrawer*> elementsDrawer;
    std::vector<ElementDrawer*> elementsDrawer;
    while (!glfwWindowShouldClose(window))
    {
        static int i = 0;
        std::cout << "running loop " << i++ << std::endl;

        processInput();

        // refresh background
        glClearColor(0.2f, 0.53f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world->applyToElements(
            [openglElements, &elementsDrawer, &view, &projection](simulation::SimulationElement* element) {
                if (element == nullptr) {
                    std::cout << "this element is nullptr" << std::endl;
                    return;
                }
                std::cout << "elementsDrawer.size() = " << elementsDrawer.size() << std::endl;
                std::cout << "element->id = " << element->id << std::endl;

                ElementDrawer* currentElement = nullptr;
                if (element->id >= elementsDrawer.size()) {
                    currentElement = new ElementDrawer(openglElements);
                    elementsDrawer.insert(elementsDrawer.begin() + element->id, currentElement);
                    std::cout << "added new element to elementsDrawer" << std::endl;
                }
                else
                {
                    currentElement = elementsDrawer[element->id];
                    if (currentElement == nullptr) {
                        std::cout << "Questo non dovrebbe succedere" << std::endl;
                        return;
                    }
                }
                // define object position
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(element->getPosition()[0], element->getPosition()[1], element->getPosition()[2]));
                std::cout << "x: " << element->getPosition()[0]
                    << "y: " << element->getPosition()[1]
                    << "z: " << element->getPosition()[2]
                    << std::endl;

                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));

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