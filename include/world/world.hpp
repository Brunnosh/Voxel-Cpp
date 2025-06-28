#pragma once

#include <chunk.hpp>
#include <hash.hpp>

#include <unordered_map>
#include <glm/glm.hpp>

class Camera;

struct worldSettings
{
	uint8_t worldHeight = 8;
};

class World {
private:
	std::unordered_map<glm::ivec3, Chunk, Vec3Hash> worldChunkData;
	worldSettings settings;
	

public:

	World() {

	}
	World(uint8_t p_WorldHeight) {
		settings.worldHeight = p_WorldHeight;
	}


	void queueChunkGen(Camera & camera);

	glm::ivec3 coordToChunkCoord(int x, int y, int z);

	Chunk& getChunk(glm::ivec3 pos){
		auto it = worldChunkData.find(pos);
		if (it != worldChunkData.end()) return it->second;
	}


};