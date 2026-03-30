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

    return 0;
}
