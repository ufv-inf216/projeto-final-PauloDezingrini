//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "Match.h"
#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include "../CSV.h"
#include "../Game.h"
#include "../Actors/Characters/Character.h"
#include "../Actors/Wall.h"
//#include "../HUD.h"
#include "../Components/DrawComponents/DrawTileComponent.h"

Match::Match(Game* game, int valorA, int valorB)
          :Scene(game)
          ,mPlayer(nullptr),
           mScoreLimit(3)
           ,valorA(valorA)
           ,valorB(valorB)
{
    mScore = new std::unordered_map<bool, int>();
}

Match::~Match()
{
    //delete mHUD;
}

void Match::Load()
{
    /*
    // Background
    auto* map = new Actor(mGame);
    new DrawTileComponent(map, "../Assets/Map/Tiles.csv",
                                     "../Assets/Map/Tiles.png",
                                     576, 576, 32);

    // Game Objects
    LoadData("../Assets/Map/ObjectsOneSoldier.csv");

    // Init HUD
    //mHUD = new HUD(this);

    // Play background music
    mGame->GetAudio()->PlaySound("MusicLoop.ogg", true);*/
    mGameClock = new GameClock(this, 2, "../Assets/Fonts/bruder/BRUDER.ttf", 680, 5, 100, 80);
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (1).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (2).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (10).png");

    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (1).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (2).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (10).png");

    mMap = new Actor(this);
    new DrawTileComponent(mMap, "../Assets/Map/map_grass.csv", "../Assets/Map/groundGrass_mown.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_ground.csv", "../Assets/Map/groundGravel.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_elements.csv", "../Assets/Map/elements.png", 1472, 1024, 32, 18);

    LoadData("../Assets/Map/Objects.csv");

    mScore->insert(std::make_pair<bool, int>(true, 0));
    mScore->insert(std::make_pair<bool, int>(false, 0));
    mScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 600, 928, 300, 100, "Brazil Strikers");
    teamAScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 1280, 10, 150, 65, std::to_string(valorA));
    teamBScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 25, 10, 150, 65, std::to_string(valorB));
}

void Match::LoadData(const std::string& fileName)
{

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        SDL_Log("Failed to load paths: %s", fileName.c_str());
    }

    int row = 0;
    bool GOL= false;
    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);

        if(!line.empty())
        {
            auto tiles = CSVHelper::Split(line);

            if(tiles[0] == "Type") {
                continue;
            }

            int x = std::stoi(tiles[1]) - 16;
            int y = std::stoi(tiles[2]) - 16;
            int width = std::stoi(tiles[3]);
            int height = std::stoi(tiles[4]);
            if(tiles[0] == "Wall") {
                new Wall(this, x, y, width, height, ColliderLayer::Wall);
            } else if(tiles[0] == "Goal") {
                auto goal = new Wall(this, x, y, width, height, ColliderLayer::Goal, true);
                goal->SetTeam(GOL);
                GOL = !GOL;
                mGoals.push_back(goal);
            } else if(tiles[0] == "Player") {
                if (tiles[5] == "True") {
                    bool isPlayer = numPlayersTeam0 > 0;
                    numPlayersTeam0--;
                    auto player = new Character(this, "Player0", spritesBlue.back(),  isPlayer, 48, tiles[6] == "True", 600);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesBlue.pop_back();
                } else {
                    bool isPlayer = numPlayersTeam1 > 0;
                    numPlayersTeam1--;
                    auto player = new Character(this, "Player1", spritesRed.back(), isPlayer, 48,  tiles[6] == "True", 600);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    player->SetRotation(1);
                    spritesRed.pop_back();
                }
            }
            else if(tiles[0] == "Ball") {
                //mBall = new Ball(this, 24, 1);
                this->GetGame()->mBall = new Ball(this, 24, 1);
                this->GetGame()->mBall->SetPosition(Vector2(x,y));
                this->GetGame()->mBall->SetDefaultPosition(this->GetGame()->mBall->GetPosition());
            } else if(tiles[0] == "HUD") {

            }
        }
    }
}

const Vector2& Match::GetCameraPos()
{
    //return mPlayer->GetPosition();
}

void Match::ResetMatchState()
{

    //Disable movement for every actor except for the ball
    for (Actor * character: mGame->mActors) {
        character->SetControllable(false);
    }
    //wait ~2 seconds
    SDL_Delay(2000);

    //auto rigidBody = mBall->GetComponent<RigidBodyComponent>();
    auto rigidBody = this->GetGame()->mBall->GetComponent<RigidBodyComponent>();
    rigidBody->SetVelocity(Vector2::Zero);
    rigidBody->SetAcceleration(Vector2::Zero);
    this->GetGame()->mBall->ResetDefaultPosition();

    //Reset position for every actor
    for (Actor * actor: mGame->mActors) {
        actor->ResetDefaultPosition();
    }
    SDL_Delay(2000);
    //Enable movement for every player
    for (Actor * character: mGame->mActors) {
        character->SetControllable(true);
    }


}

/*
Ball * Match::GetBall() {
    return this->mBall;
}
*/


bool Match::ScoreReached() const {
    return ((*mScore)[true] == mScoreLimit) || ((*mScore)[false] == mScoreLimit);
}
bool Match::CheckMatchEnded() {

    return mGameClock->isMatchFinished() || ScoreReached();
}
void Match::Update(float deltaTime, float elapsedTimeSeconds) {
    auto ticks = SDL_GetTicks();
    //elapsedTimeSeconds = ((float)ticks - startTime) / 1000.0f;
    //startTime = ticks;

    mGameClock->update(elapsedTimeSeconds, ticks);
    // Check if the match is finished(by time or goals)
    if (CheckMatchEnded()) {
        SDL_Log("The match is finished!");
        //Play sound effect
        mGame->Shutdown();
    }
}

void Match::updateScoreBoard(bool team, int goalNumber){

    if(team) {
        SDL_Log("true");
        teamAScoreBoard->updateValue(std::to_string(goalNumber));
    } else {
        SDL_Log("false");
        teamBScoreBoard->updateValue(std::to_string(goalNumber));
    }
}