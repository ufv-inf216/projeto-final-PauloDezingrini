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
#include "SDL2/SDL_ttf.h"
#include "Scenes/Menu.h"
#include "Scenes/Match.h"
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
        ,mFadeState(FadeState::None)
        ,mSceneTransitionTime(0.0f)
        ,mWindowWidth(windowWidth)
        ,mWindowHeight(windowHeight)
        ,mGameState(GameScene::Menu)
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

    //mGameClock = new GameClock(this, 2, "../Assets/Fonts/bruder/BRUDER.ttf", 680, 5, 100, 80);
    mTicksCount = SDL_GetTicks();
    startTime = SDL_GetTicks();

    // Play background music
    mAudio->PlaySound("Torcida.wav", true);

    // Init all game actors
    InitializeActors();
    return true;
}

void Game::InitializeActors()
{
    switch (mGameState)
    {
        case GameScene::Menu:
            mScene = new Menu(this);
            mScene->Load();
            break;

        case GameScene::Match:
          mScene = new Match(this);
          mScene->Load();
          break;
        default:
            break;
    }
    /////////////////////////////////////////////////////////
    /*mMap = new Actor(this);
    new DrawTileComponent(mMap, "../Assets/Map/map_grass.csv", "../Assets/Map/groundGrass_mown.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_ground.csv", "../Assets/Map/groundGravel.png", 1472, 1024, 32, 26);
    new DrawTileComponent(mMap, "../Assets/Map/map_elements.csv", "../Assets/Map/elements.png", 1472, 1024, 32, 18);

    LoadData("../Assets/Map/Objects.csv");

    mScore->insert(std::make_pair<bool, int>(true, 0));
    mScore->insert(std::make_pair<bool, int>(false, 0));
    mScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 600, 928, 300, 100, "Brazil Strikers");
    teamAScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 1280, 10, 150, 65, std::to_string((*mScore)[false]));
    teamBScoreBoard = new ScoreBoard(this, "../Assets/Fonts/bruder/BRUDER.ttf", 25, 10, 150, 65, std::to_string((*mScore)[true]));
*/
}
void Game::SetScene(GameScene gameState)
{
    // Stop all sounds
    mAudio->StopAllSounds();
    mFadeState = FadeState::FadeOut;

    // Handle scene transition
    mGameState = gameState;
    //UnloadActors();
    //InitializeActors();
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
        mScene->ProcessInput(state);
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

    //mGameClock->update(elapsedTimeSeconds, mTicksCount);
    mScene->Update(deltaTime, elapsedTimeSeconds);
    // Check if the match is finished(by time or goals)
    /*if (mScene->CheckMatchEnded()) {
        std::cout << "The match is finished!" << std::endl;
        //Play sound effect
        Shutdown();
    }*/
    // Update all actors and pending actors
    UpdateActors(deltaTime);

    audioCooldown -= deltaTime;
    if (audioCooldown < 0.0f) {
        audioCooldown = 0.0f;
    }

    // Update camera position
    UpdateCamera();
    if (mFadeState == FadeState::FadeOut)
    {
        mSceneTransitionTime += deltaTime;
        if (mSceneTransitionTime >= SCENE_TRANSITION_TIME)
        {
            mSceneTransitionTime = 0.0f;
            mFadeState = FadeState::FadeIn;

            UnloadActors();
            InitializeActors();
        }
    }
    else if (mFadeState == FadeState::FadeIn)
    {
        mSceneTransitionTime += deltaTime;
        if (mSceneTransitionTime >= SCENE_TRANSITION_TIME)
        {
            mFadeState = FadeState::None;
            mSceneTransitionTime = 0.0f;
        }
    }
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

    // Apply fade effect if changing scene
    if (mFadeState == FadeState::FadeOut)
    {
        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, static_cast<Uint8>(255 * mSceneTransitionTime/SCENE_TRANSITION_TIME));
        SDL_RenderFillRect(mRenderer, nullptr);
    }
    else if (mFadeState == FadeState::FadeIn)
    {
        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, static_cast<Uint8>(255 * (1.0f - mSceneTransitionTime/SCENE_TRANSITION_TIME)));
        SDL_RenderFillRect(mRenderer, nullptr);
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

}
void Game::UnloadActors()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    delete mScene;
}

void Game::Shutdown()
{
    UnloadActors();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    Quit();
}
void Game::PlayKickAudio() {
    if (audioCooldown <= 0.0f) {
        GetAudio()->PlaySound("Kick.wav");
        audioCooldown = audioCooldownTime; // Reiniciar o cooldown
    }

}