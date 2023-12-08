//
// Created by matheusl on 07/12/23.
//

#ifndef BRAZILSTRIKERS_GAMECLOCK_H
#define BRAZILSTRIKERS_GAMECLOCK_H

#include "Math.h"
#pragma once
#include <SDL.h>
#include "Actors/Actor.h"
#include "./Components/DrawComponents/DrawFontComponent.h"

class GameClock: public Actor {
    private:
        // Maximum time in seconds
        float maxTime;
        float elapsedTimeInSeconds;
        Uint32 lastSecond;

    public:
        GameClock(Game* game, float maxTime, std::string texturePath, int posX, int posY, int width, int height);
        void update(float deltaTime, Uint32 ticks);
        bool isMatchFinished() const;
        float getElapsedTime() const;
        DrawFontComponent* mDrawComponent;
        std::string mTexturePath;
        std::string formatTime(int seconds);

};


#endif //BRAZILSTRIKERS_GAMECLOCK_H
