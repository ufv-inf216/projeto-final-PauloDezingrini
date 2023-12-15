//
// Created by Paulo Dezingrini on 12/11/2023.
//

#ifndef BRAZILSTRIKERS_CHARACTER_H
#define BRAZILSTRIKERS_CHARACTER_H

#pragma once

#include "../Actor.h"
#include "../../Scenes/Scene.h"
#include "../../Components/DrawComponents/DrawSpriteComponent.h"
#include "../../Components/ColliderComponents/CircleColliderComponent.h"
#include "../../Components/ColliderComponents/AABBColliderComponent.h"
#include <string>

class Character : public Actor {
public:
    explicit Character(Scene* scene, const std::string &name, const std::string &texturePath, bool isPlayer, float size = 64.0f, float forwardSpeed = 1500.0f, float mass = 1.0f);

    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
private:

    bool mIsPlayer;

    float mForwardSpeed;
    float mSize;
    std::string mName;

    RigidBodyComponent* mRigidBodyComponent;
    DrawSpriteComponent* mDrawSpriteComponent;
    CircleColliderComponent* mPlayerColliderComponent;
    CircleColliderComponent* mRadiusColliderComponent;
};

#endif //BRAZILSTRIKERS_CHARACTER_H
