#include "worldViewer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include<map>

// Used to correctly include STB image library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Scene.h"
#include "Factory_SimpleElements.h"
#include "Factory_CarPack001.h"
#include "Diagnostics.h"


#include "SimulationElement_Car.h"


extern Diagnostics diagnostics;

WorldViewer::WorldViewer(std::atomic<bool>* terminationFlag, std::shared_ptr<simulation::SimulatedWorld>& world): terminationFlag(terminationFlag), world(world), window(nullptr) {
    diagnostics.log("WorldViewer | constructor called", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
}


WorldViewer::~WorldViewer(){
    diagnostics.log("WorldViewer | destructor called", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);

}

void WorldViewer::runView() {
    diagnostics.log("WorldViewer | runView called", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
    using namespace std::chrono_literals;
    try {
        setupWindow();
    }
    catch (std::exception e) {
        diagnostics.log("Error while setting up window. Terminating runView()", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        return;
    }
    //getOpenGLInfo();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Scene scene((float)window_height, (float)window_width);
    scene.setFOV(90.0);
    scene.setLightPosition(glm::vec3(0.0, 0.0, 100.0));
    scene.setLightColor(glm::vec3(1.0, 1.0, 1.0));
    Shaders shaders;
    SimpleElementsFactory simpleElementsFactory(&shaders);
    CarPack001Factory carPack001Factory(&shaders);

    SimpleTerrainDrawer* terrain = simpleElementsFactory.newSimpleTerrainDrawer();
    std::vector<Drawer*> elementsDrawer;
    while (!glfwWindowShouldClose(window) && !(*terminationFlag))
    {
        std::this_thread::sleep_for(10ms);
        
        const float radius = 10.0f;
        double camX = sin(glfwGetTime()/10) * radius;
        double camY = cos(glfwGetTime()/10) * radius;
        scene.setCameraPosition(glm::vec3(camX, camY, 10.0f));

        int errorCode = glfwGetError(nullptr);
        diagnostics.monitor("glfw error code \t", std::to_string(errorCode));

        /*
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == NULL) {
            diagnostics.monitor("glfw current contex window \t", std::string("is null!"));
        } 
        else {
            diagnostics.monitor("glfw current contex window \t", std::string("OK"));
        }
        */
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
        //diagnostics.log("New Drawing cycle", Diagnostics::Topic::Viewer);
        
        world->applyToElements(
            [&carPack001Factory, &simpleElementsFactory, &elementsDrawer, &scene](simulation::SimulationElement* element) {
                if (element == nullptr) {
                    diagnostics.log("This element is nullptr", Diagnostics::Topic::Viewer);
                    return;
                }
                Drawer* currentElement = nullptr;
                if (element->id >= elementsDrawer.size()) {
                    //diagnostics.log("element id: " + std::to_string(element->id) + " >= elementDrawer.size(): " + std::to_string(elementsDrawer.size()), Diagnostics::Topic::Viewer);
                    if (typeid(*element) == typeid(simulation::SimulationElement_Car)) {
                        simulation::SimulationElement_Car* element_casted = dynamic_cast<simulation::SimulationElement_Car*>(element);
                        try {
                            switch (element_casted->model) {
                            case simulation::CarModels::SUV:
                                currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::SUV, carPack001::Color::Red);
                                break;
                            case simulation::CarModels::Hatchback:
                                currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::Hatchback, carPack001::Color::Blue);
                                break;
                            case simulation::CarModels::Minivan:
                                currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::Minivan, carPack001::Color::White);
                                break;
                            case simulation::CarModels::Sport:
                                currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::Sport, carPack001::Color::Yellow);
                                break;
                            default:
                                currentElement = carPack001Factory.getNewSimpleCarDrawer(carPack001::Model::Compact, carPack001::Color::Black);
                            }
                        }
                        catch (carPack001::LoadingElementException e) {
                            diagnostics.log("Something went wrong with generation of simple car.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
                            elementsDrawer.insert(elementsDrawer.begin() + element->id, nullptr);
                            return;
                        }
                    }
                    else {
                        currentElement = simpleElementsFactory.newBoxDrawer();
                    }
                    elementsDrawer.insert(elementsDrawer.begin() + element->id, currentElement);
                    diagnostics.log("Added new element to elementsDrawer",Diagnostics::Topic::Viewer);
                }
                else
                {
                    currentElement = elementsDrawer[element->id];
                    if (currentElement == nullptr) {
                        // This can happen if there was a problem with the instantiation of a drawer. In this case it is necessary to avoid the call to drwa().
                        return;
                    }
                }

                auto elementPosition = element->getPosition();
                auto elementOrientation = element->getOrientation();
                glm::vec3 position = glm::vec3(elementPosition[0], elementPosition[1], elementPosition[2]);
                glm::dquat orientation = { elementOrientation.w(), elementOrientation.x(), elementOrientation.y(), elementOrientation.z() };
                //diagnostics.log("drawing element id "+std::to_string(element->id), Diagnostics::Topic::Viewer);
                currentElement->draw(position, orientation, scene);
                
            }
        );
        diagnostics.monitor("elementsDrawer.size(): ", std::to_string(elementsDrawer.size()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(window);
    window = NULL;
}

void WorldViewer::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void WorldViewer::setupWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);
     
    this->window = glfwCreateWindow(window_height, window_width, "World Viewer", NULL, NULL); // use glfwGetPrimaryMonitor() to obtain full screen
    if (window == NULL)
    {
        diagnostics.log("Failed to create GLFW window.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        throw WindowGenerationException();
    }
    diagnostics.log("GLFW window created.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height);});

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        diagnostics.log("Failed to initialize GLAD.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        throw GladInitializationException();
    }
    diagnostics.log("Glad correctly initialized.", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);

    glViewport(0,0, window_height, window_width);
}


void WorldViewer::getOpenGLInfo() {
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}