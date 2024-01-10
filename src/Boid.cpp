#include "Boid.hpp"
#include "Util.hpp"
#include <iostream>
using namespace std;
using namespace sf;

void Entity::set_color(Color color) {
    triangle.setFillColor(color);
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(Color::Black);
    view_line[0].color = Color::Red;
    view_line[1].color = Color::Red;
}

// void Boid::separation(vector<Boid> &boids) { return; }
// void Boid::alignment(vector<Boid> &boids) { return; }

Vector2f Boid::cohesion(vector<Boid> &boids) {
    float range = 500.f;
    float in_range = 0;
    Vector2f center_of_mass(0.f, 0.f);

    for (auto &boid : boids) {
        auto pos = boid.triangle.getPosition();
        auto d = distance(triangle.getPosition(), pos);

        if (d < range) {
            center_of_mass += pos;
            in_range++;
        }
    }

    if (in_range > 0) {
        center_of_mass /= in_range;
        return target(center_of_mass);
    } else {
        return Vector2f(0.f, 0.f);
    }
}
void Boid::flock(vector<Boid> &boids) {
    [[maybe_unused]] auto steering = cohesion(boids);
    set_acceleration(steering);
}

void Boid::run(vector<Boid> &boids) {
    flock(boids);
    update_entity(1.f / 60.f);
    constrain();
}
