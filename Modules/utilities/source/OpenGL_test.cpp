#include <thread>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std::chrono_literals;

int window_height = 800;
int window_width = 600;

void addWindow() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(window_height, window_width, "World Viewer", NULL, NULL); // use glfwGetPrimaryMonitor() to obtain full screen
    if (window == NULL)
    {
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {

    }

    glViewport(0, 0, window_height, window_width);

    //getOpenGLInfo();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        std::this_thread::sleep_for(10ms);

        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(window);
    window = NULL;
}

int main(int argc, char* argv[]) {

	int initResult = glfwInit();
	//initialize window
	if (initResult == GLFW_FALSE) {
		//throw WindowGenerationException();
	}




    std::thread viewerThread([]() {
        addWindow();
    });
    viewerThread.detach();

    std::this_thread::sleep_for(10000ms);
    
    std::thread viewerThread2([]() {
        addWindow();
    });
    viewerThread2.detach();

    std::this_thread::sleep_for(10000ms);


	glfwTerminate();
}