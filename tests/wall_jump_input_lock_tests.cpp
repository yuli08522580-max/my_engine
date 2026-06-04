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
        nearlyEqual(wall_jump_input_lock::durationSeconds, 0.3f),
        "wall-side input lock should expire quickly without waiting for landing"
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
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::tickLockTimer(wall_jump_input_lock::durationSeconds, 0.1f), 0.2f),
        "lock timer should decrease while airborne"
    );
    ok &= expect(
        nearlyEqual(wall_jump_input_lock::tickLockTimer(wall_jump_input_lock::durationSeconds, 0.3f), 0.0f),
        "lock timer should expire after the short wall-jump lock duration"
    );

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
