//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/ScoreBoard.h"
#include "../Actors/Ball.h"
#include "../Actors/Wall.h"
#include "../GameClock.h"
#include "../Actors/Characters/Character.h"
#include <vector>
#include <string>

class Match : public Scene
{
public:
    Match(class Game* game);
    ~Match();

    void Load() override;
    const Vector2& GetCameraPos() override;
    void Update(float deltaTime, float elapsedTimeSeconds);
    //class HUD *GetHUD() { return mHUD; }

    void ResetMatchState() override;
    Ball * GetBall();
    bool CheckMatchEnded() override;
    virtual bool ScoreReached() const;

    void PlayKickAudio();

private:
    void LoadData(const std::string& fileName);

    class Player *mPlayer;
    //class HUD *mHUD;
    Actor* mMap;
    std::unordered_map<bool, int>* mScore;
    ScoreBoard* mScoreBoard;
    ScoreBoard* teamAScoreBoard;
    ScoreBoard* teamBScoreBoard;
    std::vector<Wall*> mGoals;
    int numPlayersTeam0 = 1;
    int numPlayersTeam1 = 1;
    Ball* mBall;
    std::vector<std::string> spritesBlue;
    std::vector<std::string> spritesRed;
    GameClock * mGameClock;
    int mScoreLimit;
    std::vector<Character*> mCharacters;
};
