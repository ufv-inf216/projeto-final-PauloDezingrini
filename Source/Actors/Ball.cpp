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

    mColliderComponent = new CircleColliderComponent(this, size/2, true);
//    mColliderComponent = new AABBColliderComponent(this, 0, 0, size, size, ColliderLayer::Goal);

    mRigidBodyComponent = new RigidBodyComponent(this, mass, 1.0f);

    mDrawComponent = new DrawSpriteComponent(this, "../Assets/Sprites/Balls/ball1.png", size, size);

}

void Ball::OnProcessInput(const uint8_t* state)
{

}
