//
// Created by Lucas N. Ferreira on 10/09/23.
//

#pragma once
#include "../Component.h"
#include "../../Math.h"
#include <vector>

class CircleColliderComponent : public Component
{
public:
    CircleColliderComponent(class Actor* owner, float radius, int updateOrder = 10);

    bool Contains(const Vector2& point) const;
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const;

    const Vector2& GetCenter() const;

    bool Intersect(const CircleColliderComponent& b) const;

private:
    Vector2 mCenter;
    float mRadius;
};

