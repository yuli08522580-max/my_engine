#include "../src/objects/WallJumpInputLock.h"

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
        wall_jump_input_lock::durationSeconds >= 2.0f,
        "wall-side input lock should last for a few seconds"
    );

    ok &= expect(
        nearlyEqual(wall_jump_input_lock::lockedDirectionForWall(true), -1.0f),
        "left wall should lock left input"
    );
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::lockedDirectionForWall(false), 1.0f),
        "right wall should lock right input"
    );

    ok &= expect(
        nearlyEqual(wall_jump_input_lock::suppressWallSideInput(-1.0f, -1.0f, 0.5f), 0.0f),
        "left input should be suppressed while locked to a left wall"
    );
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::suppressWallSideInput(1.0f, -1.0f, 0.5f), 1.0f),
        "right input should remain available while locked to a left wall"
    );
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::suppressWallSideInput(1.0f, 1.0f, 0.5f), 0.0f),
        "right input should be suppressed while locked to a right wall"
    );
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::suppressWallSideInput(1.0f, 1.0f, 0.0f), 1.0f),
        "input should be restored after the lock timer expires"
    );

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
