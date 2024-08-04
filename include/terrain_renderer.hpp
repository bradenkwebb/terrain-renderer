#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"

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
        Shader shader = Shader("src/terrain_shader.vs", "src/terrain_shader.fs");
        TerrainRenderer();
        TerrainRenderer(std::string heightMapPath);
        ~TerrainRenderer();
        void loadHeightMap();
        void loadHeightMap(std::string const& heightMapPath);
        void createMesh();
        void render();
};