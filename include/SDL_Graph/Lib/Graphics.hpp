#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <SDL_Graph/Primitives/Vector.hpp>
#include <cmath>

/**
 * @brief Represents a color with RGBA components.
 */
class Color {
public:
  int r, g, b, a;
  Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
  ~Color() = default;
};

Point2D absolute_coordinates(Point2D &val, Vec2D &frame_bounds);

Point2D project_to_screen(Point3D &val);

Point3D rotate_xz(Point3D val, float angle);

Point3D rotate_yz(Point3D val, float angle);

void vector_add_3D(Vec3D &vec, Vec3D &add);

#endif
