//
// Created by Lucas N. Ferreira on 10/09/23.
//

#pragma once
#include "../Component.h"
#include "../../Math.h"
#include "../RigidBodyComponent.h"
#include <vector>

class CircleColliderComponent : public Component
{
public:

    struct Overlap
    {
        float amount;
        bool side;
        CircleColliderComponent *target;
    };

    CircleColliderComponent(class Actor* owner, float radius, bool isBall = false, bool draw = false, int updateOrder = 10);

    bool Contains(const Vector2& point) const;
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const;
    bool GetIsBall() { return mIsBall; }

    const Vector2& GetCenter() const;

    bool Intersect(const CircleColliderComponent& b) const;
    void DetectCollision(RigidBodyComponent *rigidBody);

private:
    Overlap GetMinOverlap(CircleColliderComponent* b) const;
    void ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap);
    Vector2 mCenter;
    float mRadius;
    bool mIsBall;
};

