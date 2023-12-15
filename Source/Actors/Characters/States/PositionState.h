//
// Created by Paulo Dezingrini on 15/12/2023.
//

#ifndef BRAZILSTRIKERS_POSITIONSTATE_H
#define BRAZILSTRIKERS_POSITIONSTATE_H

#pragma once

#include "../../../Components/AIComponents/FSMState.h"
#include "../../../Components/AIComponents/FSMState.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Components/RigidBodyComponent.h"
#include "../Character.h"

class PositionState : public FSMState {
public:
    PositionState(class FSMComponent *fsm, const std::string &name);

    void Start() override;
    void Update(float deltaTime) override;
    void HandleStateTransition(float stateTime) override;
private:
    class Character* mCharacter;
};


#endif //BRAZILSTRIKERS_POSITIONSTATE_H
