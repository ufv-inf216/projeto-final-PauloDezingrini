//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include <SDL_stdinc.h>
#include "../Math.h"
//#include "../Actors/Ball.h"
#include <algorithm>

class Scene
{
public:
    Scene(class Game* game);

    virtual void Load();
    virtual void ProcessInput(const Uint8* keyState);
    virtual void Update(float deltatime, float elapsedTimeSeconds);
    //virtual std::unordered_map<bool, int>* GetScore();
    class Game* GetGame() { return mGame; }


    virtual const Vector2& GetCameraPos();
    virtual void ResetMatchState();
    //Ball * GetBall();
    virtual bool CheckMatchEnded();
    virtual bool ScoreReached() const;
    virtual void updateScoreBoard(bool team, int goalNumber);
protected:
    class Game* mGame;
};
