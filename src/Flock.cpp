#include "Flock.hpp"
/**
 * Adds a new boid to the flock with the specified position and angle.
 * The new boid is colored green and added to the end of the boids vector.
 *
 * @param position The initial position of the boid as a Vector2f.
 * @param angle The initial angle of the boid.
 */
void Flock::add_boid(Vector2f position, float angle) {
    auto boid = Boid(position, angle);
    boid.set_color(Color::Green);
    boids.push_back(boid);
}

/**
 * Draws all boids in the flock to the provided RenderWindow.
 * This function iterates through each boid in the flock and draws its
 * triangular representation on the window.
 *
 * @param window A reference to the RenderWindow where the boids are to be drawn.
 */
void Flock::draw(RenderWindow &window) {
    for (auto &boid : boids) {
        window.draw(boid.triangle);
    }
}

/**
 * Updates the flock by applying flocking behavior to each boid and
 * then drawing the entire flock to the specified RenderWindow.
 *
 * @param window A reference to the RenderWindow where the updated flock is to be drawn.
 */
void Flock::update(RenderWindow &window) {
    flocking();
    draw(window);
}

/**
 * Set a new color for a specific boid in the flock, for easier tracking
 */
void Flock::set_new_color(int id, Color color) { boids[id].set_color(color); }

/**
 * Applies flocking behavior to each boid in the flock.
 * This function iterates through each boid and calls its run method,
 * which includes behaviors like separation, alignment, and cohesion.
 */
void Flock::flocking() {
    for (auto &boid : boids) {
        boid.run(boids);
    }
}
