//
// Created by Paulo Dezingrini on 12/11/2023.
//

#include "Character.h"
#include "../../Game.h"

Character::Character(Game* game, const std::string &name, const std::string &texturePath, bool isPlayer, float size, float forwardSpeed, float mass)
        :Actor(game)
        ,mName(name)
        ,mForwardSpeed(forwardSpeed)
        ,mSize(size)
        ,mIsPlayer(isPlayer)
{
    SetControllable(isPlayer);

    mRigidBodyComponent = new RigidBodyComponent(this, mass, 2.0f);
    mDrawSpriteComponent = new DrawSpriteComponent(this, texturePath, 21, 31);
//    mPlayerColliderComponent = new AABBColliderComponent(this, 0, 0, 64, 64, ColliderLayer::Player);
    mPlayerColliderComponent = new CircleColliderComponent(this, 31/2);
}

void Character::OnProcessInput(const uint8_t* state)
{
    if (!GetControllable()) {
        return;
    }

    if (mIsPlayer) {

         if (state[SDL_SCANCODE_D] && this->mName == "Player0" || state[SDL_SCANCODE_RIGHT] && this->mName == "Player1") {
            mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed, 0));
        } else if (state[SDL_SCANCODE_A] && this->mName == "Player0" || state[SDL_SCANCODE_LEFT] && this->mName == "Player1"){
            mRigidBodyComponent->ApplyForce(Vector2(-mForwardSpeed, 0));
        }

        if (state[SDL_SCANCODE_W] && this->mName == "Player0" || state[SDL_SCANCODE_UP] && this->mName == "Player1") {
            mRigidBodyComponent->ApplyForce(Vector2(0, -mForwardSpeed));
        } else if (state[SDL_SCANCODE_S] && this->mName == "Player0" || state[SDL_SCANCODE_DOWN] && this->mName == "Player1"){
            mRigidBodyComponent->ApplyForce(Vector2(0, mForwardSpeed));
        }
    }
}

void Character::OnUpdate(float deltaTime)
{

}