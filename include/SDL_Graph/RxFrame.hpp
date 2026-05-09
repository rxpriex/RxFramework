#ifndef RX_FRAME_HEADER
#define RX_FRAME_HEADER

#include <SDL2/SDL.h>
#include <SDL_Graph/Components/RxComponent.hpp>
#include <functional>
#include <memory>
#include <set>
#include <vector>

const unsigned char WAIT_ON_FRAME = 0b00000001;
const unsigned char DETACH_FROM_FRAME = 0b00000010;

/**
 * @brief A window frame for rendering components.
 */
class RxFrame {
private:
  int fps_;
  int frame_time_;
  int width_, mHeight;
  bool needs_repaint_;
  alignas(bool) volatile bool is_running_; // make sure the termination flag is
                                           // thread save

  std::shared_ptr<SDL_mutex> mutex_;
  std::shared_ptr<SDL_Window> display_;
  std::shared_ptr<SDL_Renderer> renderer_;
  std::shared_ptr<SDL_Thread> graphics_thread_;
  std::shared_ptr<std::function<void()>> on_update_;
  std::shared_ptr<std::function<void(SDL_Event)>> key_listener_;
  std::shared_ptr<std::set<char>> key_map_;
  std::shared_ptr<std::vector<Renderable *>> children_;

  /**
   * @brief Internal mouse click handler.
   * @param event Mouse click event.
   */
  void mouseClick(SDL_Event);

  /**
   * @brief Static thread function for graphics rendering.
   * @param data Pointer to the RxFrame instance.
   * @return 1 on success, -1 on failure.
   */
  static int static_thread_function(void *I) {
    RxFrame *frame = (RxFrame *)I;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 /*|| TTF_Init() < 0*/
        || SDL_Init(SDL_INIT_TIMER < 0)) {
      return -1;
    }

    frame->display_ = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("Test", 50, 50, frame->width_, frame->mHeight,
                         SDL_WINDOW_SHOWN),
        [](SDL_Window *window) {
          if (window) {
            SDL_DestroyWindow(window);
          }
        });
    if (!frame->display_.get())
      return -1;

    frame->renderer_ = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(frame->display_.get(), -1, SDL_RENDERER_ACCELERATED),
        [](SDL_Renderer *render) {
          if (render) {
            SDL_DestroyRenderer(render);
          }
        });
    if (!frame->renderer_.get())
      return -1;

    while (frame->is_running_) {
      if (frame->needs_repaint_) {
        SDL_mutexP(frame->mutex_.get());
        if (frame->renderNextFrame() == -1)
          frame->is_running_ = false;
        SDL_mutexV(frame->mutex_.get());
      }
      if (frame->on_update_.get()) {
        (*frame->on_update_.get())();
      }
    }

    return 1;
  }

public:
  /**
   * @brief Constructs a frame with specified dimensions and frame rate.
   * @param width The width of the frame.
   * @param height The height of the frame.
   * @param fps The target frames per second.
   */
  RxFrame(int width, int height, int fps);

  ~RxFrame() = default;

  /**
   * @brief Sets the target frame rate.
   * @param fps The desired frames per second.
   */
  void setFps(int fps);

  /**
   * @brief Renders the next frame.
   * @return 1 on success, -1 if the frame should close.
   */
  int renderNextFrame();

  /**
   * @brief Initializes the frame.
   * @param flags Bitmask for frame behavior.
   * @return True if initialization succeeds, false otherwise.
   */
  bool initFrame(unsigned char flags);

  /**
   * @brief Adds a component to the frame.
   * @param component Pointer to the component.
   */
  void addComponent(Renderable *component);

  /**
   * @brief Sets the update callback.
   * @param updateFunc The update function.
   */
  void setOnUpdate(std::function<void()> updateFunc);

  /**
   * @brief Sets the key event listener.
   * @param keyFunc The key event handler.
   */
  void setKeyListener(std::function<void(SDL_Event)> keyFunc);

  bool isRunning() { return is_running_; }
  void setRunning(bool val) { is_running_ = val; }
};

#endif
