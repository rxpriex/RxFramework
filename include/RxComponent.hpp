#ifndef RX_COMPONENT_HEADER
#define RX_COMPONENT_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <functional>
#include <memory>

/**
 * @brief Represents a color with RGBA components.
 */
class Color {
public:
    int r, g, b, a;
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
    ~Color() = default;
};

/**
 * @brief Base class for renderable components in the Rx framework.
 */
class RxComponent {
protected:
    int mX, mY;
    int mWidth, mHeight;
    int mXSpeed, mYSpeed;
    SDL_Rect mHitbox;
    SDL_Rect mBounds;
    Color mColor;
    std::shared_ptr<std::function<void(RxComponent*, SDL_Renderer*)>> mRenderInstructions;
    std::shared_ptr<std::function<void(RxComponent*)>> mOnAction;

public:
    /**
     * @brief Constructs a component with a color and render function.
     * @param color The color of the component.
     * @param renderInstructions The rendering function.
     */
    RxComponent(Color color, std::function<void(RxComponent*, SDL_Renderer*)> renderInstructions)
        : mColor(color), mRenderInstructions(std::make_shared<std::function<void(RxComponent*, SDL_Renderer*)>>(renderInstructions)), mXSpeed(0), mYSpeed(0), mX(0), mY(0) {}

    virtual ~RxComponent() = default;

    /**
     * @brief Moves the component based on speed and bounds.
     * @return True if movement is valid, false otherwise.
     */
    bool move();

    /**
     * @brief Sets the color of the component.
     * @param c The color to be set.
     */
     void setColor(Color c);

    /**
     * @brief Sets the component's size.
     * @param width The width.
     * @param height The height.
     */
    void setSize(int width, int height);

    /**
     * @brief Sets the movement bounds.
     * @param maxX The maximum x-boundary.
     * @param maxY The maximum y-boundary.
     */
    void setBounds(int maxX, int maxY);

    /**
     * @brief Sets the component's position.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    void setLocation(int x, int y);

    /**
     * @brief Checks for collision with another component.
     * @param other The other component.
     * @return True if collision occurs, false otherwise.
     */
    bool hasCollision(RxComponent& other);

    /**
     * @brief Sets movement speed.
     * @param xSpeed The x-axis speed.
     * @param ySpeed The y-axis speed.
     */
    void setMovementParameters(int xSpeed, int ySpeed);

    /**
     * @brief Gets position and size parameters.
     * @param x Pointer for x-coordinate.
     * @param y Pointer for y-coordinate.
     * @param w Pointer for width.
     * @param h Pointer for height.
     */
    void getParameters(int* x, int* y, int* w, int* h);

    /**
     * @brief Sets the action for the component.
     * @param a Action to be set.
     */
     void setAction(std::function<void(RxComponent*)> action);

     /**
      * @brief Getter for the components action.
      * @return The components action.
      */
     std::function<void(RxComponent*)>* getAction();

    /**
     * @brief Accesses the render instructions.
     * @return Pointer to the render function.
     */
    std::function<void(RxComponent*, SDL_Renderer*)>* getRenderInstructions();
};

#endif
