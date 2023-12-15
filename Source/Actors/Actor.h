// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <SDL_stdinc.h>
#include <unordered_map>
#include "../Math.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "../Scenes/Scene.h"

enum class ActorState
{
    Active,
    Paused,
    Destroy
};

class Actor
{
public:
    Actor(class Scene* scene);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // ProcessInput function called from Game (not overridable)

    void ProcessInput(const Uint8* keyState);
    // Position getter/setter
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }

    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    // Scale getter/setter
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }

    // Rotation getter/setter
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    // State getter/setter
    ActorState GetState() const { return mState; }
    void SetState(ActorState state) { mState = state; }

    // Game getter
    class Game* GetGame() { return mScene->GetGame(); }

    // Returns component of type T, or null if doesn't exist
    template <typename T>
    T* GetComponent() const
    {
        for (auto c : mComponents)
        {
            T* t = dynamic_cast<T*>(c);
            if (t != nullptr)
            {
                return t;
            }
        }

        return nullptr;
    }

    // Game specific
    void SetOnGround() { mIsOnGround = true; };
    void SetOffGround() { mIsOnGround = false; };
    bool IsOnGround() const { return mIsOnGround; };
    void ResetDefaultPosition ();
    void SetControllable(bool controllable) { mControllable = controllable; }
    bool GetControllable() { return mControllable; }
    void SetDefaultPosition(Vector2 position) { mDefaultPos = position; }
    Vector2 GetDefaultPosition() { return mDefaultPos; };

    void SetTeam(bool team) { mTeam = team; }
    bool GetTeam() { return mTeam; }

    // Any actor-specific collision code (overridable)
    virtual void OnCollision(std::unordered_map<CollisionSide, AABBColliderComponent::Overlap>& responses);
    virtual void Kill();

protected:
    //class Game* mGame;
    class Scene* mScene;
    // Any actor-specific update code (overridable)
    virtual void OnUpdate(float deltaTime);
    // Any actor-specific update code (overridable)
    virtual void OnProcessInput(const Uint8* keyState);

    // Actor's state
    ActorState mState;

    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;

    // Components
    std::vector<class Component*> mComponents;

    // Game specific
    bool mIsOnGround;
    bool mControllable;
    bool mTeam;
    Vector2 mDefaultPos;

private:
    friend class Component;

    // Adds component to Actor (this is automatically called
    // in the component constructor)
    void AddComponent(class Component* c);
};