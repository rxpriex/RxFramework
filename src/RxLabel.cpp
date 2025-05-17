#include "../include/RxLabel.hpp"
#include <SDL2/SDL_ttf.h>

/**
 * @brief Constructs an RxLabel with the specified text.
 * @param text The text to display on the label.
 */
RxLabel::RxLabel(const char* text)
    : RxComponent({0, 0, 0, 0}, [&](RxComponent* component, SDL_Renderer* renderer) {
        if (!mTextTexture) {
            createTexture("arial.ttf", 12);
        }
        SDL_RenderCopy(renderer, mTextTexture, nullptr, &mTextRect);
    }) {
    setText(text);
}

/**
 * @brief Sets the text content of the label.
 * @param text The new text to display.
 */
void RxLabel::setText(const char* text) {
    mLabelText = text;
    createTexture(mLabelText, 12); // Update texture when text changes
}

/**
 * @brief Creates a texture for the label's text with the specified font and size.
 * @param fontPath Path to the font file (e.g., "arial.ttf").
 * @param fontSize Size of the font in points.
 */
void RxLabel::createTexture(const char* fontPath, int fontSize) {
    if (mTextTexture) {
        SDL_DestroyTexture(mTextTexture);
        mTextTexture = nullptr;
    }
    if (mTextSurface) {
        SDL_FreeSurface(mTextSurface);
        mTextSurface = nullptr;
    }

    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color white = {255, 255, 255, 255};
    mTextSurface = TTF_RenderText_Blended(font, mLabelText, white);
    if (!mTextSurface) {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
    if (!mTextTexture) {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
    }

    mTextRect = {mX, mY, mWidth, mHeight};
    if (mTextSurface) {
        mTextRect.w = mTextSurface->w;
        mTextRect.h = mTextSurface->h;
    }

    TTF_CloseFont(font);
}

/**
 * @brief Destructor for RxLabel, cleans up SDL resources.
 */
RxLabel::~RxLabel() {
    if (mTextTexture) {
        SDL_DestroyTexture(mTextTexture);
    }
    if (mTextSurface) {
        SDL_FreeSurface(mTextSurface);
    }
}
