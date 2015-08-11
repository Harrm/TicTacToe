#include "sprite.hpp"
#include <SDL2/SDL_image.h>
#include <stdexcept>
using std::string;



Sprite::Sprite(SDL_Renderer* renderer):
    renderer(renderer) {}



Sprite::Sprite(const string& pathToImage, SDL_Renderer* renderer):
    Sprite(renderer) {
    loadFrom(pathToImage);
}



Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}



void Sprite::draw() const {
    SDL_Rect destination = {position.x, position.y, size.width, size.height};
    SDL_RenderCopy(renderer, texture, nullptr, &destination);
}



void Sprite::move(const Point& position) {
    this->position = position;
}



void Sprite::resize(const Size& size) {
    this->size = size;
}



void Sprite::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}



void Sprite::loadFrom(const string& pathToImage) {
    if(renderer == nullptr) {
        std::logic_error e("Renderer is null");
        throw e;
    }

    SDL_Surface* image = IMG_Load(pathToImage.c_str());

    if(image == nullptr) {
        std::runtime_error e("Error when load image: " + pathToImage + ":\n" +
                             SDL_GetError());
        throw e;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}



void Sprite::setImage(SDL_Surface* image) {
    if(renderer == nullptr) {
        std::logic_error e("Renderer is null");
        throw e;
    }
    if(image == nullptr) {
        std::invalid_argument e("Image surface pointer is null");
        throw e;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
}



Rect Sprite::getRect() const {
    return {position, size};
}
