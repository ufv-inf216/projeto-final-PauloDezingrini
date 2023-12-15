//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "Scene.h"
#include "../Actors/Ball.h"

Scene::Scene(Game* game)
{
    mGame = game;
}

void Scene::Load()
{
    // Load the scene
}

const Vector2& Scene::GetCameraPos()
{
    return Vector2::Zero;
}

void Scene::ProcessInput(const Uint8* keyState)
{
    // Process scene input
}

void Scene::Update(float deltatime, float elapsedTimeSeconds){

}

void Scene::ResetMatchState()
{

};

bool Scene::CheckMatchEnded()
{

};
bool Scene::ScoreReached() const {

};
void Scene::updateScoreBoard(bool team, int goalNumber)
{

}

/*Ball * Scene::GetBall() {

}*/
