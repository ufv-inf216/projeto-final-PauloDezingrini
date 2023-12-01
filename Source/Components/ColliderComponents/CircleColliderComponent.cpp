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
                Vector2 pos = rigidBody->GetOwner()->GetPosition();
                rigidBody->SetVelocity(rigidBody->GetVelocity() * -1);
                auto colliderRigidBody = collider->GetOwner()->GetComponent<RigidBodyComponent>();
                colliderRigidBody->SetVelocity(rigidBody->GetVelocity() * -1);
            }
        }

        if (horizontalCollision && verticalCollision) {
            break;
        }
    }

    // Callback only for closest (first) collision
//    mOwner->OnCollision(responses);
}