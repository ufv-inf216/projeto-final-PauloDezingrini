//
// Created by Paulo Dezingrini on 12/11/2023.
//

#include "Character.h"
#include "../../Game.h"
#include "States/GoalKeeperState.h"
#include "States/ChaseState.h"
#include "States/PositionState.h"

Character::Character(Game* game, const std::string &name, const std::string &texturePath, bool isPlayer, float size, float forwardSpeed, bool isGoalkeeper, float mass)
        :Actor(game)
        ,mName(name)
        ,mForwardSpeed(forwardSpeed)
        ,mSize(size)
        ,mIsPlayer(isPlayer)
        ,mIsGoalKeeper(isGoalkeeper)
{
    const float width = 31;
    const float height = 46;
    SetControllable(isPlayer);

    mRigidBodyComponent = new RigidBodyComponent(this, mass, 2.0f);
    mDrawSpriteComponent = new DrawSpriteComponent(this, texturePath, width, height);
//    mPlayerColliderComponent = new AABBColliderComponent(this, 0, 0, 64, 64, ColliderLayer::Player);
    mPlayerColliderComponent = new CircleColliderComponent(this, (width + height) / 4, false);
//    mRadiusColliderComponent = new CircleColliderComponent(this, ((width + height) / 4) * 2.5, false, true);

    mFsmComponent = nullptr;
    if (!isPlayer) {
        mFsmComponent = new FSMComponent(this);
        if (isGoalkeeper) {
            new GoalKeeperState(mFsmComponent, "goalkeeper");
            mFsmComponent->Start("goalkeeper");
        } else {
            new ChaseState(mFsmComponent, "chase");
            new PositionState(mFsmComponent, "position");
            mFsmComponent->Start("chase");
        }
    }
}

void Character::OnProcessInput(const uint8_t* state)
{
//    if (!GetControllable()) {
//        return;
//    }

    if (mIsPlayer) {
        mRigidBodyComponent->SetAcceleration(Vector2::Zero);
         if (state[SDL_SCANCODE_D] && this->mName == "Player0" || state[SDL_SCANCODE_RIGHT] && this->mName == "Player1") {
            mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed, 0));
            SetRotation(0);
        } else if (state[SDL_SCANCODE_A] && this->mName == "Player0" || state[SDL_SCANCODE_LEFT] && this->mName == "Player1"){
            mRigidBodyComponent->ApplyForce(Vector2(-mForwardSpeed, 0));
            SetRotation(1);
        }

        if (state[SDL_SCANCODE_W] && this->mName == "Player0" || state[SDL_SCANCODE_UP] && this->mName == "Player1") {
            mRigidBodyComponent->ApplyForce(Vector2(0, -mForwardSpeed));
        } else if (state[SDL_SCANCODE_S] && this->mName == "Player0" || state[SDL_SCANCODE_DOWN] && this->mName == "Player1"){
            mRigidBodyComponent->ApplyForce(Vector2(0, mForwardSpeed));
        }

//        Ball* ball = mGame->GetBall();
////        if (state[SDL_SCANCODE_SPACE] && mRadiusColliderComponent->Intersect(*ball->GetComponent<CircleColliderComponent>()) && mName == "Player0") {
////            Vector2 kick = mGame->GetGoals()[1]->GetPosition() + mRigidBodyComponent->GetVelocity();
////            kick.Normalize();
////            ball->GetComponent<RigidBodyComponent>()->ApplyForce(kick * mForwardSpeed * 3.5);
////
////            mGame->PlayKickAudio();
////        }
        return;
    }
    if (mIsGoalKeeper && mFsmComponent->GetState()->GetName() == "start") {
        mFsmComponent->SetState("goalkeeper");
    }
}

void Character::OnUpdate(float deltaTime)
{

}