#pragma once

#include <vector>

namespace collision2d {

struct AABB {
    float centerX;
    float centerY;
    float halfWidth;
    float halfHeight;
};

struct Vec2 {
    float x;
    float y;
};

// AABB 同士の重なり判定を提供する。
class AABBOverlap {
public:
    static bool intersects(const AABB& a, const AABB& b);
};

// 動く AABB を静的な障害物 AABB 群に対して衝突解決する。
class AABBCollisionResolver {
public:
    explicit AABBCollisionResolver(std::vector<AABB> staticColliders);

    Vec2 resolveMovement(const Vec2& start, const Vec2& delta, const Vec2& halfSize) const;

private:
    float resolveAxisX(float currentX, float currentY, float targetX, const Vec2& halfSize) const;
    float resolveAxisY(float currentX, float currentY, float targetY, const Vec2& halfSize) const;

    std::vector<AABB> staticColliders;
};



// 壁ジャンプ直後の短時間、壁方向への入力を抑制する補助関数。
// wallNormalX は接触した壁の法線 X 成分（右壁なら -1、左壁なら +1）。
// lockoutTimer が正の間は、壁方向（法線と逆向き）の入力だけ 0 にする。
float suppressTowardWallInput(float desiredMoveX, float wallNormalX, float lockoutTimer);

} // namespace collision2d
