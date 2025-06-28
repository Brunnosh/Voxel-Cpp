#include <renderer.hpp>
#include <configs.hpp>
#include <shader.hpp>
#include <appContext.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Renderer::createWorldMesh() {
    //check camera position and render distance, go through world data and create mesh for all chunks around camera.
    //first check if mesh already exists, if it exists, check if it needs to be redone.
    //call drawMesh for each chunk coordinate, passing chunk blockData.
}

void Renderer::drawMesh(glm::ivec3 & pos ) {

    Mesh mesh;


    unsigned int currentVertex = 0;
    for (uint8_t x = 0; x < CHUNKSIZE; ++x){
        for (uint8_t y = 0; y < CHUNKSIZE; ++y) {
            for (uint8_t z = 0; z < CHUNKSIZE; ++z) {
                //Block& storedBlock = chunk.getBlock(x, y, z);
                //if (storedBlock.getType() == BlockType::AIR) continue;

                //future checks for water blocks, transparent blocks (ADD TO renderData as "WaterVertices" or "Transparentvertices idk"

                for (int f = 0; f < 6; ++f) {
                    //if (shouldRenderFace(chunk.worldPos, x, y, z, FACE(f))) {setVertex(x, y, z, storedBlock, FACE(f), renderData, currentVertex);}
                    setVertex(x, y, z, FACE(f), mesh, currentVertex);
                }
            }
        }

    }
    chunkMeshes[pos] = mesh;
}

void Renderer::setVertex(uint8_t x, uint8_t y, uint8_t z, FACE face, Mesh& mesh, unsigned int& currentVertex) {

    switch (face) {
    case FACE::NORTH:

        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 0, 0, 0));

        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 1);
        currentVertex += 4;
        break;
    case FACE::SOUTH:
        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 1, 0, 0));
        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 0);
        currentVertex += 4;
        break;
    case FACE::EAST:
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 0, 0, 0));

        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 1);
        currentVertex += 4;
        break;
    case FACE::WEST:
        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 0, 0, 0));

        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 0);
        currentVertex += 4;
        break;
    case FACE::TOP:
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 1, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 1, z + 1, 0, 0));

        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 3);
        currentVertex += 4;
        break;
    case FACE::BOTTOM:
        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 0, 0, 0));
        mesh.vertices.push_back(Vertex(x + 1, y + 0, z + 1, 0, 0));
        mesh.vertices.push_back(Vertex(x + 0, y + 0, z + 1, 0, 0));

        mesh.indices.push_back(currentVertex + 0);
        mesh.indices.push_back(currentVertex + 1);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 2);
        mesh.indices.push_back(currentVertex + 3);
        mesh.indices.push_back(currentVertex + 0);
        currentVertex += 4;
        break;
    }
}

void Renderer::uploadMesh(const glm::ivec3& pos) {
    auto it = chunkMeshes.find(pos);
    if (it == chunkMeshes.end()) return;

    uploadMesh(it->second);
}

void Renderer::uploadMesh(Mesh& mesh) {
    if (mesh.uploaded) return;

    if (mesh.VAO == 0) glGenVertexArrays(1, &mesh.VAO);
    if (mesh.VBO == 0) glGenBuffers(1, &mesh.VBO);
    if (mesh.EBO == 0) glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    // Position attribute: chars interpretados como signed bytes
    glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, X));
    glEnableVertexAttribArray(0);

    // UV attribute: floats
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvX));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    mesh.uploaded = true;
}

void Renderer::renderAll() {

    glm::mat4 projection = glm::perspective(glm::radians(G.camera->fov), (float)*G.windowWidthRef / (float)*G.windowHeightRef, 0.01f, 5000.0f);
    e_Shaders[shaderType::MAIN].setMat4("projection", projection);
    glm::mat4 view = G.camera->GetViewMatrix();
    e_Shaders[shaderType::MAIN].setMat4("view", view);

    e_Shaders[shaderType::MAIN].use();
    for (const auto& [pos, mesh] : chunkMeshes) {
        if (!mesh.uploaded) continue;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos * CHUNKSIZE));
        e_Shaders[shaderType::MAIN].setMat4("model", model);

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
