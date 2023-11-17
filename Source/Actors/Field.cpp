//
// Created by Paulo Dezingrini on 30/10/2023.
//

#include "Field.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Field::Field(Game *mGame, float width, float length)
        :Actor(mGame)
        ,mWidth(width)
        ,mLength(length)
{
    Vector2 fieldPos;
    fieldPos.x = (mGame->GetWindowWidth() - width)/2;
    fieldPos.y = (mGame->GetWindowHeight() - length)/2;

    SetPosition(fieldPos);
    mDrawComponent = new DrawSpriteComponent(this, "../Assets/Sprites/Fields/court_04.png" , width, length);

    CreateColliders();
}

void Field::CreateColliders() {

    float length = 20.0f;

    float x = 1320.0f;
    float y = 900.0f;
    float offset = 85.0f;

    float windowWidth = mGame->GetWindowWidth();
    float windowHeight = mGame->GetWindowHeight();

    std::vector<Vector2> vertices;

    new AABBColliderComponent(this, windowWidth - x, windowHeight - y , x - 300, length, ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x, windowHeight - y + length);
        vertices.emplace_back(windowWidth - 280, windowHeight - y + length);
        vertices.emplace_back(windowWidth - 280, windowHeight - y);

        new DrawPolygonComponent(this, vertices);
    }

    y = 310.0f;
    new AABBColliderComponent(this, windowWidth - x, windowHeight - y, x - 300, length , ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x, windowHeight - y + length);
        vertices.emplace_back(windowWidth - 280, windowHeight - y + length);
        vertices.emplace_back(windowWidth - 280, windowHeight - y);
        new DrawPolygonComponent(this, vertices);
    }

    x = 1320.0f;
    y = 880.0f;
    new AABBColliderComponent(this, windowWidth - x, windowHeight - y, length, offset, ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y + offset);
        vertices.emplace_back(windowWidth - x, windowHeight - y + offset);

        new DrawPolygonComponent(this, vertices);
    }

    y = 710.0f;
    new AABBColliderComponent(this, windowWidth- x, y - offset, length, offset, ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, y - offset);
        vertices.emplace_back(windowWidth - x + length, y - offset);
        vertices.emplace_back(windowWidth - x + length, y);
        vertices.emplace_back(windowWidth - x, y );

        new DrawPolygonComponent(this, vertices);    y = 790.0f;
    }

    x = 300.0f;
    y = 880.0f;
    new AABBColliderComponent(this, windowWidth - x, windowHeight - y, length, offset, ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y + offset);
        vertices.emplace_back(windowWidth - x, windowHeight - y + offset);

        new DrawPolygonComponent(this, vertices);
    }

    y = 710.0f;
    new AABBColliderComponent(this, windowWidth - x, y - offset, length, offset, ColliderLayer::Wall);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, y - offset);
        vertices.emplace_back(windowWidth - x + length, y - offset);
        vertices.emplace_back(windowWidth - x + length, y);
        vertices.emplace_back(windowWidth - x, y );

        new DrawPolygonComponent(this, vertices);
    }

    x = 290.0f;
    y = 795.0f;
    offset = 400.0f;
    new AABBColliderComponent(this, windowWidth - x, windowHeight - y, length, offset, ColliderLayer::Goal);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y + offset);
        vertices.emplace_back(windowWidth - x, windowHeight - y + offset);

        new DrawPolygonComponent(this, vertices);
    }

    x = 1330;
    offset = 400;
    new AABBColliderComponent(this, windowWidth - x, windowHeight - y, length, offset, ColliderLayer::Goal);

    if (mOnDebug) {
        vertices.clear();
        vertices.emplace_back(windowWidth - x, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y);
        vertices.emplace_back(windowWidth - x + length, windowHeight - y + offset);
        vertices.emplace_back(windowWidth - x, windowHeight - y + offset);

        new DrawPolygonComponent(this, vertices);
    }

}

