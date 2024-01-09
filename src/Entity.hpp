#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
// TODO: Center might be redundant and can be changed for triangle.getPosition()
class Entity {
  private:
    float base_ = 10.f;
    float height_ = 15.f;
    float speed_ = 5.f;
    float force_ = 3.f;
    Vector2f velocity_;
    Vector2f direction_;

  public:
    ConvexShape triangle;
    VertexArray view_line;
    Entity(Vector2f point, float angle)
        : velocity_(0, 0) {
        spawn(point, angle);
    }

    virtual ~Entity() = default;

    virtual void set_color(Color color);
    void spawn(Vector2f point, float angle);
    void compute_view_line();
    void compute_direction();
    void update(float dt);
};
