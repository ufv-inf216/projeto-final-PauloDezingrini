//
// Created by matheusl on 07/12/23.
//

#include "GameClock.h"
#include <SDL.h>
GameClock::GameClock(float maxTime) : maxTime(maxTime), elapsedTimeInSeconds(0.0f) {}

void GameClock::update(float deltaTime, Uint32 ticks) {
    elapsedTimeInSeconds += deltaTime;

    if (ticks / 1000 != lastSecond) {
        lastSecond = ticks / 1000;
        SDL_Log("Seconds: %f", floor(elapsedTimeInSeconds));
    }
}

bool GameClock::isMatchFinished() const {
    return elapsedTimeInSeconds >= (maxTime * 60);
}

float GameClock::getElapsedTime() const {
    return elapsedTimeInSeconds;
}