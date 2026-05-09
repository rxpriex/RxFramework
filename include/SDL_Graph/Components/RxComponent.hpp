#ifndef RX_COMPONENT_HEADER
#define RX_COMPONENT_HEADER

#include <SDL_Graph/Lib/Graphics.hpp>
#include <functional>
#include <memory>

/**
 * @brief Base class for renderable components in the Rx framework.
 */
class Renderable {
protected:
  std::shared_ptr<std::function<void(Renderable *, SDL_Renderer *)>>
      mRenderInstructions;
  std::shared_ptr<std::function<void(Renderable *)>> mOnAction;

  Vec2D screen_bounds_;

public:
  /**
   * @brief Constructs a component with a color and render function.
   * @param color The color of the component.
   * @param renderInstructions The rendering function.
   */
  Renderable(
      std::function<void(Renderable *, SDL_Renderer *)> renderInstructions)
      : mRenderInstructions(
            std::make_shared<std::function<void(Renderable *, SDL_Renderer *)>>(
                renderInstructions)) {}

  virtual ~Renderable() = default;

  void set_bounds(Vec2D bounds);

  /**
   * @brief Sets the action for the component.
   * @param a Action to be set.
   */
  void setAction(std::function<void(Renderable *)> action);

  /**
   * @brief Getter for the components action.
   * @return The components action.
   */
  std::function<void(Renderable *)> *getAction();

  /**
   * @brief Accesses the render instructions.
   * @return Pointer to the render function.
   */
  std::function<void(Renderable *, SDL_Renderer *)> *getRenderInstructions();
};

class Base3D : public Renderable {
protected:
  Point3D *vertices_;
  Point2D *screen_space_;
  float angle_x_, angle_y_;
  float z_offset_;
  Vec3D offset_vector;
  int vertices_count_;
  bool changed_;
  Color color_;

  void Transform();

public:
  Base3D(std::function<void(Renderable *, SDL_Renderer *)> render_inst,
         Point3D *vertices, int vertice_count)
      : Renderable(render_inst), vertices_(vertices),
        vertices_count_(vertice_count), color_(0, 0, 0, 0), screen_space_(NULL),
        angle_x_(0.0f), angle_y_(0.0f), offset_vector({0, 0, 0}),
        changed_(true) {}

  Color &getColor();

  float &rotationX();

  float &rotationY();

  int getVerticeCount();

  void
  update(); // component has been updated and needs to reevaluate on next render

  Vec3D &getOffsetVector();

  Point2D *ScreenSpaceCoordinates();
};

#endif
