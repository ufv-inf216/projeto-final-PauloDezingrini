//
// Created by matheusl on 07/12/23.
//

#include "GameClock.h"
#include <SDL.h>
#include <sstream>
#include <iomanip>
GameClock::GameClock(Scene* scene, float maxTime, std::string texturePath, int posX, int posY, int width, int height) :
        Actor(scene),
        maxTime(maxTime),
        elapsedTimeInSeconds(0.0f),
        mTexturePath(texturePath)
{

    mDrawComponent = new DrawFontComponent(this, texturePath, posX, posY, width, height, std::to_string(elapsedTimeInSeconds));

}

void GameClock::update(float deltaTime, Uint32 ticks) {
    elapsedTimeInSeconds += deltaTime;

    if (ticks / 1000 != lastSecond) {
        lastSecond = ticks / 1000;

        mDrawComponent->ResetText(mTexturePath, formatTime(floor(elapsedTimeInSeconds)));
    }
}

bool GameClock::isMatchFinished() const {
    return elapsedTimeInSeconds >= (maxTime * 60);
}
std::string GameClock::formatTime(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;


    std::ostringstream formattedTime;
    formattedTime << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << remainingSeconds;

    return formattedTime.str();
}