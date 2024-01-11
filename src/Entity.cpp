#include "Entity.hpp"
#define _USE_MATH_DEFINES
#include "Util.hpp"
#include <cmath>

/**
 * Spawns in an entity at a given point and a given rotation
 *
 * @param point The point at which to spawn the entity.
 * @param angle The angle at which to spawn the entity.
 */
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

/**
 * Wraps the entity around the screen.
 */
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

/**
 * Updates the entity's position, rotation and velocity
 */
void Entity::update_entity() {
    // Acceleration is scaled to smoothen movement
    velocity_ += acceleration_ * 0.2f;
    limit(velocity_, max_speed_);

    // Rotate triangle to face in the direction of the velocity
    float angle = std::atan2(velocity_.y, velocity_.x);
    triangle.setRotation((angle * 180.f / M_PI) + 90.f);

    // Update position of triangle
    auto pos = triangle.getPosition() + velocity_;
    triangle.setPosition(pos);
    acceleration_ *= 0.f;
}
