#pragma once

// ジャンプ力と重力のチューニング値を保持し、範囲内で調整する。
class PlayerPhysicsTuning {
public:
    static constexpr float minGravityAcceleration = 0.2f;
    static constexpr float maxGravityAcceleration = 4.0f;
    static constexpr float minJumpVelocity = 0.2f;
    static constexpr float maxJumpVelocity = 2.0f;

    explicit PlayerPhysicsTuning(
        float gravityAcceleration = 2.6f,
        float jumpVelocity = 1.05f
    );

    float gravity() const;
    float jump() const;

    void adjustGravity(float delta);
    void adjustJump(float delta);

private:
    static float clampValue(float value, float minValue, float maxValue);

    float gravityAcceleration;
    float jumpVelocity;
};
