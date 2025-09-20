#ifndef RX_FRAME_HEADER
#define RX_FRAME_HEADER

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <set>
#include <vector>
#include "RxComponent.hpp"

const unsigned char WAIT_ON_FRAME = 0b00000001;
const unsigned char DETACH_FROM_FRAME = 0b00000010;

/**
 * @brief A window frame for rendering components.
 */
class RxFrame
{
private:
  int mFramesPerSecond;
  int mFrameTime;
  int mWidth, mHeight;
  bool mNeedsRepaint;
  bool mIsRunning;

  std::shared_ptr<SDL_mutex> mMutex;
  std::shared_ptr<SDL_Window> mDisplay;
  std::shared_ptr<SDL_Renderer> mRenderer;
  std::shared_ptr<SDL_Thread> mGraphicThread;
  std::shared_ptr<std::function<void()>> mOnUpdate;
  std::shared_ptr<std::function<void(SDL_Event)>> mKeyListener;
  std::shared_ptr<std::set<char>> mKeyMap;
  std::shared_ptr<std::vector<RxComponent *>> mChildren;

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
  static int static_thread_function(void *I)
  {
    RxFrame *frame = (RxFrame *)I;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 /*|| TTF_Init() < 0*/
        || SDL_Init(SDL_INIT_TIMER < 0))
    {
      return -1;
    }

    frame->mDisplay = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("Test", 50, 50, frame->mWidth, frame->mHeight,
                         SDL_WINDOW_SHOWN),
        [](SDL_Window *window)
        {
          if (window)
          {
            SDL_DestroyWindow(window);
          }
        });
    if (!frame->mDisplay.get())
      return -1;

    frame->mRenderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(frame->mDisplay.get(), -1, SDL_RENDERER_ACCELERATED),
        [](SDL_Renderer *render)
        {
          if (render)
          {
            SDL_DestroyRenderer(render);
          }
        });
    if (!frame->mRenderer.get())
      return -1;

    while (frame->mIsRunning)
    {
      if (frame->mNeedsRepaint)
      {
        SDL_mutexP(frame->mMutex.get());
        if (frame->renderNextFrame() == -1)
          frame->mIsRunning = false;
        SDL_mutexV(frame->mMutex.get());
      }
      if (frame->mOnUpdate.get())
      {
        (*frame->mOnUpdate.get())();
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
  void addComponent(RxComponent *component);

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
};

#endif
