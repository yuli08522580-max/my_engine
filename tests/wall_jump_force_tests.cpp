#include "../src/objects/WallJumpForce.h"
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
        nearlyEqual(wall_jump_force::horizontalSpeed, 0.75f),
        "wall-jump horizontal speed should stay modest after tuning"
    );

    ok &= expect(
        wall_jump_force::horizontalSpeed > horizontal_movement::groundSpeed,
        "wall-jump horizontal speed should still push the player away from the wall"
    );

    ok &= expect(
        wall_jump_force::horizontalSpeed < horizontal_movement::maxCarrySpeed,
        "wall-jump horizontal speed should stay below the carry-speed cap"
    );

    ok &= expect(
        nearlyEqual(wall_jump_force::boostDuration, 0.06f),
        "wall-jump boost should be brief so the initial push does not feel too strong"
    );

    ok &= expect(
        nearlyEqual(wall_jump_force::velocityAwayFromWall(true), wall_jump_force::horizontalSpeed),
        "left-wall jump should push to the right"
    );

    ok &= expect(
        nearlyEqual(wall_jump_force::velocityAwayFromWall(false), -wall_jump_force::horizontalSpeed),
        "right-wall jump should push to the left"
    );

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
