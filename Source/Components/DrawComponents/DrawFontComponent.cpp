//
// Created by matheusl on 08/12/23.
//

#include "DrawFontComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawFontComponent::DrawFontComponent(class Actor* owner, const std::string &texturePath, const int drawOrder)
        :DrawComponent(owner, drawOrder)
{
    mTextureSurface = owner->GetGame()->LoadFontTexture(texturePath);
}

void DrawFontComponent::Draw(SDL_Renderer *renderer)
{
    SDL_Rect rectangle;
    rectangle.x = 550;
    rectangle.y = 5;
    rectangle.w = 400;
    rectangle.h = 100;

    SDL_RenderCopy(renderer, mTextureSurface,NULL,&rectangle);
}