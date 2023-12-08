//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include <algorithm>
#include "AABBColliderComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"
#include "../../Collision.h"

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

AABBColliderComponent::Overlap AABBColliderComponent::GetMinOverlap(CircleColliderComponent* b) const
{

    std::unordered_map<int, CollisionSide> overlaps;

    float radius = b->GetRadius();
    Vector2 aMax = GetMax();
    Vector2 aMin = GetMin();
    Vector2 bCenter = b->GetCenter();
    overlaps.emplace(bCenter.y - aMin.y, CollisionSide::Top);
    overlaps.emplace(bCenter.y - aMax.y, CollisionSide::Down);
    overlaps.emplace(bCenter.x - aMin.x, CollisionSide::Left);
    overlaps.emplace(bCenter.x - aMax.x, CollisionSide::Right);

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
    auto owner = rigidBody->GetOwner();
    Vector2 pos = owner->GetPosition();

    if (minOverlap.side == CollisionSide::Top || minOverlap.side == CollisionSide::Down){
        rigidBody->SetVelocity(Vector2(rigidBody->GetVelocity().x, rigidBody->GetVelocity().y * -1.0f));
        if (minOverlap.side == CollisionSide::Down) {
            pos.y += Vector2::Normalize(rigidBody->GetVelocity()).y * minOverlap.amount;
        } else {
            pos.y -= Vector2::Normalize(rigidBody->GetVelocity()).y * minOverlap.amount;
        }
    }

    if (minOverlap.side == CollisionSide::Left || minOverlap.side == CollisionSide::Right) {
        rigidBody->SetVelocity(Vector2(rigidBody->GetVelocity().x * -1.0f, rigidBody->GetVelocity().y));
        if (minOverlap.side == CollisionSide::Right) {
            pos.x += Vector2::Normalize(rigidBody->GetVelocity()).x * minOverlap.amount;
        } else {
            pos.x -= Vector2::Normalize(rigidBody->GetVelocity()).x * minOverlap.amount;
        }
    }

    if (mLayer == ColliderLayer::Goal && minOverlap.target->GetIsBall()) {
        owner->GetGame()->ResetMatchState();
        auto score = owner->GetGame()->GetScore();
        auto it = score->find(owner->GetTeam());
        owner->GetGame()->ScoreGoal(it->first);
    }

    owner->SetPosition(pos);
}

void AABBColliderComponent::DetectCollision(RigidBodyComponent *rigidBody)
{
    // Sort colliders by amount to the player (center-to-center)
    auto colliders = mOwner->GetGame()->GetCircleColliders();

    auto *box = rigidBody->GetOwner()->GetComponent<AABBColliderComponent>();

    std::sort(colliders.begin(), colliders.end(), [this, box](CircleColliderComponent *a, CircleColliderComponent *b) {
        Vector2 center = this->GetCenter();

        return box->MinDistSq(a->GetCenter()) < box->MinDistSq(b->GetCenter());
    });

    std::unordered_map<CollisionSide, Overlap> responses;

    bool horizontalCollision = false;
    bool verticalCollision = false;
    for (auto collider : colliders) {
        if (!collider->IsEnabled()) {
            continue;
        }

        if (::Intersect(*collider, *this)) {
            Overlap minOverlap = GetMinOverlap(collider);
            SDL_Log("Overlap: Amount: %f", minOverlap.amount);
            ResolveCollisions(collider->GetOwner()->GetComponent<RigidBodyComponent>(), minOverlap);
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

float AABBColliderComponent::MinDistSq(const Vector2 &point) const {

    Vector2 min = GetMin();
    Vector2 max = GetMax();

    // Compute differences for each axis
    float dx = Math::Max(min.x - point.x, 0.0f);
    dx = Math::Max(dx, point.x - max.x);
    float dy = Math::Max(min.y - point.y, 0.0f);
    dy = Math::Max(dy, point.y - max.y);
    // Distance squared formula
    return dx * dx + dy * dy;
}