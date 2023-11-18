//
// Created by Paulo Dezingrini on 30/10/2023.
//

#pragma once

#include <string>
#include "Actor.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"

class Field : public Actor {
public:
    explicit Field(Game* game, float width, float length);
private:
    float mWidth;
    float mLength;

    bool mOnDebug = true;

    DrawSpriteComponent* mDrawComponent;

    void CreateColliders();
    void OnUpdate(float deltaTime) override;
    void HandleGoal(bool team);
};
