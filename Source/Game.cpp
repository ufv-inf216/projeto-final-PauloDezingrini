// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "SDL_image.h"
#include "Random.h"
#include "Game.h"
#include "Actors/Actor.h"
#include "Actors/Spawner.h"
#include "Components/DrawComponents/DrawComponent.h"
#include "Components/DrawComponents/DrawTileComponent.h"
#include "Components/ColliderComponents/AABBColliderComponent.h"
#include "Actors/Field.h"
#include "Actors/Characters/Character.h"
#include "CSV.h"
#include "Actors/Wall.h"

const int LEVEL_WIDTH = 213;
const int LEVEL_HEIGHT = 14;
const int TILE_SIZE = 32;
const float SPAWN_DISTANCE = 600.0f;

Game::Game(int windowWidth, int windowHeight)
        :mWindow(nullptr)
        ,mRenderer(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
        ,mUpdatingActors(false)
        ,mWindowWidth(windowWidth)
        ,mWindowHeight(windowHeight)
{

}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("P4: Super Mario Bros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    Random::Init();

    mTicksCount = SDL_GetTicks();

    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (1).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (2).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (3).png");

    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (1).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (2).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (3).png");


    // Init all game actors
    InitializeActors();

    return true;
}

void Game::InitializeActors()
{
    mMap = new Actor(this);
    new DrawTileComponent(mMap, "../Assets/Map/map_grass.csv", "../Assets/Map/groundGrass_mown.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_ground.csv", "../Assets/Map/groundGravel.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_elements.csv", "../Assets/Map/elements.png", 1472, 1024, 32, 18);

    LoadData("../Assets/Map/Objects.csv");

//    auto field = new Field(this, 1280, 860);
    //Create an array of players
//     auto player = new Character(this, "Teste", "../Assets/Sprites/Characters/placeholder.png", true);
//     auto player2 = new Character(this, "Teste", "../Assets/Sprites/Characters/placeholder.png", false);

//     player->SetDefaultPosition(Vector2(mWindowWidth/2 - 64, mWindowHeight/2 - 64));
//     player->SetPosition(player->GetDefaultPosition());

//     player2->SetDefaultPosition(Vector2(mWindowWidth/2 - 200, mWindowHeight/2 - 150));
//     player2->SetPosition(player2->GetDefaultPosition());


//     player->setControllable(true);
//     player2->setControllable(true);
// }

void Game::LoadLevel(const std::string& levelPath, const int width, const int height)
{

}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Quit();
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    // Update all actors and pending actors
    UpdateActors(deltaTime);

    // Update camera position
    UpdateCamera();
}

void Game::UpdateCamera()
{

}

void Game::UpdateActors(float deltaTime)
{
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == ActorState::Destroy)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable)
{
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable)
{
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}

void Game::AddCollider(class AABBColliderComponent* collider)
{
    mColliders.emplace_back(collider);
}

void Game::RemoveCollider(AABBColliderComponent* collider)
{
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    mColliders.erase(iter);
}

void Game::AddCollider(class CircleColliderComponent *collider) {
    mCircleColliders.emplace_back(collider);
}

void Game::RemoveCollider(class CircleColliderComponent *collider) {
    auto iter = std::find(mCircleColliders.begin(), mCircleColliders.end(), collider);
    mCircleColliders.erase(iter);
}

void Game::GenerateOutput()
{
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 107, 140, 255, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    for (auto drawable : mDrawables)
    {
        if (drawable->IsVisible())
        {
            drawable->Draw(mRenderer);
        }
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::LoadTexture(const std::string& texturePath) {
    SDL_Surface* image = IMG_Load(texturePath.c_str());
    if (!image) {
        SDL_Log("Erro ao carregar imagem");
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, image);
    SDL_FreeSurface(image);
    if (!texture) {
        return nullptr;
    }
    return texture;
}

void Game::LoadData(const std::string& fileName) {
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
                new Wall(this, x, y, width, height, ColliderLayer::Wall);
            } else if(tiles[0] == "Goal") {
                auto goal = new Wall(this, x, y, width, height, ColliderLayer::Goal, true);
                goal->SetTeam(tiles[5] == "True");
                mGoals.push_back(goal);
            } else if(tiles[0] == "Player") {
                if (tiles[5] == "True") {
                    bool isPlayer = numPlayersTeam > 0;
                    numPlayersTeam--;
                    auto player = new Character(this, "Teste", spritesBlue.back(), tiles[5] == "True", isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    spritesBlue.pop_back();
                } else {
                    bool isPlayer = numPlayersTeam > 0;
                    numPlayersTeam--;
                    auto player = new Character(this, "Teste", spritesRed.back(), tiles[5] == "True", isPlayer, 48);
                    player->SetPosition(Vector2(x, y));
                    spritesRed.pop_back();
                }
            }
            else if(tiles[0] == "Ball") {
                mBall = new Ball(this, 24, 1);
                mBall->SetPosition(Vector2(x,y));
            } else if(tiles[0] == "HUD") {

            }
        }
    }
}

void Game::Shutdown()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ResetMatchState()
{
    //Disable movement for every actor except for the ball
    for (Actor * character: mActors) {
        character->setControllable(false);
    }
    //wait ~2 seconds
    SDL_Delay(2000);

    //reset force on ball
    mBall->SetPosition(Vector2(GetWindowWidth()/2, GetWindowHeight()/2));

    //Reset position for every actor
    for (Actor * character: mActors) {
        character->ResetDefaultPosition();

    }
    SDL_Delay(2000);
    //Enable movement for every player
    for (Actor * character: mActors) {
        character->setControllable(true);
    }
}

Ball * Game::GetBall() {
    return this->mBall;
}