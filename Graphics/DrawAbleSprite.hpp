#include "Components/Template/RxComponent.hpp"
#include <cstdio>

class DrawAbleSprite : public RxComponent {
private:
  bool off;

  SDL_Rect getRect(int x, int y, int w, int h) {
    SDL_Rect to_render;

    to_render.x = x;
    to_render.y = y;
    to_render.w = w;
    to_render.h = h;

    return to_render;
  }

public:
  DrawAbleSprite(int x, int y, int width, int height)
      : RxComponent(Color(255, 255, 255, 255),
                    [&](RxComponent *component, SDL_Renderer *render) {
                      off = !move();
                      SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);

                      SDL_Rect to_render =
                          getRect(this->x, this->y, this->width, this->height);
                      SDL_RenderFillRect(render, &to_render);
                    }),off(false) {
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = width;
    hitbox.h = height;

    setLocation(x, y);
    setSize(width, height);
  }

  bool isOff(){
    return off;
  }
};
