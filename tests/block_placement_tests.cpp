#include "../src/objects/BlockPlacement.h"
#include <cmath>

namespace {
bool nearlyEqual(float a, float b, float eps = 0.0001f) {
    return std::abs(a - b) < eps;
}
}

int main() {
    using namespace block_placement;

    if (!nearlyEqual(snapToGrid(0.14f, 0.1f), 0.1f)) return 1;
    if (!nearlyEqual(snapToGrid(0.15f, 0.1f), 0.2f)) return 2;

    std::vector<BlockPos> blocks;
    if (!tryPlaceBlock(blocks, 0.14f, -0.16f, 0.1f)) return 3;
    if (blocks.size() != 1) return 4;
    if (!nearlyEqual(blocks[0].x, 0.1f) || !nearlyEqual(blocks[0].y, -0.2f)) return 5;

    if (tryPlaceBlock(blocks, 0.11f, -0.19f, 0.1f)) return 6;
    if (blocks.size() != 1) return 7;

    if (!tryPlaceBlock(blocks, 0.31f, -0.19f, 0.1f)) return 8;
    if (blocks.size() != 2) return 9;

    return 0;
}
