#include <world.hpp>
#include <camera.hpp>
#include <configs.hpp>
#include <appContext.hpp>

void World::queueChunkGen(Camera& camera) {
    glm::vec3 playerPos = camera.getCamPos();
    glm::ivec3 playerChunkPos = coordToChunkCoord(playerPos.x, playerPos.y, playerPos.z);
    
    cfg.renderDistance;




}

glm::ivec3 World::coordToChunkCoord(int x, int y, int z) {
    auto flooredDiv = [](int value, int size) {
        return (value >= 0) ? (value / size) : ((value - size + 1) / size);
        };

    return glm::ivec3(
        flooredDiv(x, CHUNKSIZE),
        flooredDiv(y, CHUNKSIZE),
        flooredDiv(z, CHUNKSIZE)
    );
}

