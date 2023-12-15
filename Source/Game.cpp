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
#include "GameClock.h"
#include "Actors/ScoreBoard.h"
#include "SDL_ttf.h"
#include <string>

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
        ,mScoreLimit(3)
{
    mScore = new std::unordered_map<bool, int>();

}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Brazil Strikers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, 0);
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

    mAudio = new AudioSystem();
    if(TTF_Init() == -1){
        SDL_Log("Could not initailize SDL2_ttf, error: %s", TTF_GetError());
    }

    Random::Init();

    mGameClock = new GameClock(this, 2, "../Assets/Fonts/bruder/BRUDER.ttf", 680, 5, 100, 80);
    mTicksCount = SDL_GetTicks();
    startTime = SDL_GetTicks();

    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (1).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (2).png");
    spritesRed.push_back("../Assets/Sprites/Characters/Red/characterRed (10).png");

    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (1).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (2).png");
    spritesBlue.push_back("../Assets/Sprites/Characters/Blue/characterBlue (10).png");

    // Play background music
    mAudio->PlaySound("Torcida.wav", true);

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

    mScore->insert(std::make_pair<bool, int>(true, 0));
    mScore->insert(std::make_pair<bool, int>(false, 0));
    mScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 600, 928, 300, 100, "Brazil Strikers");
    teamAScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 1280, 10, 150, 65, std::to_string((*mScore)[false]));
    teamBScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 25, 10, 150, 65, std::to_string((*mScore)[true]));

}

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

SDL_GameController *Game::findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            return SDL_GameControllerOpen(i);
        }
    }

    return nullptr;
}

std::vector<SDL_GameController*> Game::findControllers() {
    std::vector<SDL_GameController*> controllers;

    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            controllers.push_back(SDL_GameControllerOpen(i));
        }
    }

    return controllers;
}

SDL_JoystickID Game::getControllerInstanceID(SDL_GameController *controller) {
    return SDL_JoystickInstanceID(
            SDL_GameControllerGetJoystick(controller));
}

void Game::ProcessInput() {
    std::vector<SDL_GameController *> controllers = findControllers();

    SDL_Event event;

    if (controllers.empty()) { //caso nao tenha controle, processar comandos de teclado
//        std::cout << "Nenhum controle encontrado" << std::endl;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Quit();
                    break;
            }
        }
        const Uint8 *state = SDL_GetKeyboardState(nullptr);

        mAudio->ProcessInput(state);

        for (auto actor: mActors) {

            actor->ProcessInput(state);
        }

        return;

    }

    for (auto controller: controllers) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Quit();
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    if (!controller) {
                        controller = SDL_GameControllerOpen(event.cdevice.which);
                    }
                    break;
                case SDL_CONTROLLERDEVICEREMOVED:
                    if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                        SDL_GameControllerClose(controller);
                        controller = findController();
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN: //caso tenha apertado um botão, chamar actor->ProcessInput()
                    if (controller && event.cdevice.which == getControllerInstanceID(controller)) {
                        for (auto actor: mActors) {

                            //actor->ProcessInput();
                        }
                    }
            }

        }
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

    mAudio->Update(deltaTime);

    mTicksCount = SDL_GetTicks();
    // Update the game clock

    mTicksCount = SDL_GetTicks();
    elapsedTimeSeconds = ((float)mTicksCount - startTime) / 1000.0f;
    startTime = mTicksCount;

    mGameClock->update(elapsedTimeSeconds, mTicksCount);
    // Check if the match is finished(by time or goals)
    if (CheckMatchEnded()) {
        std::cout << "The match is finished!" << std::endl;
        //Play sound effect
        Shutdown();
    }
    // Update all actors and pending actors
    UpdateActors(deltaTime);

    audioCooldown -= deltaTime;
    if (audioCooldown < 0.0f) {
        audioCooldown = 0.0f;
    }

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
SDL_Texture* Game::LoadFontTexture(const std::string& texturePath, const std::string& text){

    TTF_Font* ourFont = TTF_OpenFont(texturePath.c_str(), 200);
    if(ourFont == nullptr){
        SDL_Log("Could not load font");
        exit(1);
    }
    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont, text.c_str(),{255,255,255});

    SDL_Texture* textureText = SDL_CreateTextureFromSurface(mRenderer,surfaceText);
    SDL_FreeSurface(surfaceText);
    return textureText;
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
                    bool isPlayer = numPlayersTeam0 > 0;
                    numPlayersTeam0--;
                    auto player = new Character(this, "Player0", spritesBlue.back(),  isPlayer, 48, 600, tiles[6] == "True");
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    spritesBlue.pop_back();
                } else {
                    bool isPlayer = numPlayersTeam1 > 0;
                    numPlayersTeam1--;
                    auto player = new Character(this, "Player1", spritesRed.back(), isPlayer, 48, 600, tiles[6] == "True");
                    player->SetPosition(Vector2(x, y));
                    player->SetDefaultPosition(player->GetPosition());
                    player->SetTeam(tiles[5] == "True");
                    player->SetRotation(1.0);
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
    Quit();
}

void Game::ResetMatchState()
{
    //Disable movement for every actor except for the ball
    for (Actor * character: mActors) {
        character->SetControllable(false);
    }
    //wait ~2 seconds
    SDL_Delay(2000);

    auto rigidBody = mBall->GetComponent<RigidBodyComponent>();
    rigidBody->SetVelocity(Vector2::Zero);
    rigidBody->SetAcceleration(Vector2::Zero);
    mBall->ResetDefaultPosition();

    //Reset position for every actor
    for (Actor * actor: mActors) {
        actor->ResetDefaultPosition();
    }
    SDL_Delay(2000);
    //Enable movement for every player
    for (Actor * character: mActors) {
        character->SetControllable(true);
    }


}

Ball * Game::GetBall() {
    return this->mBall;
}

void Game::PlayKickAudio() {
    if (audioCooldown <= 0.0f) {
        GetAudio()->PlaySound("Kick.wav");
        audioCooldown = audioCooldownTime; // Reiniciar o cooldown
    }

}

void Game::ScoreGoal(bool team) {
    if (team) {
        (*mScore)[team] += 1;
        teamAScoreBoard->updateValue(std::to_string((*mScore)[team]));
    } else {
        (*mScore)[team] += 1;
        teamBScoreBoard->updateValue(std::to_string((*mScore)[team]));
    }

}

bool Game::ScoreReached() const {
    return ((*mScore)[true] == mScoreLimit) || ((*mScore)[false] == mScoreLimit);
}
bool Game::CheckMatchEnded() {

    return mGameClock->isMatchFinished() || ScoreReached();
}

