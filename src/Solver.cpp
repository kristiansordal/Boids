#include "Solver.hpp"
void Solver::apply_constraint() {
    for (auto &boid : boids) {
        auto view_range = boid.view_line[1].position;

        if (view_range.x > 800 || view_range.x < 0 || view_range.y > 600 || view_range.y < 0) {
            boid.triangle.rotate(1.f);
        }
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
    for (auto &boid : boids) {
        boid.update(1.f / 60.f);
    }
    draw(window);
}
