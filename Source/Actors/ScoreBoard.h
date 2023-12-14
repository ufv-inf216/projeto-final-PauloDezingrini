//
// Created by matheusl on 08/12/23.
//

#ifndef BRAZILSTRIKERS_SCOREBOARD_H
#define BRAZILSTRIKERS_SCOREBOARD_H

#include "../Components/DrawComponents/DrawFontComponent.h"
#include "Actor.h"
#include <string>
class ScoreBoard: Actor {
    public:
        explicit ScoreBoard(Game* game, std::string texturePath, int posX, int posY, int width, int height, std::string value);
        void OnUpdate(float deltaTime) override;
        void updateValue(std::string value);
    private:
    DrawFontComponent* mDrawComponent;
    std::string mValue;
    int mPosX, mPosY, mWidth, mHeight;
    std::string texturePath;
};

#endif //BRAZILSTRIKERS_SCOREBOARD_H
