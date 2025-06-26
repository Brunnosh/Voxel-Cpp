#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <glad/glad.h>
#include <string>

struct Vec3Hash {
    std::size_t operator()(const glm::ivec3& v) const {
        std::size_t h1 = std::hash<int>()(v.x);
        std::size_t h2 = std::hash<int>()(v.y);
        std::size_t h3 = std::hash<int>()(v.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2); 
    }
};

// Vertex format (exemplo simplificado)
struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
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
    void createMesh(const glm::ivec3& pos, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void uploadMesh(const glm::ivec3& pos);
    void renderMesh(GLuint modelLoc);
    void cleanup();

private:
    std::unordered_map<glm::ivec3, Mesh, Vec3Hash> chunkMeshes;

    void setupMesh(Mesh& mesh);
};
