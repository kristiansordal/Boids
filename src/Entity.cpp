#include "Entity.hpp"
#define _USE_MATH_DEFINES
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
    auto view_range = view_line[1].position;

    if (view_range.x > 800 || view_range.x < 0 || view_range.y > 600 || view_range.y < 0) {
        triangle.rotate(1.f);
    }
}

void Entity::update(float dt) {
    compute_direction();
    compute_view_line();
    velocity_ = direction_ * speed_;
    triangle.move(velocity_ * dt);
}
