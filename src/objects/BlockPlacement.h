#pragma once
#include <vector>

namespace block_placement {

struct BlockPos {
    float x;
    float y;
};

float snapToGrid(float value, float step);
bool hasBlockAt(const std::vector<BlockPos>& blocks, float x, float y, float eps = 0.001f);
bool tryPlaceBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps = 0.001f);

} // namespace block_placement
