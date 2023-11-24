//
// Created by Paulo Dezingrini on 24/11/2023.
//

#include "Wall.h"
#include "../Game.h"

Wall::Wall(Game* game, float dx, float dy, float w, float h, ColliderLayer layer): Actor(game) {
    mColliderComponent = new AABBColliderComponent(this, dx, dy, w, h, layer);
    mRigidBody = new RigidBodyComponent(this);
}