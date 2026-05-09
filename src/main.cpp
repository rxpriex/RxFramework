#include <SDL_Graph/Components/Rectangle.hpp>
#include <SDL_Graph/RxFrame.hpp>
#include <stdio.h>

int main(int argc, char **argv) {
  RxFrame *frame = new RxFrame(800, 600, 60);
  frame->initFrame(DETACH_FROM_FRAME);
  // frame->setOnUpdate([&]() { printf("Test\n"); });

  Point3D rect_bounds[8] = {
      {-0.5f, -0.5f, -0.5f}, /* 0: left  bottom front */
      {0.5f, -0.5f, -0.5f},  /* 1: right bottom front */
      {0.5f, 0.5f, -0.5f},   /* 2: right top    front */
      {-0.5f, 0.5f, -0.5f},  /* 3: left  top    front */
      {-0.5f, -0.5f, 0.5f},  /* 4: left  bottom back  */
      {0.5f, -0.5f, 0.5f},   /* 5: right bottom back  */
      {0.5f, 0.5f, 0.5f},    /* 6: right top    back  */
      {-0.5f, 0.5f, 0.5f},   /* 7: left  top    back  */
  };
  Rectangle3D rect(rect_bounds, sizeof(rect_bounds) / sizeof(Point3D));
  frame->addComponent(&rect);
  frame->setKeyListener([&](SDL_Event event) {
    switch ((char)event.key.keysym.sym) {
    case 'a':
      rect.rotationX() -= 0.1f;
      rect.update();
      break;
    case 'd':
      rect.rotationX() += 0.1f;
      rect.update();
      break;
    case 'w':
      rect.rotationY() -= 0.1f;
      rect.update();
      break;
    case 's':
      rect.rotationY() += 0.1f;
      rect.update();
      break;
    case '+':
      rect.getOffsetVector().z += 0.1f;
      rect.update();
      break;
    case '-':
      rect.getOffsetVector().z -= 0.1f;
      rect.update();
      break;
    }
  });
  while (frame->isRunning()) {
  }
}
