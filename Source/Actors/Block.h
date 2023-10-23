//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once

#include <string>
#include "Actor.h"

class Block : public Actor
{
public:
    explicit Block(Game* game, const std::string &texturePath);
};
