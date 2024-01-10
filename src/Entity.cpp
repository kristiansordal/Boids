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
}

void Entity::constrain() {
    // Wrap around the screen
    sf::Vector2f position = triangle.getPosition();

    // Wrap around horizontally
    if (position.x > SCREEN_WIDTH) {
        position.x = 0;
    } else if (position.x < 0) {
        position.x = SCREEN_WIDTH;
    }

    // Wrap around vertically
    if (position.y > SCREEN_HEIGHT) {
        position.y = 0;
    } else if (position.y < 0) {
        position.y = SCREEN_HEIGHT;
    }

    triangle.setPosition(position);
}

Vector2f Entity::target(Vector2f &target) {
    normalize(target);
    auto desired = -target * max_speed_;
    acceleration_ = desired - velocity_;
    limit(acceleration_, max_force_);
    return acceleration_;
}

void Entity::update_entity() {
    velocity_ += acceleration_ * 0.2f;
    speed_ = magnitude(velocity_);

    if (speed_ > max_speed_) {
        normalize(velocity_);
        velocity_ *= max_speed_;
    }

    // Rotate triangle to face in the direction of the velocity
    float angle = std::atan2(velocity_.y, velocity_.x);
    triangle.setRotation((angle * 180.f / M_PI) + 90.f);

    // Update position of triangle
    auto pos = triangle.getPosition() + velocity_;
    triangle.setPosition(pos);
    acceleration_ *= 0.f;
}
