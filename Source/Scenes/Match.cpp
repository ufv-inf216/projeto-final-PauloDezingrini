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

Match::Match(Game* game)
          :Scene(game)
          ,mPlayer(nullptr),
           mScoreLimit(3)
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
    mGameClock = new GameClock(mGame, 2, "../Assets/Fonts/bruder/BRUDER.ttf", 680, 5, 100, 80);
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (1).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (2).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (3).png");

    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (1).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (2).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (3).png");

    mMap = new Actor(mGame);
    new DrawTileComponent(mMap, "../Assets/Map/map_grass.csv", "../Assets/Map/groundGrass_mown.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_ground.csv", "../Assets/Map/groundGravel.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_elements.csv", "../Assets/Map/elements.png", 1472, 1024, 32, 18);

    LoadData("../Assets/Map/Objects.csv");

    mScore->insert(std::make_pair<bool, int>(true, 0));
    mScore->insert(std::make_pair<bool, int>(false, 0));
    mScoreBoard = new ScoreBoard(mGame, "../Assets/Fonts/bruder/BRUDER.ttf", 600, 928, 300, 100, "Brazil Strikers");
    teamAScoreBoard = new ScoreBoard(mGame, "../Assets/Fonts/bruder/BRUDER.ttf", 1280, 10, 150, 65, std::to_string((*mScore)[false]));
    teamBScoreBoard = new ScoreBoard(mGame, "../Assets/Fonts/bruder/BRUDER.ttf", 25, 10, 150, 65, std::to_string((*mScore)[true]));
}

void Match::LoadData(const std::string& fileName)
{
    /*std::ifstream file(fileName);
    if (!file.is_open())
    {
        SDL_Log("Failed to load paths: %s", fileName.c_str());
    }

    int row = 0;

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

            int x = std::stoi(tiles[1]);
            int y = std::stoi(tiles[2]);
            int width = std::stoi(tiles[3]);
            int height = std::stoi(tiles[4]);

            if(tiles[0] == "Player")
            {
                mPlayer = new Player(this);
                mPlayer->SetPosition(Vector2(x + width/2.0f, y + height/2.0));
            }
            else if(tiles[0] == "Collider")
            {
                auto *wall = new Wall(this, width, height);
                wall->SetPosition(Vector2(x + width/2.0f, y + height/2.0));
            }
            else if(tiles[0] == "Bush")
            {
                auto *bush = new Bush(this);
                bush->SetPosition(Vector2(x + width/2.0f, y + height/2.0));
            }std::ifstream file(fileName);
    if (!file.is_open())
    {
        SDL_Log("Failed to load paths: %s", fileName.c_str());
    }

    int row = 0;

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
                goal->SetTeam(tiles[5] == "True");
                mGoals.push_back(goal);
            } else if(tiles[0] == "Player") {
                if (tiles[5] == "True") {
                    bool isPlayer = numPlayersTeam0 > 0;
                    numPlayersTeam0--;
                    auto player = new Character(this, "Player0", spritesBlue.back(),  isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesBlue.pop_back();
                } else {
                    bool isPlayer = numPlayersTeam1 > 0;
                    numPlayersTeam1--;
                    auto player = new Character(this, "Player1", spritesRed.back(), isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesRed.pop_back();
                }
            }
            else if(tiles[0] == "Ball") {
                mBall = new Ball(this, 24, 1);
                mBall->SetPosition(Vector2(x,y));
                mBall->SetDefaultPosition(mBall->GetPosition());
            } else if(tiles[0] == "HUD") {

            }
        }
    }
            else if(tiles[0] == "Soldier")
            {
                auto *soldier = new Soldier(this, 10.0f);
                soldier->SetPosition(Vector2(x + width/2.0f, y + height/2.0));
            }
        }
    }*/
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        SDL_Log("Failed to load paths: %s", fileName.c_str());
    }

    int row = 0;

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
                new Wall(mGame, x, y, width, height, ColliderLayer::Wall);
            } else if(tiles[0] == "Goal") {
                auto goal = new Wall(mGame, x, y, width, height, ColliderLayer::Goal, true);
                goal->SetTeam(tiles[5] == "True");
                mGoals.push_back(goal);
            } else if(tiles[0] == "Player") {
                if (tiles[5] == "True") {
                    bool isPlayer = numPlayersTeam0 > 0;
                    numPlayersTeam0--;
                    auto player = new Character(mGame, "Player0", spritesBlue.back(),  isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesBlue.pop_back();
                } else {
                    bool isPlayer = numPlayersTeam1 > 0;
                    numPlayersTeam1--;
                    auto player = new Character(mGame, "Player1", spritesRed.back(), isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesRed.pop_back();
                }
            }
            else if(tiles[0] == "Ball") {
                mBall = new Ball(mGame, 24, 1);
                mBall->SetPosition(Vector2(x,y));
                mBall->SetDefaultPosition(mBall->GetPosition());
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

    auto rigidBody = mBall->GetComponent<RigidBodyComponent>();
    rigidBody->SetVelocity(Vector2::Zero);
    rigidBody->SetAcceleration(Vector2::Zero);
    mBall->ResetDefaultPosition();

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

Ball * Match::GetBall() {
    return this->mBall;
}

void Match::ScoreGoal(bool team) {
    if (team) {
        (*mScore)[team] += 1;
        teamAScoreBoard->updateValue(std::to_string((*mScore)[team]));
    } else {
        (*mScore)[team] += 1;
        teamBScoreBoard->updateValue(std::to_string((*mScore)[team]));
    }

}

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