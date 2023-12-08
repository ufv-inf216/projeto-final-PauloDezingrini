//
// Created by matheusl on 07/12/23.
//

#include "GameClock.h"
#include <SDL.h>
GameClock::GameClock(Game* game, float maxTime, std::string texturePath, int posX, int posY, int width, int height) :
        Actor(game),
        maxTime(maxTime),
        elapsedTimeInSeconds(0.0f)
{

    mDrawComponent = new DrawFontComponent(this, texturePath, posX, posY, width, height, std::to_string(elapsedTimeInSeconds));

}

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