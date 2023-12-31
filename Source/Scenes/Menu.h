//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include "Scene.h"
#include "../Components/DrawComponents/DrawFontComponent.h"
class Menu : public Scene
{
public:
    Menu(class Game* game);

    void Load() override;
    void ProcessInput(const Uint8* keyState) override;
    DrawFontComponent* mDrawComponent;
    void Update(float deltatime, float elapsedTimeSeconds);
    std::unordered_map<bool, int>* GetScore();

private:
    class Font *mMenuFont;
};
