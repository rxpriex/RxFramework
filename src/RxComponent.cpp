#include "../include/RxComponent.hpp"
#include <cstddef>
#include <functional>

void RxComponent::setLocation(int x, int y) {
  this->x = x;
  this->y = y;
}

void RxComponent::setSize(int width, int height) {
  this->width = width;
  this->height = height;
}

std::function<void(RxComponent *,SDL_Renderer*)> *RxComponent::access_render_instructions() {
  return &render_instructions;
}

void RxComponent::getParameters(int *x, int *y, int *w, int *h){
    if(x != NULL){
        *x = this->x;
    }
    if(y != NULL){
        *y = this->y;
    }
    if(w != NULL){
        *w = this->width;
    }
    if(h != NULL){
        *h = this->height;
    }
}

bool RxComponent::hasCollission(RxComponent& other){
    return (SDL_HasIntersection(&hitbox, &(other.hitbox)) == SDL_TRUE);
}

void RxComponent::setBounds(int maxX, int maxY){
   bounds.h = maxY;
   bounds.w = maxX;
   bounds.x = 0;
   bounds.y = 0;
}

bool RxComponent::move(){
  hitbox.x += xspeed;
  hitbox.y += yspeed;

  if (SDL_HasIntersection(&bounds, &hitbox) == SDL_FALSE) {
    if ((hitbox.y) >= (bounds.y + bounds.h)) {
        hitbox.x -= xspeed;
        hitbox.y -= yspeed;
        return false;
    }
  } else {
    x += xspeed;
    y += yspeed;
  }

  xspeed = 0;
  yspeed = 0;

  return true;
}

void RxComponent::set_movement_parameters(int x, int y){
  xspeed=x;
  yspeed=y;
}
