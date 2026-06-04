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
        nearlyEqual(horizontal_movement::inputVelocity(1.0f, false), horizontal_movement::airborneInputSpeed),
        "airborne input should be slower than grounded movement"
    );

    ok &= expect(
        horizontal_movement::airborneInputSpeed < horizontal_movement::groundSpeed,
        "airborne control should remain intentionally weaker than ground control"
    );

    ok &= expect(
        nearlyEqual(horizontal_movement::inputVelocity(-1.0f, false), -horizontal_movement::airborneInputSpeed),
        "airborne left input should keep direction while using the slower speed"
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
        horizontal_movement::nextVelocity(0.0f, 1.0f, true, 1.0f / 60.0f) > 0.0f,
        "ground input should accelerate from rest instead of snapping through state"
    );

    ok &= expect(
        horizontal_movement::nextVelocity(horizontal_movement::groundSpeed, -1.0f, false, 1.0f / 60.0f)
            < horizontal_movement::groundSpeed,
        "opposite airborne input should be able to steer carried speed down gradually"
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
