#include "Entity.hpp"
#define _USE_MATH_DEFINES
#include "Util.hpp"
#include <cmath>

void Entity::spawn(Vector2f point, float angle) {
    // Sets the triangle to an isosceles triangle starting at the pase point
    triangle.setPointCount(3);
    triangle.setPoint(0, point);
    triangle.setPoint(1, Vector2f(point.x - base_ / 2.f, point.y + height_));
    triangle.setPoint(2, Vector2f(point.x + base_ / 2.f, point.y + height_));

    // Sets the origin to the center of the base and rotates triangle
    triangle.setOrigin(Vector2f(point.x, point.y + height_ / 3.f));
    triangle.setRotation(angle);
    triangle.setPosition(point);

    // Initializes rotation and view line
    view_line = VertexArray(Lines, 2);
    compute_view_line();
    compute_direction();
}

void Entity::compute_view_line() {
    Vector2f pos = triangle.getPosition() + height_ / 3.f * direction_;
    view_line[0].position = pos;
    view_line[1].position = pos + direction_ * 200.f;
}

void Entity::compute_direction() {
    float rotation = triangle.getRotation() * M_PI / 180.f;
    direction_.y = -cos(rotation);
    direction_.x = sin(rotation);
}

void Entity::constrain() {
    // Screen dimensions
    const float screen_width = 800.0f;
    const float screen_height = 600.0f;

    sf::Vector2f position = triangle.getPosition();

    // Wrap around horizontally
    if (position.x > screen_width) {
        position.x = 0;
    } else if (position.x < 0) {
        position.x = screen_width;
    }

    // Wrap around vertically
    if (position.y > screen_height) {
        position.y = 0;
    } else if (position.y < 0) {
        position.y = screen_height;
    }

    triangle.setPosition(position);
}

Vector2f Entity::target(Vector2f &target) {
    auto pos = triangle.getOrigin();
    auto d = distance(pos, target);
    auto desired_velocity = (target - pos) / (d * max_speed_);
    auto steering = desired_velocity - velocity_;
    return steering;
}

void Entity::update_entity(float dt) {
    compute_direction();
    compute_view_line();

    auto aligned_acceleration = direction_ * magnitude(acceleration_);
    velocity_ += aligned_acceleration * dt;

    speed_ = magnitude(velocity_);

    if (speed_ > max_speed_) {
        velocity_ = normalize(velocity_) * max_speed_;
        speed_ = max_speed_;
    }

    auto pos = triangle.getPosition() + velocity_ * dt;
    triangle.setPosition(pos);
}
