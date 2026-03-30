#include "PlayerPhysicsTuning.h"

PlayerPhysicsTuning::PlayerPhysicsTuning(float gravityAcceleration, float jumpVelocity)
: gravityAcceleration(clampValue(gravityAcceleration, minGravityAcceleration, maxGravityAcceleration)),
  jumpVelocity(clampValue(jumpVelocity, minJumpVelocity, maxJumpVelocity))
{}

float PlayerPhysicsTuning::gravity() const {
    return gravityAcceleration;
}

float PlayerPhysicsTuning::jump() const {
    return jumpVelocity;
}

void PlayerPhysicsTuning::adjustGravity(float delta) {
    gravityAcceleration = clampValue(
        gravityAcceleration + delta,
        minGravityAcceleration,
        maxGravityAcceleration
    );
}

void PlayerPhysicsTuning::adjustJump(float delta) {
    jumpVelocity = clampValue(
        jumpVelocity + delta,
        minJumpVelocity,
        maxJumpVelocity
    );
}

float PlayerPhysicsTuning::clampValue(float value, float minValue, float maxValue) {
    if (value < minValue) {
        return minValue;
    }
    if (value > maxValue) {
        return maxValue;
    }
    return value;
}
