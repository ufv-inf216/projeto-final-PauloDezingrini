//
// Created by matheusl on 08/12/23.
//

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(Game *game, std::string texturePath):
        Actor(game)
{
    mDrawComponent = new DrawFontComponent(this, texturePath, 100);

}