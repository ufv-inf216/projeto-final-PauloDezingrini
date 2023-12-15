//
// Created by Paulo Dezingrini on 30/10/2023.
//

#pragma once

#include <string>
#include "Actor.h"
#include "../Scenes/Scene.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"

class Field : public Actor {
public:
    explicit Field(Scene* scene, float width, float length);
private:
    float mWidth;
    float mLength;

    bool mOnDebug = true;
    AABBColliderComponent * mGoal1 = nullptr;
    AABBColliderComponent * mGoal2 = nullptr;
    DrawSpriteComponent* mDrawComponent;

    void CreateColliders();
};
