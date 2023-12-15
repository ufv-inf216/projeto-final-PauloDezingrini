//
// Created by Paulo Dezingrini on 15/12/2023.
//

#ifndef BRAZILSTRIKERS_GOALKEEPERSTATE_H
#define BRAZILSTRIKERS_GOALKEEPERSTATE_H

#pragma once

#include "../../../Components/AIComponents/FSMState.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Components/RigidBodyComponent.h"
#include "../Character.h"

class GoalKeeperState : FSMState{
public:
    GoalKeeperState(class FSMComponent *fsm, const std::string &name);

    void Start() override;
    void Update(float deltaTime) override;
private:
    const float mMaxDist = 500.0f;
    const float mMinDist = 450.0f;

    class Character* mCharacter;
};


#endif //BRAZILSTRIKERS_GOALKEEPERSTATE_H
