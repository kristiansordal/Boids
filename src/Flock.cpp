#include "Flock.hpp"
void Flock::add_boid(Vector2f position, float angle) {
    auto boid = Boid(position, angle);
    boid.set_color(Color::Green);
    boids.push_back(boid);
}

void Flock::draw(RenderWindow &window) {
    for (auto &boid : boids) {
        window.draw(boid.triangle);
        window.draw(boid.view_line);
    }
}
void Flock::update(RenderWindow &window) {
    for (auto &boid : boids) {
        boid.constrain();
        boid.update(1.f / 60.f);
    }
    draw(window);
}

void Flock::flocking(vector<Boid> &boids) {
    for (auto &boid : boids) {
        boid.cohesion(boids);
        // boid.alignment(boids);
        // boid.separation(boids);
    }
}
