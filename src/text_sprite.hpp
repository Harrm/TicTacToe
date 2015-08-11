#pragma once
#ifndef TEXTSPRITE_HPP
#define TEXTSPRITE_HPP
#include "sprite.hpp"
class SDL_Color;



class TextSprite: public Sprite {
public:
    TextSprite(const string& text,
               const string& pathToFontFile,
               const SDL_Color& color,
               SDL_Renderer* renderer);

private:

};

#endif // TEXTSPRITE_HPP
