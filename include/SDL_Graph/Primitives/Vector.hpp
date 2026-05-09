#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <SDL2/SDL.h>

typedef struct {
  float x, y, z;
} Vec3D;

typedef struct {
  float x, y;
} Vec2D;

typedef Vec2D Point2D;
typedef Vec3D Point3D;

#endif
