#ifndef RX_LABEL_HEADER
#define RX_LABEL_HEADER

#include "RxComponent.hpp"
#include <SDL2/SDL_ttf.h>

/**
 * @brief A component that displays text on the screen.
 */
class RxLabel : public RxComponent {
private:
    const char* mLabelText;
    SDL_Texture* mTextTexture;
    SDL_Surface* mTextSurface;
    SDL_Renderer* mRenderer;
    SDL_Rect mTextRect;

public:
    /**
     * @brief Constructs a label with the specified text.
     * @param text The text to display.
     */
    RxLabel(const char* text);

    /**
     * @brief Destructor, cleans up SDL resources.
     */
    ~RxLabel();

    /**
     * @brief Creates a texture for the text.
     * @param fontPath Path to the font file.
     * @param fontSize Size of the font.
     */
    void createTexture(const char* fontPath, int fontSize);

    /**
     * @brief Sets the text content of the label.
     * @param text The new text to display.
     */
    void setText(const char* text);
};

#endif
