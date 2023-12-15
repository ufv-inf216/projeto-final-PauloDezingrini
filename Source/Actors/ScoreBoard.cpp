//
// Created by matheusl on 08/12/23.
//

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(Scene *scene, std::string texturePath, int posX, int posY, int width, int height, std::string value):
        Actor(scene),
        mValue(value),
        mWidth(width),
        mHeight(height),
        mPosY(posY),
        mPosX(posX),
        texturePath(texturePath)
{
    mDrawComponent = new DrawFontComponent(this, texturePath, posX, posY, width, height, mValue);

}

void ScoreBoard::OnUpdate(float deltaTime) {
    //mDrawComponent = new DrawFontComponent(this, texturePath, mPosX, mPosY, mWidth, mHeight, mValue);
};

void ScoreBoard::updateValue(std::string value) {
    mValue = value;
    mDrawComponent->ResetText(texturePath, mValue);
}