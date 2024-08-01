#pragma once

#include <vector>
#include <string>

#ifndef TERRAIN_RENDER_H
#define TERRAIN_RENDER_H

class TerrainRenderer {
    private:
        bool hasPath;
        std::string heightMapPath;
        std::vector<float> terMeshVertices;
        std::vector<unsigned int> terMeshIndices;
        unsigned int terHeight;
        unsigned int terWidth;
        float* heightMap;

    public:
        TerrainRenderer();
        TerrainRenderer(std::string heightMapPath);
        void loadHeightMap();
        void loadHeightMap(std::string const& heightMapPath);
        void createMesh();
        
};

#endif