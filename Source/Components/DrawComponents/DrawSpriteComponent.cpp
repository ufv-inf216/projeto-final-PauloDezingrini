//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawSpriteComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawSpriteComponent::DrawSpriteComponent(class Actor* owner, const std::string &texturePath, const int width, const int height, const int drawOrder)
        :DrawComponent(owner, drawOrder)
        ,mWidth(width)
        ,mHeight(height)
{
    mSpriteSheetSurface = owner->GetGame()->LoadTexture(texturePath);
}

void DrawSpriteComponent::Draw(SDL_Renderer *renderer)
{

    Vector2 camPos = mOwner->GetGame()->GetCameraPos();
    auto dstrect = new SDL_Rect();
    dstrect->x = mOwner->GetPosition().x - camPos.x;
    dstrect->y = mOwner->GetPosition().y - camPos.y;
    dstrect->w = mWidth;
    dstrect->h = mHeight;
    float rotation = mOwner->GetRotation();
    SDL_RendererFlip flip = rotation == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, nullptr, dstrect, 0.0, nullptr, flip);

}