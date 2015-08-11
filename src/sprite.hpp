#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "support_structs.hpp"
#include <string>
using std::string;
class SDL_Texture;
class SDL_Surface;
class SDL_Renderer;



class Sprite {
public:
    Sprite(SDL_Renderer* renderer);
    Sprite(const string& pathToImage, SDL_Renderer* renderer);
    ~Sprite();

    virtual void draw() const;
    void move(const Point& position);
    void resize(const Size& size);

    void setRenderer(SDL_Renderer* renderer);
    void loadFrom(const string& pathToImage);
    void setImage(SDL_Surface* image);

    Rect getRect() const;

private:
    Point position;
    Size size;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};

#endif // SPRITE_HPP
