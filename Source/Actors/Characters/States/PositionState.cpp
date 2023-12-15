//
// Created by Paulo Dezingrini on 15/12/2023.
//

#include "PositionState.h"
#include "../../../Game.h"

const float POSITION_TIME_BLUE = 5.0f;
const float POSITION_TIME_RED = 9.0f;

PositionState::PositionState(struct FSMComponent *fsm, const std::string &name) : FSMState(fsm, name) {
    mCharacter = dynamic_cast<Character *>(fsm->GetOwner());
}

void PositionState::Start() {

}

void PositionState::Update(float deltaTime) {
    Ball* ball = mCharacter->GetGame()->GetBall();

    auto rigidBody = mCharacter->GetComponent<RigidBodyComponent>();


    Vector2 force = Vector2::Normalize(mCharacter->GetDefaultPosition() - mCharacter->GetPosition()) * mCharacter->GetForwardSpeed() * 0.75;
    rigidBody->ApplyForce(force);
}

void PositionState::HandleStateTransition(float stateTime) {
    float positionTime = POSITION_TIME_BLUE;
    if (mFSM->GetOwner()->GetTeam()) {
        positionTime = POSITION_TIME_RED;
    }

    if (stateTime > positionTime) {
        mFSM->SetState("chase");
    }
}
