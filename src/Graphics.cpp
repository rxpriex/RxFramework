#include <SDL_Graph/Lib/Graphics.hpp>

Point2D project_to_screen(Point3D &val) {
  return {(val.x / val.z), (val.y / val.z)};
}

Point2D absolute_coordinates(Point2D &val, Vec2D &frame_bounds) {
  float x_relative = (val.x + 1) / 2;
  float y_relative = (val.y + 1) / 2;
  return {frame_bounds.x * x_relative, frame_bounds.y * y_relative};
}

void vector_add_3D(Vec3D &vec, Vec3D &add) {
  vec.x += add.x;
  vec.y += add.y;
  vec.z += add.z;
}

Point3D rotate_xz(Point3D val, float angle) {
  float s = sin(angle);
  float c = cos(angle);
  return {((val.x * c) - (val.z * s)), val.y, ((val.x * s) + (val.z * c))};
}

Point3D rotate_yz(Point3D val, float angle) {
  float s = sin(angle);
  float c = cos(angle);
  return {val.x, ((val.y * c) - (val.z * s)), ((val.y * s) + (val.z * c))};
}
