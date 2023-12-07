//
// Created by Paulo Dezingrini on 24/11/2023.
//

#pragma once
#ifndef BRAZILSTRIKERS_WALL_H
#define BRAZILSTRIKERS_WALL_H


#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "Actor.h"

class Wall : public Actor {
public:
    Wall(Game* game, float dx, float dy, float w, float h, ColliderLayer layer, bool isGoal = false);

    void SetTeam(bool team) { mTeam = team; }
    bool getTeam() { return mTeam; }
private:
    bool mIsGoal;
    bool mTeam;

    AABBColliderComponent* mColliderComponent;
    RigidBodyComponent* mRigidBody;
};


#endif //BRAZILSTRIKERS_WALL_H
