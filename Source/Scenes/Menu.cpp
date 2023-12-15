//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "Menu.h"
#include "../Game.h"
#include "../Font.h"
#include "../Actors/Actor.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawFontComponent.h"

Menu::Menu(Game* game)
     :Scene(game)
     ,mMenuFont(nullptr)
{
    //mDrawComponent = new DrawFontComponent(game, "../Assets/Fonts/bruder/BRUDER.ttf", 500, 500, 200, 200, "BRAZIL STRIKERS");
    mMenuFont = new Font();
    mMenuFont->Load("../Assets/Fonts/bruder/BRUDER.ttf");
}

void Menu::Load()
{
    // Background and Title
    auto *background = new Actor(this);
    new DrawSpriteComponent(background, "../Assets/Sprites/Menu/Background.jpeg", 1472, 1024);
    //new DrawSpriteComponent(background, "../Assets/Sprites/Menu/Title.png", 348, 172);

    // Press Space label
    auto *pressSpace = new Actor(this);
    pressSpace->SetPosition(Vector2(mGame->GetWindowWidth()/2.0f, mGame->GetWindowHeight() - 42.0f));
    new DrawFontComponent(pressSpace, "../Assets/Fonts/bruder/BRUDER.ttf", 640, 640, 400, 256, "Press Space");

    auto *title = new Actor(this);
    title->SetPosition(Vector2(mGame->GetWindowWidth()/2.0f, mGame->GetWindowHeight() - 42.0f));
    new DrawFontComponent(title, "../Assets/Fonts/bruder/BRUDER.ttf", 520, 250, 512, 256, "BRAZIL STRIKERS");
}

void Menu::ProcessInput(const Uint8 *keyState)
{
    if(keyState[SDL_SCANCODE_SPACE])
    {
        mGame->SetScene(Game::GameScene::Match);
    }
}

void Menu::Update(float deltaTime, float elapsedTimeSeconds){

}

void Menu::updateScoreBoard(bool team, int goalNumber){

}
/*
Ball * Menu::GetBall() {

}*/
