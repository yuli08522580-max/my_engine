#pragma once

#include <algorithm>
#include <cmath>

namespace horizontal_movement {

// 通常移動時の地上水平速度。空中入力もこの速度を超えて加速しない。
constexpr float groundSpeed = 0.6f;
// 地上入力で目標速度へ近づく加速度。
constexpr float groundAcceleration = 8.0f;
// 地上で入力がないときだけ速度を落とす摩擦。
constexpr float groundFriction = 10.0f;
// 空中で地上と同じ目標速度へゆっくり近づく加速度。
constexpr float airborneAcceleration = 1.8f;
// 坂や壁ジャンプなどの外力も含めて維持できる水平速度の上限。
constexpr float maxCarrySpeed = 1.2f;

// 入力方向(-1..1)と接地状態から、その状態で目指す水平速度を返す。
constexpr float inputVelocity(float inputDirection, bool grounded) {
    (void)grounded;
    return std::clamp(inputDirection, -1.0f, 1.0f) * groundSpeed;
}

constexpr float approach(float current, float target, float maxDelta) {
    if (current < target) {
        return std::min(current + maxDelta, target);
    }
    if (current > target) {
        return std::max(current - maxDelta, target);
    }
    return current;
}

inline float nextVelocity(float currentVelocity, float inputDirection, bool grounded, float dt) {
    const float input = std::clamp(inputDirection, -1.0f, 1.0f);
    if (grounded) {
        const float targetVelocity = input * groundSpeed;
        const float acceleration = (std::fabs(input) > 0.0f) ? groundAcceleration : groundFriction;
        return approach(currentVelocity, targetVelocity, acceleration * dt);
    }

    const float carriedVelocity = std::clamp(currentVelocity, -maxCarrySpeed, maxCarrySpeed);
    if (std::fabs(input) == 0.0f) {
        return carriedVelocity;
    }

    // 空中操作は地上と同じ最高速度を目標にするが、加速は弱くする。
    // そのため垂直ジャンプからの横移動は少しずつ始まり、地上で得た速度と逆入力した場合も急停止せず軽くブレーキする。
    const float targetVelocity = input * groundSpeed;
    return approach(carriedVelocity, targetVelocity, airborneAcceleration * dt);
}

} // namespace horizontal_movement
