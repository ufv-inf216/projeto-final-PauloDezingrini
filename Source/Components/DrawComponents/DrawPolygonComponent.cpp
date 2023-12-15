//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawPolygonComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawPolygonComponent::DrawPolygonComponent(class Actor* owner, std::vector<Vector2> &vertices, int drawOrder)
        :DrawComponent(owner)
        ,mVertices(vertices)
        ,mDrawOrder(drawOrder)
        ,mIsCircle(false)
        ,mRadius(0.0f)
{
}

DrawPolygonComponent::DrawPolygonComponent(class Actor* owner, float radius, int numVertices, int drawOrder)
        :DrawComponent(owner)
        ,mDrawOrder(drawOrder)
        ,mIsCircle(true)
        ,mRadius(radius)
{
    std::vector<Vector2> vertices;

    float angle = 0.0f;

    for (int i = 0; i < 20; i++) {
        float x = radius * Math::Cos(angle);
        float y = radius * Math::Sin(angle);
        vertices.emplace_back(x, y);
        angle += Math::TwoPi / numVertices;
    }

    mVertices = vertices;

}

void DrawPolygonComponent::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 252, 244, 3, 255);

    Vector2 pos = mOwner->GetPosition();
    Vector2 cameraPos = mOwner->GetGame()->GetCameraPos();

    if (mIsCircle) {
        pos.x += mRadius/2;
        pos.y += mRadius;
    }
    // Render vertices as lines
    for(int i = 0; i < mVertices.size() - 1; i++) {
        SDL_RenderDrawLine(renderer, pos.x + mVertices[i].x - cameraPos.x,
                                     pos.y + mVertices[i].y - cameraPos.y,
                                     pos.x + mVertices[i+1].x - cameraPos.x,
                                     pos.y + mVertices[i+1].y - cameraPos.y);
    }

    // Close geometry
    SDL_RenderDrawLine(renderer, pos.x + mVertices[mVertices.size() - 1].x - cameraPos.x,
                                 pos.y + mVertices[mVertices.size() - 1].y - cameraPos.y,
                                 pos.x + mVertices[0].x - cameraPos.x,
                                 pos.y + mVertices[0].y - cameraPos.y);
}