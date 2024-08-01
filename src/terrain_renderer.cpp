#include "terrain_renderer.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TerrainRenderer::TerrainRenderer() {
    this->hasPath = false;
}

TerrainRenderer::TerrainRenderer(std::string heightMapPath) {
    this->heightMapPath = heightMapPath;
    this->hasPath = true;
};

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

    this->heightMapPath = heightMapPath;
    this->hasPath = true;
    this->terHeight = height;
    this->terWidth = width;
    this->heightMap = heightMap;
    return;
};

void TerrainRenderer::loadHeightMap() {
    if (!this->hasPath) {
        throw "The heightMapPath must be provided either at object initilization, or as an argument.";
    } else {
        this->loadHeightMap(this->heightMapPath);
    }
    return;
}

void TerrainRenderer::createMesh() {
    for (unsigned int y = 0; y < this->terHeight; y++) {
        for (unsigned int x = 0; x < this->terWidth; x++) {
            this->terMeshVertices.push_back((float)x / (this->terWidth - 1)); // x-coordinate
            this->terMeshVertices.push_back(heightMap[this->terWidth * y + x]); // height, or y-coordinate
            this->terMeshVertices.push_back((float)y / (this->terHeight - 1));
        }
    }
    std::cout << "There are " << this->terMeshVertices.size() << " vertices." << std::endl;

    for (unsigned int y = 0; y < this->terHeight - 1; y++) {
        for (unsigned int x = 0; x < this->terWidth - 1; x++) {
            // Indices of the 4 vertices defining a grid cell
            // We should have two triangles for each square cell
            unsigned int topLeft = y * this->terWidth + x;
            unsigned int topRight = y * this->terWidth + x + 1;
            unsigned int bottomLeft = (y + 1) * this->terWidth + x;
            unsigned int bottomRight = (y + 1) * this->terWidth + x + 1;

            // Triangle 1 vertices
            this->terMeshIndices.push_back(topLeft);
            this->terMeshIndices.push_back(bottomLeft);
            this->terMeshIndices.push_back(topRight);

            // Triangle 2 vertices
            this->terMeshIndices.push_back(topRight);
            this->terMeshIndices.push_back(bottomLeft);
            this->terMeshIndices.push_back(bottomRight);
        }
    }
    std::cout << "There are " << this->terMeshIndices.size() << " triangle indices." << std::endl;
    return;
}