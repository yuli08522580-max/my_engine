#pragma once

#include <algorithm>
#include <cmath>

namespace horizontal_movement {

// 通常移動時の地上水平速度。
constexpr float groundSpeed = 0.6f;
// 地上で慣性を得ていない状態からの空中水平操作は控えめにする。
constexpr float airborneInputSpeed = 0.12f;
// 地上入力で目標速度へ近づく加速度。
constexpr float groundAcceleration = 8.0f;
// 地上で入力がないときだけ速度を落とす摩擦。
constexpr float groundFriction = 10.0f;
// 空中での追加操作量。地面や坂で得た速度は入力がない限り消さない。
constexpr float airborneAcceleration = 1.8f;
// 坂や壁ジャンプなどの外力も含めて維持できる水平速度の上限。
constexpr float maxCarrySpeed = 1.2f;

// 入力方向(-1..1)と接地状態から、そのフレームで使う水平速度を返す。
constexpr float inputVelocity(float inputDirection, bool grounded) {
    return inputDirection * (grounded ? groundSpeed : airborneInputSpeed);
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

    if (std::fabs(input) == 0.0f) {
        return std::clamp(currentVelocity, -maxCarrySpeed, maxCarrySpeed);
    }

    return std::clamp(
        currentVelocity + input * airborneAcceleration * dt,
        -maxCarrySpeed,
        maxCarrySpeed
    );
}

} // namespace horizontal_movement
