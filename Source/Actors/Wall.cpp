//
// Created by Paulo Dezingrini on 24/11/2023.
//

#include "Wall.h"
#include "../Game.h"

Wall::Wall(Scene* scene, float dx, float dy, float w, float h, ColliderLayer layer, bool isGoal): Actor(scene), mIsGoal(isGoal) {
    mColliderComponent = new AABBColliderComponent(this, dx, dy, w, h, layer);
    mRigidBody = new RigidBodyComponent(this);
}