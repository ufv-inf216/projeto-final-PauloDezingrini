//
// Created by Paulo Dezingrini on 12/11/2023.
//

#include "Character.h"
#include "../../Game.h"

Character::Character(Game* game, const std::string &name, const std::string &texturePath, bool team, bool isPlayer, float size, float forwardSpeed, float mass)
        :Actor(game)
        ,mName(name)
        ,mTeam(team)
        ,mForwardSpeed(forwardSpeed)
        ,mSize(size)
        ,mIsPlayer(isPlayer)
{
    int width = mSize * 21/32;

    mRigidBodyComponent = new RigidBodyComponent(this, mass, 2.0f);
    mDrawSpriteComponent = new DrawSpriteComponent(this, texturePath, 21, 31);
//    mPlayerColliderComponent = new AABBColliderComponent(this, 0, 0, 64, 64, ColliderLayer::Player);
    mPlayerColliderComponent = new CircleColliderComponent(this, size/2);
}

void Character::OnProcessInput(const uint8_t* state)
{
    if (mIsPlayer) {

        if (state[SDL_SCANCODE_D]) {
            mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed, 0));
        } else if (state[SDL_SCANCODE_A]){
            mRigidBodyComponent->ApplyForce(Vector2(-mForwardSpeed, 0));
        }

        if (state[SDL_SCANCODE_W]) {
            mRigidBodyComponent->ApplyForce(Vector2(0, -mForwardSpeed));
        } else if (state[SDL_SCANCODE_S]){
            mRigidBodyComponent->ApplyForce(Vector2(0, mForwardSpeed));
        }
    }
}

void Character::OnUpdate(float deltaTime)
{

}