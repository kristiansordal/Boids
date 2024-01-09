#include "Solver.hpp"
#include <iostream>
void Solver::apply_constraint() {
    float threshold = 250.0f; // Distance from edge at which boids start steering away
    for (auto &boid : boids) {
        Vector2f center = boid.triangle.getPosition();

        // Check if the boid is near any of the edges
        if (center.x < threshold || center.x > 800 - threshold || center.y < threshold || center.y > 600 - threshold) {
            boid.triangle.rotate(.1f);
        }
    }
}

void Solver::apply_acceleration() {
    for (auto &boid : boids) {
        auto acceleration = Vector2f(0.f, 0.f);
        boid.accelerate(acceleration);
    }
}
void Solver::add_boid(Vector2f position, float angle) {
    auto boid = Boid(position, angle);
    boid.set_color(Color::Green);
    boids.push_back(boid);
}

void Solver::draw(RenderWindow &window) {
    for (auto &boid : boids) {
        window.draw(boid.triangle);
        window.draw(boid.view_line);
    }
}
void Solver::update(RenderWindow &window) {
    apply_constraint();
    apply_acceleration();
    for (auto &boid : boids) {
        boid.update(1.f / 60.f);
    }
    draw(window);
}

float dist(Vector2f pos) { return sqrt(pos.x * pos.x + pos.y * pos.y); }
