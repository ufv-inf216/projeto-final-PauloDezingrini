//
// Created by Paulo Dezingrini on 12/11/2023.
//

#include "Ball.h"
#include <vector>
#include "../Game.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"


Ball::Ball(Game *game, float size, float mass):
    Actor(game),
    mSize(size)
{
    SetPosition(Vector2(game->GetWindowWidth()/2, game->GetWindowHeight()/2));

//    mColliderComponent = new CircleColliderComponent(this, size);
    mColliderComponent = new AABBColliderComponent(this, 0, 0, size, size, ColliderLayer::Goal);

    mRigidBodyComponent = new RigidBodyComponent(this, mass);

    mDrawComponent = new DrawSpriteComponent(this, "../Assets/Sprites/Balls/ball1.png", size, size);

}

void Ball::OnProcessInput(const uint8_t* state)
{
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
