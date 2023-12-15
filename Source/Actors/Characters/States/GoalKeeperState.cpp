//
// Created by Paulo Dezingrini on 15/12/2023.
//

#include "GoalKeeperState.h"
#include "../../../Game.h"
#include "../../../Actors/Wall.h"

GoalKeeperState::GoalKeeperState(class FSMComponent *fsm, const std::string &name)
        : FSMState(fsm, name) {
    mCharacter = dynamic_cast<Character *>(fsm->GetOwner());
}

void GoalKeeperState::Update(float deltaTime) {
    Ball* ball = mCharacter->GetGame()->GetBall();

    auto rigidBody = mCharacter->GetComponent<RigidBodyComponent>();

    Vector2 ballVelocity = ball->GetComponent<RigidBodyComponent>()->GetVelocity();
    if (ballVelocity.x != 0 || ballVelocity.y != 0) {

        Vector2 playerBallDist = ball->GetPosition() - mCharacter->GetPosition();
        Vector2 force = Vector2::Normalize(playerBallDist) * mCharacter->GetForwardSpeed() * 0.5;
        force.x = 0;

        rigidBody->ApplyForce(force);
    }
}

void GoalKeeperState::Start() {
}
