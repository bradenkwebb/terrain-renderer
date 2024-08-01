#pragma once
#ifndef TERRAIN_RENDER_H
#define TERRAIN_RENDER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TerrainRenderer {
    private:
        bool hasPath;
        std::string heightMapPath;
        std::vector<float> terMeshVertices;
        std::vector<unsigned int> terMeshIndices;
        unsigned int terHeight;
        unsigned int terWidth;
        float* heightMap;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        unsigned int shaderProgram;

    public:
        TerrainRenderer();
        TerrainRenderer(std::string heightMapPath);
        ~TerrainRenderer();
        void loadHeightMap();
        void loadHeightMap(std::string const& heightMapPath);
        void createMesh();
        void createAndCompileShaders();
        void render();

        unsigned int compileShader(unsigned int type, const char* source);
        unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

#endif