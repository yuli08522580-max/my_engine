#include "../src/objects/HorizontalMovement.h"

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

    ok &= expect(
        nearlyEqual(horizontal_movement::inputVelocity(1.0f, true), horizontal_movement::groundSpeed),
        "grounded input should use the normal ground speed"
    );

    ok &= expect(
        nearlyEqual(horizontal_movement::inputVelocity(1.0f, false), horizontal_movement::groundSpeed),
        "airborne input should target the same top speed as grounded movement"
    );

    ok &= expect(
        nearlyEqual(horizontal_movement::inputVelocity(-1.0f, false), -horizontal_movement::groundSpeed),
        "airborne left input should keep direction while targeting ground speed"
    );

    ok &= expect(
        nearlyEqual(horizontal_movement::inputVelocity(0.0f, false), 0.0f),
        "no airborne input should not create horizontal movement"
    );

    ok &= expect(
        nearlyEqual(
            horizontal_movement::nextVelocity(horizontal_movement::groundSpeed, 0.0f, false, 1.0f / 60.0f),
            horizontal_movement::groundSpeed
        ),
        "airborne frames without input should preserve speed gained on the ground or slopes"
    );

    ok &= expect(
        horizontal_movement::nextVelocity(0.0f, 1.0f, false, 1.0f / 60.0f)
            < horizontal_movement::groundSpeed,
        "vertical jumps should only gain a small amount of horizontal speed per airborne frame"
    );

    ok &= expect(
        nearlyEqual(
            horizontal_movement::nextVelocity(horizontal_movement::groundSpeed, 1.0f, false, 1.0f / 60.0f),
            horizontal_movement::groundSpeed
        ),
        "same-direction airborne input should not accelerate past ground speed"
    );

    ok &= expect(
        horizontal_movement::nextVelocity(0.0f, 1.0f, true, 1.0f / 60.0f) >
            horizontal_movement::nextVelocity(0.0f, 1.0f, false, 1.0f / 60.0f),
        "ground input should accelerate more strongly than airborne input"
    );

    const float oppositeAirborneVelocity = horizontal_movement::nextVelocity(
        horizontal_movement::groundSpeed,
        -1.0f,
        false,
        1.0f / 60.0f
    );
    ok &= expect(
        oppositeAirborneVelocity < horizontal_movement::groundSpeed && oppositeAirborneVelocity > 0.0f,
        "opposite airborne input should lightly brake carried ground speed without instantly reversing"
    );

    ok &= expect(
        nearlyEqual(
            horizontal_movement::nextVelocity(horizontal_movement::maxCarrySpeed * 2.0f, 0.0f, false, 1.0f / 60.0f),
            horizontal_movement::maxCarrySpeed
        ),
        "carried airborne speed should remain capped"
    );

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
