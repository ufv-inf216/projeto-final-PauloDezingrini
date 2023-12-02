//
// Created by Lucas N. Ferreira on 10/09/23.
//

#include <algorithm>
#include "CircleColliderComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

CircleColliderComponent::CircleColliderComponent(class Actor* owner, const float radius, const int updateOrder)
        :Component(owner, updateOrder)
        ,mRadius(radius) {
        owner->GetGame()->AddCollider(this);
}

const Vector2& CircleColliderComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

float CircleColliderComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

bool CircleColliderComponent::Intersect(const CircleColliderComponent& c) const
{
    // Calculate amount squared
    Vector2 diff = GetCenter() - c.GetCenter();
    float distSq = diff.LengthSq();

    // Calculate sum of radii squared
    float radiiSq = GetRadius() + c.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;

}


CircleColliderComponent::Overlap CircleColliderComponent::GetMinOverlap(CircleColliderComponent *b) const {

    Vector2 bCenter = b->GetCenter();
    Vector2 center = GetCenter();

    float verticalDist = bCenter.y - center.y;
    float horizontalDist = bCenter.x - center.x;
    float amount;
    bool side;

    if (verticalDist < horizontalDist) {
        side = true;
    } else {
        side = false;
    }

    Vector2 diff = GetCenter() - b->GetCenter();
    float rad = GetRadius() + b->GetRadius();

    Overlap minOverlap{
            .amount = rad - diff.Length(),
            .side = side,
            .target = b
    };
    return minOverlap;
}

void CircleColliderComponent::ResolveCollisions(RigidBodyComponent *rigidBody,
                                                const CircleColliderComponent::Overlap &minOverlap) {

    auto owner = rigidBody->GetOwner();
    Vector2 pos = owner->GetPosition();

    rigidBody->SetVelocity(rigidBody->GetVelocity() * -1);
    auto colliderRigidBody = minOverlap.target->GetOwner()->GetComponent<RigidBodyComponent>();
    colliderRigidBody->SetVelocity(rigidBody->GetVelocity() * -1);

    if (minOverlap.side) {
        pos.y += Vector2::Normalize(rigidBody->GetVelocity()).y * minOverlap.amount;
    } else {
        pos.x += Vector2::Normalize(rigidBody->GetVelocity()).x * minOverlap.amount;
    }

    owner->SetPosition(pos);

}


void CircleColliderComponent::DetectCollision(RigidBodyComponent *rigidBody) {
    auto colliders = mOwner->GetGame()->GetCircleColliders();

    auto circle = mOwner->GetComponent<CircleColliderComponent>();

    Vector2 center = circle->GetCenter();

    std::sort(colliders.begin(), colliders.end(), [this, center](CircleColliderComponent *a, CircleColliderComponent *b) {
        return (center - a->GetCenter()).LengthSq() < (center - b->GetCenter()).LengthSq();
    });

    bool horizontalCollision = false;
    bool verticalCollision = false;
    for (auto collider : colliders) {
        if (!collider->IsEnabled()) {
            continue;
        }

        if (this != collider) {

            if (circle->Intersect(*collider)) {
                Overlap minOverlap = GetMinOverlap(collider);
                ResolveCollisions(rigidBody, minOverlap);
                if (minOverlap.side) {
                    verticalCollision = true;
                } else {
                    horizontalCollision = true;
                }
            }
        }

        if (horizontalCollision && verticalCollision) {
            break;
        }
    }

    // Callback only for closest (first) collision
//    mOwner->OnCollision(responses);
}


