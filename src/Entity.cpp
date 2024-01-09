#include "Entity.hpp"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

// Sets the triangle to an isosceles triangle starting at the pase point
void Entity::spawn(Vector2f point, float angle) {
    triangle.setPoint(0, point);
    triangle.setPoint(1, Vector2f(point.x - base_ / 2, point.y + height_));
    triangle.setPoint(2, Vector2f(point.x + base_ / 2, point.y + height_));
    triangle.setOrigin(Vector2f(point.x, point.y + height_ / 3));
    triangle.setRotation(angle);
    triangle.setPosition(point);
}

void Entity::accelerate(Vector2f acceleration) {
    auto magnitude = sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y);

    if (magnitude < max_velocity_) {
        acceleration_ += acceleration;
    }
}
void Entity::set_velocity(Vector2f velocity) { prev_center_ = center_ - velocity; }

void Entity::compute_view_line() {
    // Get rotation and convert to radians
    float rotation = triangle.getRotation() * M_PI / 180.f;

    // Get the direction vector and rotate it 90 degrees
    Vector2f dir(cos(rotation), sin(rotation));
    dir = Vector2f(dir.y, -dir.x);
    Vector2f pos = triangle.getPosition() + height_ / 3.f * dir;

    // Update the view line of the boid
    view_line[0].position = pos;
    view_line[1].position = pos + dir * 250.f;
}

// TODO: Add max velocity and acceleration
void Entity::update(float dt) {
    float rotation = triangle.getRotation() * M_PI / 180.f;
    Vector2f dir(cos(rotation), sin(rotation));
    dir = Vector2f(dir.y, -dir.x);
    velocity_ = dir * .001f * dt;
    prev_center_ = center_;
    center_ += velocity_;
    triangle.move(center_);
    compute_view_line();
}
