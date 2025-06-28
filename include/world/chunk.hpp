#pragma once

#include <configs.hpp>
#include <block.hpp>

#include <array>
#include <glm/glm.hpp>

class Chunk {
private:
	glm::ivec3 worldPos;
	std::array<Block, CHUNKSIZE * CHUNKSIZE * CHUNKSIZE> chunkData;

	int index(int x, int y, int z) {
		return (x + CHUNKSIZE * (y + CHUNKSIZE * z));
	}

public:

	Block& getBlock(int x, int y, int z) {
		return chunkData[index(x,y,z)];
	}

	

};