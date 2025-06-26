#include <renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Renderer::createMesh(const glm::ivec3& pos, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    Mesh& mesh = chunkMeshes[pos];
    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.uploaded = false;
}

void Renderer::uploadMesh(const glm::ivec3& pos) {
    auto it = chunkMeshes.find(pos);
    if (it == chunkMeshes.end()) return;

    setupMesh(it->second);
}

void Renderer::setupMesh(Mesh& mesh) {
    if (mesh.uploaded) return;

    if (mesh.VAO == 0) glGenVertexArrays(1, &mesh.VAO);
    if (mesh.VBO == 0) glGenBuffers(1, &mesh.VBO);
    if (mesh.EBO == 0) glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    mesh.uploaded = true;
}

void Renderer::renderMesh(GLuint modelLoc) {
    for (const auto& [pos, mesh] : chunkMeshes) {
        if (!mesh.uploaded) continue;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos * 31)); // CHUNKSIZE = 31
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

void Renderer::cleanup() {
    for (auto& [_, mesh] : chunkMeshes) {
        glDeleteBuffers(1, &mesh.VBO);
        glDeleteBuffers(1, &mesh.EBO);
        glDeleteVertexArrays(1, &mesh.VAO);
    }
    chunkMeshes.clear();
}
