#include "Collision2D.h"

#include <algorithm>
#include <utility>

namespace collision2d {

namespace {
constexpr float kSkinWidth = 0.0001f;

bool overlapsOnY(float dynamicCenterY, float dynamicHalfHeight, const AABB& obstacle) {
    const float dynamicMinY = dynamicCenterY - dynamicHalfHeight;
    const float dynamicMaxY = dynamicCenterY + dynamicHalfHeight;
    const float obstacleMinY = obstacle.centerY - obstacle.halfHeight;
    const float obstacleMaxY = obstacle.centerY + obstacle.halfHeight;
    return dynamicMaxY > obstacleMinY && dynamicMinY < obstacleMaxY;
}

bool overlapsOnX(float dynamicCenterX, float dynamicHalfWidth, const AABB& obstacle) {
    const float dynamicMinX = dynamicCenterX - dynamicHalfWidth;
    const float dynamicMaxX = dynamicCenterX + dynamicHalfWidth;
    const float obstacleMinX = obstacle.centerX - obstacle.halfWidth;
    const float obstacleMaxX = obstacle.centerX + obstacle.halfWidth;
    return dynamicMaxX > obstacleMinX && dynamicMinX < obstacleMaxX;
}
} // namespace

bool AABBOverlap::intersects(const AABB& a, const AABB& b) {
    const float aMinX = a.centerX - a.halfWidth;
    const float aMaxX = a.centerX + a.halfWidth;
    const float aMinY = a.centerY - a.halfHeight;
    const float aMaxY = a.centerY + a.halfHeight;

    const float bMinX = b.centerX - b.halfWidth;
    const float bMaxX = b.centerX + b.halfWidth;
    const float bMinY = b.centerY - b.halfHeight;
    const float bMaxY = b.centerY + b.halfHeight;

    return aMaxX > bMinX && aMinX < bMaxX && aMaxY > bMinY && aMinY < bMaxY;
}

AABBCollisionResolver::AABBCollisionResolver(std::vector<AABB> staticColliders)
: staticColliders(std::move(staticColliders)) {}

Vec2 AABBCollisionResolver::resolveMovement(const Vec2& start, const Vec2& delta, const Vec2& halfSize) const {
    const float targetX = start.x + delta.x;
    const float resolvedX = resolveAxisX(start.x, start.y, targetX, halfSize);

    const float targetY = start.y + delta.y;
    const float resolvedY = resolveAxisY(resolvedX, start.y, targetY, halfSize);

    return {resolvedX, resolvedY};
}

float AABBCollisionResolver::resolveAxisX(float currentX, float currentY, float targetX, const Vec2& halfSize) const {
    if (targetX == currentX) {
        return currentX;
    }

    float resultX = targetX;
    if (targetX > currentX) {
        for (const auto& obstacle : staticColliders) {
            if (!overlapsOnY(currentY, halfSize.y, obstacle)) {
                continue;
            }

            const float obstacleMinX = obstacle.centerX - obstacle.halfWidth;
            const float dynamicCurrentMaxX = currentX + halfSize.x;
            const float dynamicTargetMaxX = targetX + halfSize.x;
            if (dynamicCurrentMaxX <= obstacleMinX && dynamicTargetMaxX > obstacleMinX) {
                resultX = std::min(resultX, obstacleMinX - halfSize.x - kSkinWidth);
            }
        }
    } else {
        for (const auto& obstacle : staticColliders) {
            if (!overlapsOnY(currentY, halfSize.y, obstacle)) {
                continue;
            }

            const float obstacleMaxX = obstacle.centerX + obstacle.halfWidth;
            const float dynamicCurrentMinX = currentX - halfSize.x;
            const float dynamicTargetMinX = targetX - halfSize.x;
            if (dynamicCurrentMinX >= obstacleMaxX && dynamicTargetMinX < obstacleMaxX) {
                resultX = std::max(resultX, obstacleMaxX + halfSize.x + kSkinWidth);
            }
        }
    }
    return resultX;
}

float AABBCollisionResolver::resolveAxisY(float currentX, float currentY, float targetY, const Vec2& halfSize) const {
    if (targetY == currentY) {
        return currentY;
    }

    float resultY = targetY;
    if (targetY > currentY) {
        for (const auto& obstacle : staticColliders) {
            if (!overlapsOnX(currentX, halfSize.x, obstacle)) {
                continue;
            }

            const float obstacleMinY = obstacle.centerY - obstacle.halfHeight;
            const float dynamicCurrentMaxY = currentY + halfSize.y;
            const float dynamicTargetMaxY = targetY + halfSize.y;
            if (dynamicCurrentMaxY <= obstacleMinY && dynamicTargetMaxY > obstacleMinY) {
                resultY = std::min(resultY, obstacleMinY - halfSize.y - kSkinWidth);
            }
        }
    } else {
        for (const auto& obstacle : staticColliders) {
            if (!overlapsOnX(currentX, halfSize.x, obstacle)) {
                continue;
            }

            const float obstacleMaxY = obstacle.centerY + obstacle.halfHeight;
            const float dynamicCurrentMinY = currentY - halfSize.y;
            const float dynamicTargetMinY = targetY - halfSize.y;
            if (dynamicCurrentMinY >= obstacleMaxY && dynamicTargetMinY < obstacleMaxY) {
                resultY = std::max(resultY, obstacleMaxY + halfSize.y + kSkinWidth);
            }
        }
    }

    return resultY;
}

} // namespace collision2d
