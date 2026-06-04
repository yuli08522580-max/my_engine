#pragma once

namespace wall_jump_force {

// 壁ジャンプ時に壁から離れる方向へ付与する水平速度。
// 地上速度より少し強い程度に抑え、壁ジャンプ直後に横へ飛びすぎないようにする。
constexpr float horizontalSpeed = 0.75f;
// 壁ジャンプ時の水平速度を維持する時間[s]。
// 短めにして、壁から離れる初速だけを軽く補助する。
constexpr float boostDuration = 0.06f;

// 左壁なら右向き、右壁なら左向きの壁ジャンプ水平速度を返す。
constexpr float velocityAwayFromWall(bool touchingWallLeft) {
    return touchingWallLeft ? horizontalSpeed : -horizontalSpeed;
}

} // namespace wall_jump_force
