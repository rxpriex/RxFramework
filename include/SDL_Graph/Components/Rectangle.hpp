#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include <SDL_Graph/Components/RxComponent.hpp>

class Rectangle3D : public Base3D {
private:
public:
  Rectangle3D(Point3D *points, int count)
      : Base3D(
            [&](Renderable *component, SDL_Renderer *renderer) {
              float dt = 1.0f / 60.0f;
              SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b,
                                     color_.a);

              if (changed_)
                Transform();

              // front face edges (z = -0.5)
              SDL_RenderDrawLine(renderer, screen_space_[0].x,
                                 screen_space_[0].y, screen_space_[1].x,
                                 screen_space_[1].y);
              SDL_RenderDrawLine(renderer, screen_space_[1].x,
                                 screen_space_[1].y, screen_space_[2].x,
                                 screen_space_[2].y);
              SDL_RenderDrawLine(renderer, screen_space_[2].x,
                                 screen_space_[2].y, screen_space_[3].x,
                                 screen_space_[3].y);
              SDL_RenderDrawLine(renderer, screen_space_[3].x,
                                 screen_space_[3].y, screen_space_[0].x,
                                 screen_space_[0].y);

              // back face edges (z = 0.5)
              SDL_RenderDrawLine(renderer, screen_space_[4].x,
                                 screen_space_[4].y, screen_space_[5].x,
                                 screen_space_[5].y);
              SDL_RenderDrawLine(renderer, screen_space_[5].x,
                                 screen_space_[5].y, screen_space_[6].x,
                                 screen_space_[6].y);
              SDL_RenderDrawLine(renderer, screen_space_[6].x,
                                 screen_space_[6].y, screen_space_[7].x,
                                 screen_space_[7].y);
              SDL_RenderDrawLine(renderer, screen_space_[7].x,
                                 screen_space_[7].y, screen_space_[4].x,
                                 screen_space_[4].y);

              // connecting edges (front to back)
              SDL_RenderDrawLine(renderer, screen_space_[0].x,
                                 screen_space_[0].y, screen_space_[4].x,
                                 screen_space_[4].y);
              SDL_RenderDrawLine(renderer, screen_space_[1].x,
                                 screen_space_[1].y, screen_space_[5].x,
                                 screen_space_[5].y);
              SDL_RenderDrawLine(renderer, screen_space_[2].x,
                                 screen_space_[2].y, screen_space_[6].x,
                                 screen_space_[6].y);
              SDL_RenderDrawLine(renderer, screen_space_[3].x,
                                 screen_space_[3].y, screen_space_[7].x,
                                 screen_space_[7].y);
            },
            points, count) {
    z_offset_ = 4;
    color_ = {255, 255, 255, 255};
  }
};

#endif
