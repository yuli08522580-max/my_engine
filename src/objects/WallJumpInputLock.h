#pragma once

namespace wall_jump_input_lock {
// 壁ジャンプ直後に壁側入力を無効化する時間[s]。
constexpr float durationSeconds = 2.0f;

// 壁側の入力方向を返す（左壁: -1, 右壁: +1）。
constexpr float lockedDirectionForWall(bool touchingWallLeft) {
    return touchingWallLeft ? -1.0f : 1.0f;
}

// 入力ロック中に壁側へ戻る入力だけを無効化し、壁から離れる入力は維持する。
constexpr float suppressWallSideInput(float horizontalInput, float lockedDirectionX, float lockTimer) {
    if (lockTimer <= 0.0f) {
        return horizontalInput;
    }
    if ((lockedDirectionX < 0.0f && horizontalInput < 0.0f) ||
        (lockedDirectionX > 0.0f && horizontalInput > 0.0f)) {
        return 0.0f;
    }
    return horizontalInput;
}
}
