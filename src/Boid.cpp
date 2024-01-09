#include "Boid.hpp"
using namespace std;
using namespace sf;

float distance(Vector2f a, Vector2f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }

void Entity::set_color(Color color) {
    triangle.setFillColor(color);
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(Color::Black);
    view_line[0].color = Color::Red;
    view_line[1].color = Color::Red;
}

// void Boid::separation(vector<Boid> &boids) { return; }
// void Boid::alignment(vector<Boid> &boids) { return; }

void Boid::cohesion(vector<Boid> &boids) {
    float range = 50.f;
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
    } else {
        return;
    }

    // Vector2f desired_velocity = center_of_mass - triangle.getPosition();
    // return;
}
void Boid::flock(vector<Boid> &boids) {
    cohesion(boids);
    // alignment(boids);
    // separation(boids);
}

void Boid::run(vector<Boid> &boids) {
    flock(boids);
    update(1.f / 60.f);
}
