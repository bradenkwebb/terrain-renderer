#include "terrain_renderer.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "shader.hpp"

TerrainRenderer::TerrainRenderer() {
    hasPath = false;
}

TerrainRenderer::TerrainRenderer(std::string heightMapPath) {
    this->heightMapPath = heightMapPath;
    hasPath = true;
};

TerrainRenderer::~TerrainRenderer() {
    if (heightMap) {
        delete[] heightMap;
    }
}

void TerrainRenderer::loadHeightMap(std::string const& heightMapPath) {
    int width, height, nrChannels;
    
    unsigned char* data = stbi_load(heightMapPath.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cout << "Failed to load height map" << std::endl;
        throw "Failed to load height map";
    }
    float* heightMap = new float[width*height];
    for (int i = 0; i < width * height; i++) {
        heightMap[i] = data[i] / 255.0f;
    }
    stbi_image_free(data);

    std::cout << "Height map loaded successfully! Height: " << height << " Width: " << width << std::endl;

    this->heightMapPath = heightMapPath;
    this->heightMap = heightMap;
    hasPath = true;
    terHeight = height;
    terWidth = width;
    return;
};

void TerrainRenderer::loadHeightMap() {
    if (!hasPath) {
        throw "The heightMapPath must be provided either at object initilization, or as an argument.";
    } else {
        loadHeightMap(heightMapPath);
    }
    return;
}

void TerrainRenderer::createMesh() {
    for (unsigned int y = 0; y < terHeight; y++) {
        for (unsigned int x = 0; x < terWidth; x++) {
            terMeshVertices.push_back((float)x / (terWidth - 1)); // x-coordinate
            terMeshVertices.push_back(heightMap[terWidth * y + x]); // height, or y-coordinate
            terMeshVertices.push_back((float)y / (terHeight - 1));
        }
    }
    std::cout << "There are " << terMeshVertices.size() << " vertices." << std::endl;

    for (unsigned int y = 0; y < terHeight - 1; y++) {
        for (unsigned int x = 0; x < terWidth - 1; x++) {
            // Indices of the 4 vertices defining a grid cell
            // We should have two triangles for each square cell
            unsigned int topLeft = y * terWidth + x;
            unsigned int topRight = y * terWidth + x + 1;
            unsigned int bottomLeft = (y + 1) * terWidth + x;
            unsigned int bottomRight = (y + 1) * terWidth + x + 1;

            // Triangle 1 vertices
            terMeshIndices.push_back(topLeft);
            terMeshIndices.push_back(bottomLeft);
            terMeshIndices.push_back(topRight);

            // Triangle 2 vertices
            terMeshIndices.push_back(topRight);
            terMeshIndices.push_back(bottomLeft);
            terMeshIndices.push_back(bottomRight);
        }
    }
    std::cout << "There are " << terMeshIndices.size() << " triangle indices." << std::endl;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, terMeshVertices.size() * sizeof(float), &terMeshVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terMeshIndices.size() * sizeof(unsigned int), &terMeshIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return;
}

void TerrainRenderer::render() {
    glUseProgram(shaderProgram);
    // Set up model, view and projection matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Target position
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
    );
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    // Get location of the uniform variables in the shader program
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Set the uniform variables in the shader program
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Bind the VAO and draw the elements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, terMeshIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}