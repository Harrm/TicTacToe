#include "text_sprite.hpp"
#include <SDL_ttf.h>
#include <stdexcept>



TextSprite::TextSprite(const string& text,
                       const string& pathToFontFile,
                       const SDL_Color& color, SDL_Renderer* renderer):
    Sprite(renderer) {
    auto* font = TTF_OpenFont("../fonts/28_days_later.ttf", 256);
    if(font == nullptr) {
        std::invalid_argument e("Error when read font file");
        throw e;
    }
    auto textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    setImage(textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

/*

ptr<TextSprite> TextSprite::createTextSprite(const string& text,
                                             const SDL_Color& color) const {
    auto* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    ptr<Sprite> textSprite(new Sprite(textSurface, renderer));
    SDL_FreeSurface(textSurface);
    return textSprite;
}
*/
