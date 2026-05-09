#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <SDL_Graph/Lib/RxFrame.hpp>
#include <chrono>

/**
 * @brief Constructs an RxFrame with specified dimensions and frame rate.
 * @param width The width of the frame.
 * @param height The height of the frame.
 * @param fps The target frames per second.
 */
RxFrame::RxFrame(int width, int height, int fps) {
  children_ = std::make_shared<std::vector<Renderable *>>();
  mutex_ = std::shared_ptr<SDL_mutex>(SDL_CreateMutex(), SDL_DestroyMutex);
  key_map_ = std::make_shared<std::set<char>>();
  bounds_.x = width;
  bounds_.y = height;
  needs_repaint_ = true;
  is_running_ = true;
  setFps(fps);
}

/**
 * @brief Initializes the frame with specified flags.
 * @param flags Bitmask for frame behavior (e.g., DETACH_FROM_FRAME).
 * @return True if initialization succeeds, false otherwise.
 */
bool RxFrame::initFrame(unsigned char flags) {
  if (flags & DETACH_FROM_FRAME) {
    graphics_thread_ = std::shared_ptr<SDL_Thread>(
        SDL_CreateThread(static_thread_function, "GraphicsThread", this),
        [](SDL_Thread *) {});
    SDL_DetachThread(graphics_thread_.get());
  } else if (flags & WAIT_ON_FRAME) {
    static_thread_function(this);
  }
  return true;
}

void RxFrame::mouseClick(SDL_Event event) {
  int x = event.button.x;
  int y = event.button.y;

  // Click logic
}

/**
 * @brief Renders the next frame and handles events.
 * @return 1 if rendering succeeds, -1 if the frame should close.
 */
int RxFrame::renderNextFrame() {
  auto startTime = std::chrono::system_clock::now();
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return -1;
    case SDL_MOUSEBUTTONDOWN:
      mouseClick(event);
      break;
    case SDL_KEYUP:
      key_map_->erase(static_cast<char>(event.key.keysym.sym));
      break;
    case SDL_KEYDOWN:
      char key = static_cast<char>(event.key.keysym.sym);
      if (key_map_->count(key) == 0) {
        if (key_listener_)
          (*key_listener_)(event);
        key_map_->insert(key);
      }
      break;
    }
  }

  SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer_.get());

  for (Renderable *component : *children_) {
    (*component->getRenderInstructions())(component, renderer_.get());
  }

  auto endTime = std::chrono::system_clock::now();
  long frameDuration =
      std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)
          .count();
  int delay = frame_time_ - (frameDuration / 1000);
  if (delay > 0) {
    SDL_Delay(delay);
  }

  SDL_RenderPresent(renderer_.get());
  return 1;
}

/**
 * @brief Adds a component to the frame's children.
 * @param component Pointer to the component to add.
 */
void RxFrame::addComponent(Renderable *component) {
  component->set_bounds(bounds_);
  children_->push_back(component);
}

/**
 * @brief Sets the update callback function.
 * @param updateFunc The function to call on each update.
 */
void RxFrame::setOnUpdate(std::function<void()> updateFunc) {
  on_update_ = std::make_shared<std::function<void()>>(updateFunc);
}

/**
 * @brief Sets the key event listener.
 * @param keyFunc The function to call on key events.
 */
void RxFrame::setKeyListener(std::function<void(SDL_Event)> keyFunc) {
  key_listener_ = std::make_shared<std::function<void(SDL_Event)>>(keyFunc);
}

/**
 * @brief Sets the target frames per second.
 * @param fps The desired frame rate.
 */
void RxFrame::setFps(int fps) {
  fps_ = fps;
  frame_time_ = 1000 / fps;
}
