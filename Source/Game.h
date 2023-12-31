// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL.h>
#include <vector>
#include "Math.h"
#include "Actors/Ball.h"
#include "Actors/Wall.h"
#include "Actors/Characters/Character.h"
#include <string>
#include "AudioSystem.h"
#include "GameClock.h"
#include "Actors/ScoreBoard.h"


class Game
{
public:
    const float SCENE_TRANSITION_TIME = 0.25f;

    enum class GameScene
    {
        Menu,
        Match
    };

    enum class FadeState
    {
        FadeIn,
        FadeOut,
        None
    };
    Game(int windowWidth, int windowHeight);

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Actor functions
    void InitializeActors();
    void UpdateActors(float deltaTime);
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // Draw functions
    void AddDrawable(class DrawComponent* drawable);
    void RemoveDrawable(class DrawComponent* drawable);

    // Collider functions
    void AddCollider(class AABBColliderComponent* collider);
    void RemoveCollider(class AABBColliderComponent* collider);
    std::vector<class AABBColliderComponent*>& GetColliders() { return mColliders; }

    void AddCollider(class CircleColliderComponent* collider);
    void RemoveCollider(class CircleColliderComponent* collider);
    std::vector<class CircleColliderComponent*>& GetCircleColliders() { return mCircleColliders; }

    Vector2& GetCameraPos() { return mCameraPos; };
    void SetCameraPos(const Vector2& position) { mCameraPos = position; };

    // Window functions
    int GetWindowWidth() const { return mWindowWidth; }
    int GetWindowHeight() const { return mWindowHeight; }
    Ball* GetBall() const { return mBall; }
    std::vector<Wall*> GetGoals() const { return mGoals; }

    AudioSystem* GetAudio() { return mAudio; }

    SDL_Texture* LoadTexture(const std::string& texturePath);
    SDL_Texture* LoadFontTexture(const std::string& texturePath, const std::string& text);
    std::unordered_map<bool, int>* GetScore();
    // Game-specific
    /*void ResetMatchState();
    Ball * GetBall();
    bool CheckMatchEnded();
    bool ScoreReached() const;
    void ScoreGoal(bool team);*/

    void PlayKickAudio();

    void SetScene(GameScene gameState);
    class Scene *mScene;
    std::vector<class Actor*> mActors;
    void UnloadActors();

private:

    SDL_GameController *findController();
    std::vector<SDL_GameController *> findControllers();
    SDL_JoystickID getControllerInstanceID(SDL_GameController *controller);
    void ProcessInput();
    void UpdateGame();
    void UpdateCamera();
    void GenerateOutput();

    // Game-specific
    void LoadLevel(const std::string& texturePath, int width, int height);
    void LoadData(const std::string& fileName);


    // All the actors in the game
    //std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    // All the draw components
    std::vector<class DrawComponent*> mDrawables;

    // All the collision components
    std::vector<class AABBColliderComponent*> mColliders;
    std::vector<class CircleColliderComponent*> mCircleColliders;

    // SDL stuff
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    AudioSystem* mAudio = nullptr;

    // Window properties
    int mWindowWidth;
    int mWindowHeight;

    // Track elapsed time since game start
    Uint32 mTicksCount;
//    GameClock * mGameClock;
    // Track if we're updating actors right now
    bool mIsRunning;
    bool mUpdatingActors;

    Vector2 mCameraPos;

    // Game-specific
    //int numPlayersTeam0 = 1;
    //int numPlayersTeam1 = 1;
    //Ball* mBall;
    //Actor* mMap;
    //std::vector<std::string> spritesBlue;
    //std::vector<std::string> spritesRed;
    //std::vector<Wall*> mGoals;
    //std::vector<Character*> mCharacters;
    //std::unordered_map<bool, int>* mScore;

    std::unordered_map<bool, int>* mScore;

    float audioCooldown = 0.0f;
    const float audioCooldownTime = 0.1f; // Tempo de cooldown em segundos

    Uint32 startTime;
    float elapsedTimeSeconds;
    // int mScoreLimit;
    //ScoreBoard* mScoreBoard;
    //ScoreBoard* teamAScoreBoard;
    //ScoreBoard* teamBScoreBoard;

    // Scene transition effect
    FadeState mFadeState;
    float mSceneTransitionTime;

    GameScene mGameState;
    //class Scene *mScene;
};
