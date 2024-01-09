#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
// TODO: Center might be redundant and can be changed for triangle.getPosition()
class Entity {
  private:
    float base_ = 10.f;
    float height_ = 15.f;
    Vector2f center_;
    Vector2f velocity_;
    Vector2f acceleration_;
    float max_velocity_ = 0.0000001f;
    Vector2f prev_center_;

  public:
    ConvexShape triangle;
    VertexArray view_line;
    Entity(Vector2f point, float angle)
        : velocity_(0, 0),
          view_line(Lines, 2) {
        triangle.setPointCount(3);
        spawn(point, angle);
        compute_view_line();
    }

    virtual ~Entity() = default;

    virtual void set_color(Color color);
    void spawn(Vector2f point, float angle);
    void accelerate(Vector2f acceleration);
    void set_velocity(Vector2f velocity);
    void compute_view_line();
    void update(float dt);
};
