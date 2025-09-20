#ifndef DRAWABLE_SPRITE_HEADER
#define DRAWABLE_SPRITE_HEADER

#include "RxComponent.hpp"
#include <SDL2/SDL_render.h>

/**
 * @brief A component that renders a colored rectangle sprite.
 */
class DrawAbleSprite : public RxComponent {
private:
    bool mIsOff;

    Color mOutline;

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
    DrawAbleSprite()
        : RxComponent(Color(255, 255, 255, 255),
            [&](RxComponent* component, SDL_Renderer* renderer) {
              mIsOff = !move();
              SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
              SDL_Rect rect = createRect(mX, mY, mWidth, mHeight);
              SDL_RenderFillRect(renderer, &rect);
              SDL_SetRenderDrawColor(renderer, mOutline.r, mOutline.g, mOutline.b, mOutline.a);
              SDL_RenderDrawRect(renderer, &rect);
          }),
          mIsOff(false), mOutline(Color(255, 255, 255, 255)) {
        mHitbox = {0, 0, 0, 0};
        setLocation(0, 0);
        setSize(0, 0);
    }

    /**
     * @brief Checks if the sprite is off-screen.
     * @return True if off-screen, false otherwise.
     */
    bool isOff();

    /**
     * @brief Sets the outline color of a component.
     * @param c The color to be set.
     */
     void setOutline(Color c);
};

#endif
