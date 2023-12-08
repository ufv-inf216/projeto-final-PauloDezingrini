//
// Created by matheusl on 08/12/23.
//

#include "DrawFontComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawFontComponent::DrawFontComponent(class Actor* owner, const std::string &texturePath, int posX, int posY, int width, int height, std::string text, const int drawOrder)
        :DrawComponent(owner, drawOrder), mPosX(posX), mPosY(posY), mHeight(height), mWidth(width)
{
    mTextureSurface = owner->GetGame()->LoadFontTexture(texturePath, text);
}

void DrawFontComponent::Draw(SDL_Renderer *renderer)
{
    SDL_Rect rectangle;
    rectangle.x = mPosX;
    rectangle.y = mPosY;
    rectangle.w = mWidth;
    rectangle.h = mHeight;

    SDL_RenderCopy(renderer, mTextureSurface,NULL,&rectangle);
}