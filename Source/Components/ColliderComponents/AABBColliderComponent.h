//
// Created by Lucas N. Ferreira on 28/09/23.
//

#ifndef AABB
#define AABB

#pragma once
#include "../Component.h"
#include "../../Math.h"
#include "../RigidBodyComponent.h"
#include "CircleColliderComponent.h"
#include <vector>
#include <set>

enum class ColliderLayer
{
    Player,
    Ball,
    Wall,
    Goal,
};

enum class CollisionSide
{
    Top,
    Down,
    Left,
    Right
};

class AABBColliderComponent : public Component
{
public:
    struct Overlap
    {
        float amount;
        CollisionSide side;
        CircleColliderComponent *target;
    };

    AABBColliderComponent(class Actor* owner, int dx, int dy, int w, int h,
                                ColliderLayer layer, int updateOrder = 10);
    ~AABBColliderComponent() override;

    bool Intersect(const AABBColliderComponent& b) const;
    void DetectCollision(RigidBodyComponent *rigidBody);
    float MinDistSq(const Vector2& point) const;

    Vector2 GetMin() const;
    Vector2 GetMax() const;
    Vector2 GetCenter() const;
    ColliderLayer GetLayer() const { return mLayer; }

private:
    Overlap GetMinOverlap(CircleColliderComponent* b) const;
    void ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap);


    Vector2 mOffset;
    int mWidth;
    int mHeight;

    ColliderLayer mLayer;
};

#endif