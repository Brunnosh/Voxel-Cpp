#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <glad/glad.h>
#include <string>
#include <hash.hpp>


enum FACE { //order used for texture index in chunk.cpp/block.cpp
    NORTH,
    SOUTH,
    EAST,
    WEST,
    TOP,
    BOTTOM
};

// Vertex format (exemplo simplificado)
struct Vertex
{
    char X, Y, Z;
    float uvX, uvY;


    Vertex(char _posX, char _posY, char _posZ, float _texGridX, float _texGridY)
        :X(_posX), Y(_posY), Z(_posZ),

        uvX(_texGridX), uvY(_texGridY){}
};

// Mesh de um chunk
struct Mesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    bool uploaded = false;
};

class Renderer {
public:
    void createWorldMesh();
    void drawMesh(glm::ivec3& pos);
    void uploadMesh(const glm::ivec3& pos);
    void renderAll();
    void cleanup();

private:
    std::unordered_map<glm::ivec3, Mesh, Vec3Hash> chunkMeshes;

    void Renderer::setVertex(uint8_t x, uint8_t y, uint8_t z, FACE face, Mesh& mesh, unsigned int& currentVertex);
    void uploadMesh(Mesh& mesh);
};
