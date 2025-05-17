#ifndef DRAWABLE_SPRITE_HEADER
#define DRAWABLE_SPRITE_HEADER

#include "RxComponent.hpp"

/**
 * @brief A component that renders a colored rectangle sprite.
 */
class DrawableSprite : public RxComponent {
private:
    bool mIsOff;

    /**
     * @brief Creates an SDL_Rect for rendering.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param w The width.
     * @param h The height.
     * @return The constructed SDL_Rect.
     */
    SDL_Rect createRect(int x, int y, int w, int h) {
        SDL_Rect rect = {x, y, w, h};
        return rect;
    }

public:
    /**
     * @brief Constructs a sprite at the specified position and size.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param width The width of the sprite.
     * @param height The height of the sprite.
     */
    DrawableSprite(int x, int y, int width, int height)
        : RxComponent(Color(255, 255, 255, 255), [&](RxComponent* component, SDL_Renderer* renderer) {
              mIsOff = !move();
              SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
              SDL_Rect rect = createRect(mX, mY, mWidth, mHeight);
              SDL_RenderFillRect(renderer, &rect);
          }),
          mIsOff(false) {
        mHitbox = {x, y, width, height};
        setLocation(x, y);
        setSize(width, height);
    }

    /**
     * @brief Checks if the sprite is off-screen.
     * @return True if off-screen, false otherwise.
     */
    bool isOff() { return mIsOff; }
};

#endif