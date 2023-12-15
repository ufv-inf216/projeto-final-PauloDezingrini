//
// Created by Paulo Dezingrini on 15/12/2023.
//

#include "ChaseState.h"
#include "../../../Game.h"

const float CHASE_TIME_BLUE = 10.0f;
const float CHASE_TIME_RED = 7.0f;

ChaseState::ChaseState(FSMComponent *fsm, const std::string &name) : FSMState(fsm, name) {
    mCharacter = dynamic_cast<Character *>(fsm->GetOwner());
}

void ChaseState::Update(float deltaTime) {
    Ball* ball = mCharacter->GetGame()->GetBall();

    auto rigidBody = mCharacter->GetComponent<RigidBodyComponent>();

    Vector2 ballVelocity = ball->GetComponent<RigidBodyComponent>()->GetVelocity();
    if (ballVelocity.x != 0 || ballVelocity.y != 0) {
        Vector2 force = Vector2::Normalize(ball->GetPosition() - mCharacter->GetPosition()) * mCharacter->GetForwardSpeed() * 0.75;
        rigidBody->ApplyForce(force);
    }
}

void ChaseState::Start() {
}

void ChaseState::HandleStateTransition(float stateTime) {
    float chaseTime = CHASE_TIME_RED;
    if (mFSM->GetOwner()->GetTeam()) {
        chaseTime = CHASE_TIME_BLUE;
    }

    if (stateTime > chaseTime) {
        mFSM->SetState("position");
    }
}
