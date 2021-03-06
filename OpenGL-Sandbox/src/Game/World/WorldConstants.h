#pragma once

#include<array>

namespace WorldConstants
{
	constexpr int ChunkHeight = 128;
	constexpr int ChunkSize = 16;
	constexpr int ChunkVolume = ChunkSize * ChunkSize * ChunkHeight;
	constexpr int GrassLevel = 32;
	constexpr int WaterLevel = GrassLevel - 3;
	constexpr int RenderDistance = 8;
	constexpr int TreeHeight = 7;
}

using ChunkHeightMap = std::array<int, WorldConstants::ChunkSize * WorldConstants::ChunkSize>;