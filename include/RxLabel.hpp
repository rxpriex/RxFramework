#ifndef RXLABEL_HEADER
#define RXLABEL_HEADER


#include "RxComponent.hpp"

class RxLabel : public RxComponent{
private:
    const char* label_text;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;

    SDL_Rect textRect;

public:
    RxLabel(const char*);
    RxLabel(int,int);
    ~RxLabel();

    void createTexture(const char*,int);

    void setText(const char*);

};

#endif
