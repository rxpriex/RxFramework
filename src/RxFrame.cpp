#include "../include/RxFrame.hpp"
#include <SDL2/SDL_timer.h>
#include <chrono>
#include <iostream>

/**
 * @brief Constructs an RxFrame with specified dimensions and frame rate.
 * @param width The width of the frame.
 * @param height The height of the frame.
 * @param fps The target frames per second.
 */
RxFrame::RxFrame(int width, int height, int fps) {
    mChildren = std::make_shared<std::vector<RxComponent*>>();
    mMutex = std::shared_ptr<SDL_mutex>(SDL_CreateMutex(), SDL_DestroyMutex);
    mKeyMap = std::make_shared<std::set<char>>();
    mWidth = width;
    mHeight = height;
    mNeedsRepaint = true;
    mIsRunning = true;
    setFps(fps);
}

/**
 * @brief Initializes the frame with specified flags.
 * @param flags Bitmask for frame behavior (e.g., DETACH_FROM_FRAME).
 * @return True if initialization succeeds, false otherwise.
 */
bool RxFrame::initFrame(unsigned char flags) {
    if (flags & DETACH_FROM_FRAME) {
        mGraphicThread = std::shared_ptr<SDL_Thread>(
            SDL_CreateThread(static_thread_function, "GraphicsThread", this), [](SDL_Thread*) {});
        SDL_DetachThread(mGraphicThread.get());
    } else if (flags & WAIT_ON_FRAME) {
        static_thread_function(this);
    }
    return true;
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
        case SDL_KEYUP:
            mKeyMap->erase(static_cast<char>(event.key.keysym.sym));
            break;
        case SDL_KEYDOWN:
            char key = static_cast<char>(event.key.keysym.sym);
            if (mKeyMap->count(key) == 0) {
                (*mKeyListener)(event);
                mKeyMap->insert(key);
            }
            break;
        }
    }

    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(mRenderer.get());

    for (RxComponent* component : *mChildren) {
        (*component->getRenderInstructions())(component, mRenderer.get());
    }

    auto endTime = std::chrono::system_clock::now();
    long frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    int delay = mFrameTime - (frameDuration / 1000);
    if (delay > 0) {
        SDL_Delay(delay);
    }

    SDL_RenderPresent(mRenderer.get());
    return 1;
}

/**
 * @brief Adds a component to the frame's children.
 * @param component Pointer to the component to add.
 */
void RxFrame::addComponent(RxComponent* component) {
    mChildren->push_back(component);
}

/**
 * @brief Sets the update callback function.
 * @param updateFunc The function to call on each update.
 */
void RxFrame::setOnUpdate(std::function<void()> updateFunc) {
    mOnUpdate = std::make_shared<std::function<void()>>(updateFunc);
}

/**
 * @brief Sets the key event listener.
 * @param keyFunc The function to call on key events.
 */
void RxFrame::setKeyListener(std::function<void(SDL_Event)> keyFunc) {
    mKeyListener = std::make_shared<std::function<void(SDL_Event)>>(keyFunc);
}

/**
 * @brief Sets the target frames per second.
 * @param fps The desired frame rate.
 */
void RxFrame::setFps(int fps) {
    mFramesPerSecond = fps;
    mFrameTime = 1000 / fps;
}