//
// Created by Paulo Dezingrini on 12/11/2023.
//
#pragma once
#ifndef BRAZILSTRIKERS_BALL_H
#define BRAZILSTRIKERS_BALL_H
#include "Actor.h"
#include "../Scenes/Scene.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/ColliderComponents/CircleColliderComponent.h"

class Ball : public Actor {
public:
    explicit Ball(Scene* scene, float size, float mass);

    void OnProcessInput(const Uint8* keyState) override;
private:
    float mSize;
    float mForwardSpeed = 3000.0f;

    CircleColliderComponent* mColliderComponent;
//    AABBColliderComponent* mColliderComponent;
    RigidBodyComponent* mRigidBodyComponent;
    DrawSpriteComponent* mDrawComponent;
};


#endif //BRAZILSTRIKERS_BALL_H
