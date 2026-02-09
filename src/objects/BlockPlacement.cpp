#include "BlockPlacement.h"
#include <algorithm>
#include <cmath>

namespace block_placement {

float snapToGrid(float value, float step) {
    return std::round(value / step) * step;
}

bool hasBlockAt(const std::vector<BlockPos>& blocks, float x, float y, float eps) {
    return std::any_of(blocks.begin(), blocks.end(), [&](const BlockPos& block) {
        return std::abs(block.x - x) < eps && std::abs(block.y - y) < eps;
    });
}

bool tryPlaceBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps) {
    const float snappedX = snapToGrid(x, snap);
    const float snappedY = snapToGrid(y, snap);

    if (hasBlockAt(blocks, snappedX, snappedY, eps)) {
        return false;
    }

    blocks.push_back({snappedX, snappedY});
    return true;
}

} // namespace block_placement
#include "BlockPlacement.h"
#include <algorithm>
#include <cmath>

namespace block_placement {

float snapToGrid(float value, float step) {
    return std::round(value / step) * step;
}

bool hasBlockAt(const std::vector<BlockPos>& blocks, float x, float y, float eps) {
    return std::any_of(blocks.begin(), blocks.end(), [&](const BlockPos& block) {
        return std::abs(block.x - x) < eps && std::abs(block.y - y) < eps;
    });
}

bool tryPlaceBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps) {
    // 入力座標をグリッド上へスナップしてから重複判定を行う。
    const float snappedX = snapToGrid(x, snap);
    const float snappedY = snapToGrid(y, snap);

    if (hasBlockAt(blocks, snappedX, snappedY, eps)) {
        return false;
    }

    blocks.push_back({snappedX, snappedY});
    return true;
}

bool tryRemoveBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps) {
    const float snappedX = snapToGrid(x, snap);
    const float snappedY = snapToGrid(y, snap);

    const auto it = std::find_if(blocks.begin(), blocks.end(), [&](const BlockPos& block) {
        return std::abs(block.x - snappedX) < eps && std::abs(block.y - snappedY) < eps;
    });

    if (it == blocks.end()) {
        return false;
    }

    blocks.erase(it);
    return true;
}

} // namespace block_placement
