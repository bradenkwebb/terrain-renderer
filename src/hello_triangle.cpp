#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "hello_triangle.h"
#include "shader.h"

void helloTriangle(GLFWwindow* window) {

    Shader shader("src/triangle_shader.vs", "src/triangle_shader.fs");
    
    // triangle
    float vertices[] = {
        // positions            //colors
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    // left
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,    // right
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f    // top
    };

    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); // create 1 vertex array object
    glGenBuffers(1, &VBO); // create 1 vertex buffer object

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Now that the data and attributes have been bound to the VAO, we can unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        // glUseProgram(shaderProgram);
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);
}