#include "Flock.hpp"
void Flock::add_boid(Vector2f position, float angle) {
    auto boid = Boid(position, angle);
    boid.set_color(Color::Green);
    boids.push_back(boid);
}

void Flock::draw(RenderWindow &window) {
    for (auto &boid : boids) {
        window.draw(boid.triangle);
    }
}
void Flock::update(RenderWindow &window) {
    flocking();
    draw(window);
}

void Flock::flocking() {
    for (auto &boid : boids) {
        boid.run(boids);
    }
}
