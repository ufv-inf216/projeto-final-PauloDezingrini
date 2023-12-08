//
// Created by matheusl on 08/12/23.
//

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(Game *game, std::string texturePath, int posX, int posY, int width, int height, std::string value):
        Actor(game),
        mValue(value)
{
    mDrawComponent = new DrawFontComponent(this, texturePath, posX, posY, width, height, mValue);

}