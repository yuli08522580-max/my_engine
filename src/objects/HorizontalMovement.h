#pragma once

namespace horizontal_movement {

// 通常移動時の地上水平速度。
constexpr float groundSpeed = 0.6f;
// 地上で慣性を得ていない状態からの空中水平操作は控えめにする。
constexpr float airborneInputSpeed = 0.12f;

// 入力方向(-1..1)と接地状態から、そのフレームで使う水平速度を返す。
constexpr float inputVelocity(float inputDirection, bool grounded) {
    return inputDirection * (grounded ? groundSpeed : airborneInputSpeed);
}

} // namespace horizontal_movement
