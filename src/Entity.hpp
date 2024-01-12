#pragma once
#include <SFML/Graphics.hpp>
#define SCREEN_WIDTH 2560.0f
#define SCREEN_HEIGHT 1440.0f
using namespace sf;
class Entity {
  private:
    float base_ = 10.f;
    float height_ = 15.f;
    float speed_ = 0.f;
    float max_speed_ = 7.f;
    float max_force_ = 1.5f;
    Vector2f acceleration_;
    Vector2f velocity_;
    Vector2f direction_;

  public:
    ConvexShape triangle;
    Entity(Vector2f point, float angle)
        : velocity_(rand() % 3 - 2, rand() % 3 - 2) {
        spawn(point, angle);
    }

    virtual ~Entity() = default;

    // Getters
    Vector2f get_acceleration() { return acceleration_; }
    Vector2f get_velocity() { return velocity_; }
    float get_max_speed() { return max_speed_; }
    float get_max_force() { return max_force_; }

    // Setters
    void set_acceleration(Vector2f acceleration) { acceleration_ = acceleration; }
    void set_velocity(Vector2f velocity) { velocity_ = velocity; }
    void set_max_speed(float max_speed) { max_speed_ = max_speed; }
    void set_max_force(float max_force) { max_force_ = max_force; }

    virtual void set_color(Color color);
    void spawn(Vector2f point, float angle);
    void apply_force(Vector2f force) { acceleration_ += force; }
    void constrain();
    void update_entity();
};
