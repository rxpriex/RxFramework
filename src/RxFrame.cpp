#include "../include/RxFrame.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_thread.h>

#include <SDL2/SDL_timer.h>
#include <chrono>
#include <iostream>
#include <memory>

RxFrame::RxFrame(int rw, int rh, int frames) {
  children = std::shared_ptr<std::vector<RxComponent *>>(
      new std::vector<RxComponent *>);

  mutex = std::shared_ptr<SDL_mutex>(
      SDL_CreateMutex(), [](SDL_mutex *mutex) { SDL_DestroyMutex(mutex); });

  keymap = std::shared_ptr<std::set<char>>(new std::set<char>());

  this->rw = rw;
  this->rh = rh;
  this->repaint = true;
  this->running = true;

  setFps(frames);
}

bool RxFrame::initFrame(unsigned char flags) {

  if (flags & DETACH_FROM_FRAME) {
    graphicThread = std::shared_ptr<SDL_Thread>(
        SDL_CreateThread(static_thread_function, "GraphicsThread", this),
        [](SDL_Thread *th) {});
    SDL_DetachThread(graphicThread.get());
  } else if (flags & WAIT_ON_FRAME) {
    static_thread_function((void *)this);
  }

  return true;
}

int RxFrame::renderNextFrame() {
  auto timeAtStart = std::chrono::system_clock::now();
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    return -1;
  case SDL_KEYUP:
    keymap.get()->erase((char)event.key.keysym.sym);
    break;
  case SDL_KEYDOWN:
    char c = (char)event.key.keysym.sym;
    if (keymap.get()->count(c) == 0)
      (*keyListener.get())(event);
    keymap.get()->insert((char)event.key.keysym.sym);
    break;
  }

  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer.get());

  for (RxComponent *rc : *children.get()) {
    (*(rc->access_render_instructions()))(rc, renderer.get());
  }

  auto timeAtEnd = std::chrono::system_clock::now();
  long frameTime = timeAtEnd.time_since_epoch().count() -
                   timeAtStart.time_since_epoch().count();

  int timeToWait = (this->frameTime - (frameTime/1000));
  if (timeToWait > 0)
    SDL_Delay(timeToWait);

  SDL_RenderPresent(renderer.get());
  return 1;
}

void RxFrame::addComponent(RxComponent *target) {
  children.get()->push_back(target);
}

void RxFrame::setOnUpdate(std::function<void()> uFunc) {
  onUpdate = std::shared_ptr<std::function<void()>>(&uFunc);
}

void RxFrame::setKeyListener(std::function<void(SDL_Event)> kFunc) {
  keyListener = std::shared_ptr<std::function<void(SDL_Event)>>(&kFunc);
}

void RxFrame::setFps(int fps) {
  frames = fps;
  frameTime = 1000 / fps;
}
