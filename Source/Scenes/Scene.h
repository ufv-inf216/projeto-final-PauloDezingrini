//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include <SDL_stdinc.h>
#include "../Math.h"
#include "../Actors/Ball.h"

class Scene
{
public:
    Scene(class Game* game);

    virtual void Load();
    virtual void ProcessInput(const Uint8* keyState);
    virtual void Update(float deltatime, float elapsedTimeSeconds);
    class Game* GetGame() { return mGame; }

    virtual const Vector2& GetCameraPos();
    void ResetMatchState();
    Ball * GetBall();
    bool CheckMatchEnded();
    bool ScoreReached() const;
    void ScoreGoal(bool team);
protected:
    class Game* mGame;
};
