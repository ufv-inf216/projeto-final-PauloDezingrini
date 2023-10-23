//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include <algorithm>
#include "AABBColliderComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

AABBColliderComponent::AABBColliderComponent(class Actor* owner, int dx, int dy, int w, int h, ColliderLayer layer, int updateOrder)
        :Component(owner, updateOrder)
        ,mOffset(Vector2((float)dx, (float)dy))
        ,mWidth(w)
        ,mHeight(h)
        ,mLayer(layer)
{
    mOwner->GetGame()->AddCollider(this);
}

AABBColliderComponent::~AABBColliderComponent()
{
    mOwner->GetGame()->RemoveCollider(this);
}

Vector2 AABBColliderComponent::GetMin() const
{
    return mOffset + mOwner->GetPosition();
}

Vector2 AABBColliderComponent::GetMax() const
{
    return GetMin() + Vector2(mWidth, mHeight);
}

Vector2 AABBColliderComponent::GetCenter() const
{
    return GetMin() + Vector2(mWidth/2, mHeight/2);
}

bool AABBColliderComponent::Intersect(const AABBColliderComponent& b) const
{
    Vector2 aMax = GetMax();
    Vector2 aMin = GetMin();
    Vector2 bMax = b.GetMax();
    Vector2 bMin = b.GetMin();
    bool notColliding = (aMax.x < bMin.x) || (bMax.x < aMin.x) || (aMax.y < bMin.y) || (bMax.y < aMin.y);
    return !notColliding;
}

AABBColliderComponent::Overlap AABBColliderComponent::GetMinOverlap(AABBColliderComponent* b) const
{

    std::unordered_map<int, CollisionSide> overlaps;

    Vector2 aMax = GetMax();
    Vector2 aMin = GetMin();
    Vector2 bMax = b->GetMax();
    Vector2 bMin = b->GetMin();
    overlaps.emplace(bMax.y - aMin.y, CollisionSide::Top);
    overlaps.emplace(bMin.y - aMax.y, CollisionSide::Down);
    overlaps.emplace(bMax.x - aMin.x, CollisionSide::Left);
    overlaps.emplace(bMin.x - aMax.x, CollisionSide::Right);

    float amount = INFINITY;
    CollisionSide side;
    for (auto & overlap : overlaps){
        if (Math::Abs(overlap.first) < Math::Abs(amount)) {
            amount = overlap.first;
            side = overlap.second;
        }
    }

    Overlap minOverlap{
        .amount = amount,
        .side = side,
        .target = b
    };
    return minOverlap;
}

void AABBColliderComponent::ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap)
{

    if (minOverlap.side == CollisionSide::Top || minOverlap.side == CollisionSide::Down){
        mOwner->SetPosition(mOwner->GetPosition() + Vector2(0, minOverlap.amount));
        rigidBody->SetVelocity(Vector2(rigidBody->GetVelocity().x, 0));
    }

    if (minOverlap.side == CollisionSide::Left || minOverlap.side == CollisionSide::Right) {
        mOwner->SetPosition(mOwner->GetPosition() + Vector2(minOverlap.amount, 0));
        rigidBody->SetVelocity(Vector2(0, rigidBody->GetVelocity().y));
    }
}

void AABBColliderComponent::DetectCollision(RigidBodyComponent *rigidBody)
{

    // Sort colliders by amount to the player (center-to-center)
    auto colliders = mOwner->GetGame()->GetColliders();


    std::sort(colliders.begin(), colliders.end(), [this](AABBColliderComponent *a, AABBColliderComponent *b) {
        Vector2 center = this->GetCenter();

        return (a->GetCenter() - center).LengthSq() < (b->GetCenter() - center).LengthSq();
    });
    std::unordered_map<CollisionSide, Overlap> responses;

    bool horizontalCollision = false;
    bool verticalCollision = false;
    for (auto collider : colliders) {
        if (collider == this || !collider->IsEnabled()) {
            continue;
        }

        if (Intersect(*collider)) {
            Overlap minOverlap = GetMinOverlap(collider);
            ResolveCollisions(mOwner->GetComponent<RigidBodyComponent>(), minOverlap);
            responses.emplace(minOverlap.side, minOverlap);
            if (minOverlap.side == CollisionSide::Right || minOverlap.side == CollisionSide::Left) {
                horizontalCollision = true;
            } else {
                verticalCollision = true;
            }
        }

        if (horizontalCollision && verticalCollision) {
            break;
        }
    }

    // Callback only for closest (first) collision
    mOwner->OnCollision(responses);
}