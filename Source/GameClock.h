//
// Created by matheusl on 07/12/23.
//

#ifndef BRAZILSTRIKERS_GAMECLOCK_H
#define BRAZILSTRIKERS_GAMECLOCK_H

#include "Math.h"
#pragma once
#include <SDL.h>
#include "Math.h"

class GameClock {
    private:
        // Maximum time in seconds
        float maxTime;
        float elapsedTimeInSeconds;
        Uint32 lastSecond;

    public:
        GameClock(float maxTime);
        void update(float deltaTime, Uint32 ticks);
        bool isMatchFinished() const;
        float getElapsedTime() const;

};


#endif //BRAZILSTRIKERS_GAMECLOCK_H
