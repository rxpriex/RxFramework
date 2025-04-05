#include <Components/Template/RxComponent.hpp>
#include <SDL_ttf.h>

class RxLabel : public RxComponent{
private:
    const char* label_text;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;
    TTF_Font* font;

    SDL_Rect textRect;

public:
    RxLabel(const char*);
    RxLabel(int,int);
    ~RxLabel();

    void createTexture(const char*,int);

    void setText(const char*);

};
