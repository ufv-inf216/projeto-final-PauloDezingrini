//
// Created by Paulo Dezingrini on 12/11/2023.
//

#include "Character.h"
#include "../../Game.h"

Character::Character(Game* game, const std::string &name, const std::string &texturePath, bool team, float forwardSpeed, float mass, float size)
        :Actor(game)
        ,mName(name)
        ,mTeam(team)
        ,mForwardSpeed(forwardSpeed)
        ,mSize(size)
{
    mRigidBodyComponent = new RigidBodyComponent(this, mass);
    mDrawSpriteComponent = new DrawSpriteComponent(this, texturePath, mSize, mSize);
    mPlayerColliderComponent = new AABBColliderComponent(this, 0, 0, 64, 64, ColliderLayer::Player);
}

void Character::OnProcessInput(const uint8_t* state)
{
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

void Character::OnUpdate(float deltaTime)
{

}