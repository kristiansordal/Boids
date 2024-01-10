#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Entity {
  private:
    float base_ = 10.f;
    float height_ = 15.f;
    float speed_ = 0.f;
    float max_speed_ = 5.f;
    float force_ = 3.f;
    Vector2f acceleration_;
    Vector2f velocity_;
    Vector2f direction_;

  public:
    ConvexShape triangle;
    VertexArray view_line;
    Entity(Vector2f point, float angle)
        : acceleration_(0.01f, 0.01f),
          velocity_(0, 0) {
        spawn(point, angle);
    }

    virtual ~Entity() = default;

    // Getters
    Vector2f get_acceleration() { return acceleration_; }

    // Setters
    void set_acceleration(Vector2f acceleration) { acceleration_ = acceleration; }

    virtual void set_color(Color color);
    void spawn(Vector2f point, float angle);
    void compute_view_line();
    void compute_direction();
    void apply_force(Vector2f force) { acceleration_ += force; }
    Vector2f target(Vector2f &target);
    void constrain();
    void update_entity(float dt);
};
