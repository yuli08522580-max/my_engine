#include "../src/objects/PlayerPhysicsTuning.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {
bool nearlyEqual(float a, float b) {
    return std::fabs(a - b) < 1e-6f;
}

bool expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "[FAIL] " << message << '\n';
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    PlayerPhysicsTuning tuning;
    tuning.adjustGravity(0.2f);
    ok &= expect(nearlyEqual(tuning.gravity(), 2.0f), "gravity should increase by delta");

    tuning.adjustGravity(10.0f);
    ok &= expect(
        nearlyEqual(tuning.gravity(), PlayerPhysicsTuning::maxGravityAcceleration),
        "gravity should clamp to max"
    );

    tuning.adjustGravity(-10.0f);
    ok &= expect(
        nearlyEqual(tuning.gravity(), PlayerPhysicsTuning::minGravityAcceleration),
        "gravity should clamp to min"
    );

    const float initialJump = tuning.jump();
    tuning.adjustJump(0.1f);
    ok &= expect(nearlyEqual(tuning.jump(), initialJump + 0.1f), "jump should increase by delta");

    tuning.adjustJump(10.0f);
    ok &= expect(
        nearlyEqual(tuning.jump(), PlayerPhysicsTuning::maxJumpVelocity),
        "jump should clamp to max"
    );

    tuning.adjustJump(-10.0f);
    ok &= expect(
        nearlyEqual(tuning.jump(), PlayerPhysicsTuning::minJumpVelocity),
        "jump should clamp to min"
    );

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
