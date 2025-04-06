#include "../include/RxFrame.hpp"
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_thread.h>

#include <memory>

RxFrame::RxFrame(int rw, int rh){
    if (!initFrame(rw, rh)) {
      THROW_SDL_ERROR(display.get(), renderer.get());
    }
}

bool RxFrame::initFrame(int rw, int rh) {

    children = std::shared_ptr<std::vector<RxComponent*>>(new std::vector<RxComponent*>);

    mutex = std::shared_ptr<SDL_mutex>(SDL_CreateMutex(),[](SDL_mutex* mutex){
      SDL_DestroyMutex(mutex);
    });

    this->rw = rw;
    this->rh = rh;
    this->frames = 60;
    this->repaint = true;
    this->running = true;

    graphicThread = std::shared_ptr<SDL_Thread>(SDL_CreateThread(static_thread_function, "GraphicsThread", this),
  [](SDL_Thread* th){});
    SDL_DetachThread(graphicThread.get());

  return true;
}

int RxFrame::renderNextFrame() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) return -1;
  if(event.type == SDL_KEYDOWN && keyListener.get())(*keyListener.get())(event);

  SDL_SetRenderDrawColor(renderer.get(),
    0, 0, 0, 255);
  SDL_RenderClear(renderer.get());

  for (RxComponent* rc : *children.get()) {

    (*(rc->access_render_instructions()))(rc, renderer.get());

  }

  SDL_RenderPresent(renderer.get());

  return 1;
}

void RxFrame::addComponent(RxComponent* target){
    children.get()->push_back(target);
}

void RxFrame::setOnUpdate(std::function<void()> uFunc) {onUpdate =
  std::shared_ptr<std::function<void()>>(&uFunc);}

void RxFrame::setKeyListener(std::function<void(SDL_Event)> kFunc){keyListener =
  std::shared_ptr<std::function<void(SDL_Event)>>(&kFunc);}
