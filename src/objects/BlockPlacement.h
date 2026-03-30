#pragma once
#include <vector>

namespace block_placement {

// 2D 空間上のブロック配置座標。
struct BlockPos {
    float x;
    float y;
};

// 任意の値を step 間隔のグリッド値に丸める。
float snapToGrid(float value, float step);

// 指定座標に既存ブロックがあるかを許容誤差 eps 付きで判定する。
bool hasBlockAt(const std::vector<BlockPos>& blocks, float x, float y, float eps = 0.001f);

// 座標を snap でグリッド化して重複がなければ追加する。
// 追加できた場合 true、重複で追加しなかった場合 false を返す。
bool tryPlaceBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps = 0.001f);

// 座標を snap でグリッド化し、その位置のブロックを1つ削除する。
// 削除できた場合 true、対象が無い場合 false を返す。
bool tryRemoveBlock(std::vector<BlockPos>& blocks, float x, float y, float snap, float eps = 0.001f);

} // namespace block_placement
