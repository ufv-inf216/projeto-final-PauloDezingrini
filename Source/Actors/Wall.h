//
// Created by Paulo Dezingrini on 24/11/2023.
//

#pragma once
#ifndef BRAZILSTRIKERS_WALL_H
#define BRAZILSTRIKERS_WALL_H


#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "Actor.h"
#include "../Scenes/Scene.h"

class Wall : public Actor {
public:
    Wall(Scene* scene, float dx, float dy, float w, float h, ColliderLayer layer, bool isGoal = false);

private:
    bool mIsGoal;
    bool mTeam;

    AABBColliderComponent* mColliderComponent;
    RigidBodyComponent* mRigidBody;
};


#endif //BRAZILSTRIKERS_WALL_H
