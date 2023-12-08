//
// Created by matheusl on 08/12/23.
//

#ifndef BRAZILSTRIKERS_DRAWFONTCOMPONENT_H
#define BRAZILSTRIKERS_DRAWFONTCOMPONENT_H
#pragma once
#include "DrawComponent.h"
#include <string>

class DrawFontComponent: public DrawComponent {

    public:
        // (Lower draw order corresponds with further back)
        DrawFontComponent(class Actor* owner, const std::string &texturePath, int posX, int posY, int width, int height, std::string value,  const int drawOrder=300);

        void Draw(SDL_Renderer* renderer) override;

    protected:
        SDL_Texture* mTextureSurface;

        int mWidth;
        int mHeight;
        int mPosX;
        int mPosY;


};


#endif //BRAZILSTRIKERS_DRAWFONTCOMPONENT_H
