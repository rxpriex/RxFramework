#include "RxLabel.hpp"
#include <Components/Template/RxComponent.hpp>
#include <SDL_ttf.h>

RxLabel::RxLabel(const char* text):RxComponent({0,0,0,0}, [&](RxComponent *rcmp,SDL_Renderer* sdlr){
    if(textTexture)
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdlr, textSurface);
    SDL_RenderCopy(sdlr, textTexture, NULL, &textRect);
}){
    setText(text);
}

void RxLabel::setText(const char* text){
    label_text = text;
}

void RxLabel::createTexture(const char* text, int fontSize){
    if(textTexture)
        SDL_DestroyTexture(textTexture);
    if(textSurface)
        SDL_FreeSurface(textSurface);
    if(font)
        TTF_CloseFont(font);

    font = TTF_OpenFont("font.ttf", 24);
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Hello, SDL2!", {255,255,255,255});

    textRect = {x,y,width,height};
}
