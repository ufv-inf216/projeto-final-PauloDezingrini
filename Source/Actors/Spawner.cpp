//
// Created by Lucas N. Ferreira on 30/09/23.
//

#include "Spawner.h"
#include "../Game.h"

const float GOOMBA_FORWARD_SPEED = 100.0f;

Spawner::Spawner(Scene* scene, float spawnDistance)
        :Actor(scene)
        ,mSpawnDistance(spawnDistance)
{

}

void Spawner::OnUpdate(float deltaTime)
{

}