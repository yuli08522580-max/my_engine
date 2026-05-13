#include "../src/physics/Collision2D.h"

#include <cmath>
#include <vector>

namespace {
bool nearlyEqual(float a, float b, float eps = 0.0002f) {
    return std::abs(a - b) < eps;
}
}

int main() {
    using namespace collision2d;

    const AABB dynamic{0.0f, 0.0f, 0.025f, 0.025f};
    const AABB obstacle{0.0f, 0.0f, 0.05f, 0.05f};
    if (!AABBOverlap::intersects(dynamic, obstacle)) return 1;

    const AABB farObstacle{0.2f, 0.2f, 0.05f, 0.05f};
    if (AABBOverlap::intersects(dynamic, farObstacle)) return 2;

    {
        std::vector<AABB> obstacles = {{0.1f, 0.0f, 0.05f, 0.05f}};
        const AABBCollisionResolver resolver(obstacles);
        const Vec2 resolved = resolver.resolveMovement({0.0f, 0.0f}, {0.2f, 0.0f}, {0.025f, 0.025f});
        if (!nearlyEqual(resolved.x, 0.0249f)) return 3;
        if (!nearlyEqual(resolved.y, 0.0f)) return 4;
    }

    {
        std::vector<AABB> obstacles = {{0.0f, -0.1f, 0.05f, 0.05f}};
        const AABBCollisionResolver resolver(obstacles);
        const Vec2 resolved = resolver.resolveMovement({0.0f, 0.0f}, {0.0f, -0.2f}, {0.025f, 0.025f});
        if (!nearlyEqual(resolved.y, -0.0249f)) return 5;
    }

    {
        std::vector<AABB> obstacles = {{0.1f, 0.0f, 0.05f, 0.05f}};
        const AABBCollisionResolver resolver(obstacles);
        const Vec2 resolved = resolver.resolveMovement({0.0f, 0.2f}, {0.2f, 0.0f}, {0.025f, 0.025f});
        if (!nearlyEqual(resolved.x, 0.2f)) return 6;
    }


    {
        // 右壁（法線 -1）に触れて壁ジャンプした直後は、右入力を抑制する。
        const float filtered = suppressTowardWallInput(1.0f, -1.0f, 0.12f);
        if (!nearlyEqual(filtered, 0.0f)) return 7;

        // 壁と逆方向（左）への入力は通す。
        const float away = suppressTowardWallInput(-1.0f, -1.0f, 0.12f);
        if (!nearlyEqual(away, -1.0f)) return 8;

        // ロックアウト終了後は壁方向入力も通す。
        const float afterTimer = suppressTowardWallInput(1.0f, -1.0f, 0.0f);
        if (!nearlyEqual(afterTimer, 1.0f)) return 9;
    }

    return 0;
}
