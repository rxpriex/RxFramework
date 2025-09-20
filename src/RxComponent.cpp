#include "../include/RxComponent.hpp"
#include <functional>
#include <memory>

/**
 * @brief Sets the position of the component.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 */
void RxComponent::setLocation(int x, int y) {
    mX = x;
    mY = y;
    mHitbox.x = x;
    mHitbox.y = y;
}

void RxComponent::setAction(std::function<void(RxComponent*)> action){
    mOnAction = std::make_shared<std::function<void(RxComponent*)>>(action);
}

std::function<void(RxComponent*)>* RxComponent::getAction(){
    return mOnAction.get();
}

/**
 * @brief Sets the size of the component.
 * @param width The width of the component.
 * @param height The height of the component.
 */
void RxComponent::setSize(int width, int height) {
    mWidth = width;
    mHeight = height;
    mHitbox.w = width;
    mHitbox.h = height;
}

/**
 * @brief Provides access to the component's render instructions.
 * @return Pointer to the render function.
 */
std::function<void(RxComponent*, SDL_Renderer*)>* RxComponent::getRenderInstructions() {
    return mRenderInstructions.get();
}

void RxComponent::setColor(Color c){
    mColor = c;
}

/**
 * @brief Retrieves the component's position and size parameters.
 * @param x Pointer to store x-coordinate (can be nullptr).
 * @param y Pointer to store y-coordinate (can be nullptr).
 * @param w Pointer to store width (can be nullptr).
 * @param h Pointer to store height (can be nullptr).
 */
void RxComponent::getParameters(int* x, int* y, int* w, int* h) {
    if (x) *x = mX;
    if (y) *y = mY;
    if (w) *w = mWidth;
    if (h) *h = mHeight;
}

/**
 * @brief Checks for collision with another component.
 * @param other The other component to check against.
 * @return True if the components collide, false otherwise.
 */
bool RxComponent::hasCollision(RxComponent& other) {
    return SDL_HasIntersection(&mHitbox, &other.mHitbox) == SDL_TRUE;
}

/**
 * @brief Sets the movement bounds for the component.
 * @param maxX The maximum x-boundary.
 * @param maxY The maximum y-boundary.
 */
void RxComponent::setBounds(int maxX, int maxY) {
    mBounds.h = maxY;
    mBounds.w = maxX;
    mBounds.x = 0;
    mBounds.y = 0;
}

/**
 * @brief Moves the component based on its speed and checks bounds.
 * @return True if movement is valid, false if out of bounds.
 */
bool RxComponent::move() {
    mHitbox.x += mXSpeed;
    mHitbox.y += mYSpeed;

    if (SDL_HasIntersection(&mBounds, &mHitbox) == SDL_FALSE) {
        mHitbox.x -= mXSpeed;
        mHitbox.y -= mYSpeed;
        if (mHitbox.y >= mBounds.y + mBounds.h) {
            return false;
        }
    } else {
        mX += mXSpeed;
        mY += mYSpeed;
    }

    mXSpeed = 0;
    mYSpeed = 0;
    return true;
}

/**
 * @brief Sets the movement speed of the component.
 * @param xSpeed The speed along the x-axis.
 * @param ySpeed The speed along the y-axis.
 */
void RxComponent::setMovementParameters(int xSpeed, int ySpeed) {
    mXSpeed = xSpeed;
    mYSpeed = ySpeed;
}
