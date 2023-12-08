//
// Created by matheusl on 08/12/23.
//

#ifndef BRAZILSTRIKERS_SCOREBOARD_H
#define BRAZILSTRIKERS_SCOREBOARD_H

#include "../Components/DrawComponents/DrawFontComponent.h"
#include "Actor.h"
class ScoreBoard: Actor {
    public:
        explicit ScoreBoard(Game* game, std::string texturePath);
    private:
    DrawFontComponent* mDrawComponent;
};


#endif //BRAZILSTRIKERS_SCOREBOARD_H
