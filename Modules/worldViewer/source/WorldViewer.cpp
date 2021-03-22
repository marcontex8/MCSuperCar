#include "worldViewer.h"

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

#include "Scene.h"
#include "Factory_SimpleElements.h"
#include "Factory_CarPack001.h"
#include "Diagnostics.h"

#include <chrono>

extern Diagnostics diagnostics;

WorldViewer::WorldViewer(std::atomic<bool>* terminationFlag, simulation::SimulatedWorld* world): terminationFlag(terminationFlag), world(world), window(nullptr) {
    diagnostics.log("WorldViewer | constructor called", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
}


WorldViewer::~WorldViewer(){
    diagnostics.log("WorldViewer | destructor called", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);

}

void WorldViewer::runView() {
    diagnostics.log("WorldViewer | runView called", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
    using namespace std::chrono_literals;
    setupWindow();
    //getOpenGLInfo();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Scene scene(window_height, window_width);
    scene.setFOV(90.0);
    scene.setLightPosition(glm::vec3(0.0, 0.0, 100.0));
    scene.setLightColor(glm::vec3(1.0, 1.0, 1.0));
    SimpleElementsFactory simpleElementsFactory;
    CarPack001Factory carPack001Factory;

    SimpleTerrainDrawer* terrain = simpleElementsFactory.newSimpleTerrainDrawer();
    std::vector<Drawer*> elementsDrawer;
    while (!glfwWindowShouldClose(window) && !(*terminationFlag))
    {
        std::this_thread::sleep_for(10ms);
        
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()/10) * radius;
        float camY = cos(glfwGetTime()/10) * radius;
        scene.setCameraPosition(glm::vec3(camX, camY, 10.0f));


        static int i = 0;
        diagnostics.monitor("VIEWER LOOP \t", std::to_string( i++));

        processInput();
        // refresh background
        //glClearColor(0.2f, 0.53f, 0.3f, 1.0f);
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::quat rotation = { 1,0,0,0 };
        //diagnostics.log("rotation:" + std::to_string(rotation.x) + " - " + std::to_string(rotation.y) + " - " + std::to_string(rotation.z) + " - " + std::to_string(rotation.w), Diagnostics::Topic::Viewer);
        terrain->draw(glm::vec3(0,0,0), rotation, scene);

        world->applyToElements(
            [&carPack001Factory, &simpleElementsFactory, &elementsDrawer, &scene](simulation::SimulationElement* element) {
                if (element == nullptr) {
                    diagnostics.log("This element is nullptr", Diagnostics::Topic::Viewer);
                    return;
                }
                Drawer* currentElement = nullptr;
                if (element->id >= elementsDrawer.size()) {
                    currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::SUV, carPack001::Color::Red);
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
                /*std::cout << "x: " << element->getPosition()[0]
                    << "y: " << element->getPosition()[1]
                    << "z: " << element->getPosition()[2]
                    << std::endl;
                */
                glm::vec3 position = glm::vec3(element->getPosition()[0], element->getPosition()[1], element->getPosition()[2]);
                glm::dquat orientation = { element->getOrientation().w(), element->getOrientation().x(), element->getOrientation().y(), element->getOrientation().z() };
                //diagnostics.monitor("element rotation:", std::to_string(orientation.x) + " - " + std::to_string(orientation.y) + " - " + std::to_string(orientation.z) + " - " + std::to_string(orientation.w));
                currentElement->draw(position, orientation, scene);
                
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

    glfwWindowHint(GLFW_SAMPLES, 4);
    this->window = glfwCreateWindow(1200, 1200, "World Viewer", NULL, NULL);
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