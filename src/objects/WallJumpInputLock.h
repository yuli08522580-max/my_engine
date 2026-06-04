#pragma once

namespace wall_jump_input_lock {
// 壁ジャンプ直後に壁側入力を無効化する時間[s]。
// 滞空時間より十分短くし、着地を待たずに操作を復帰させる。
constexpr float durationSeconds = 0.3f;

// 壁側の入力方向を返す（左壁: -1, 右壁: +1）。
constexpr float lockedDirectionForWall(bool touchingWallLeft) {
    return touchingWallLeft ? -1.0f : 1.0f;
}

// 経過時間で入力ロック残り時間を進め、0未満にならないようにする。
constexpr float tickLockTimer(float lockTimer, float dt) {
    const float nextTimer = lockTimer - dt;
    return nextTimer > 0.0f ? nextTimer : 0.0f;
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
