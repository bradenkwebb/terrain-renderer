#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "terrain_renderer.hpp"
#include "hello_triangle.hpp"
#include "camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

float currentFrame;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera* camera = new Camera();

int main(int argc, char* argv[]) {
    std::cout << "Number of arguments: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "\tArgument " << i << ": " <<argv[i] << std::endl;
    }

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "tutorial") == 0) {
        helloTriangle(window, camera, processInput);
    } else if (strcmp(argv[1], "terrain") == 0) {
        ///////////////////////////////////////////////////////////////////////
        // BEGINNING TERRAIN RENDERER STUFF BELOW
        ///////////////////////////////////////////////////////////////////////
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // this enables wireframe mode

        TerrainRenderer terrain = TerrainRenderer();
        terrain.loadHeightMap("assets/iceland_heightmap.png");
        terrain.createMesh();
        // terrain.createAndCompileShaders();

        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            glfwPollEvents();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            terrain.render();

            glfwSwapBuffers(window);   
        }
    } else {
        std::cout << "Pass either \"tutorial\" or \"terrain\" as argument" << std::endl;
    }
    
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window) {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->processKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->processKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->processKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->processKeyboard(BACKWARD, deltaTime);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.3f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->processMouseMovement(xoffset, yoffset);
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->processMouseScroll(xoffset, yoffset);
}