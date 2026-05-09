#include <SDL_Graph/Components/RxComponent.hpp>
#include <functional>
#include <memory>

/**
 * @brief Provides access to the component's render instructions.
 * @return Pointer to the render function.
 */
std::function<void(Renderable *, SDL_Renderer *)> *
Renderable::getRenderInstructions() {
  return mRenderInstructions.get();
}

void Renderable::set_bounds(Vec2D bounds) { screen_bounds_ = bounds; }

float &Base3D::rotationX() { return angle_x_; }

float &Base3D::rotationY() { return angle_y_; }

void Base3D::Transform() {
  if (!screen_space_)
    screen_space_ = new Point2D[vertices_count_];
  for (int i = 0; i < vertices_count_; i++) {
    Point3D transform = rotate_xz(vertices_[i], angle_x_);
    transform = rotate_yz(transform, angle_y_);
    transform.z += z_offset_;
    vector_add_3D(transform, offset_vector);
    Point2D projected = project_to_screen(transform);
    projected = absolute_coordinates(projected, screen_bounds_);
    screen_space_[i] = projected;
  }
  changed_ = false;
}

Vec3D &Base3D::getOffsetVector() { return offset_vector; }

Point2D *Base3D::ScreenSpaceCoordinates() { return screen_space_; }

Color &Base3D::getColor() { return color_; }

void Base3D::update() { changed_ = true; }
