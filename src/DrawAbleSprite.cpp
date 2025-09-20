#include "../include/DrawAbleSprite.hpp"

bool DrawAbleSprite::isOff() { return mIsOff; }

void DrawAbleSprite::setOutline(Color c){
    mOutline = c;
}
