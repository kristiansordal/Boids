#include "Boid.hpp"
#include "Util.hpp"
using namespace sf;

/**
 * Sets the color of the entity.
 *
 * @param color The Color object representing the fill color of the entity.
 */
void Entity::set_color(Color color) {
    triangle.setFillColor(color);
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(Color::Black);
}

/**
 * Calculates the separation force for a boid. This function ensures that
 * each boid maintains a certain distance from others to avoid crowding.
 *
 * @param boids A reference to a vector of all Boids in the simulation.
 * @return Vector2f representing the steering force for separation.
 */
Vector2f Boid::separation(vector<Boid> &boids) {
    float separation_range = 30.f;
    float in_range = 0;
    Vector2f steer(0.f, 0.f);
    auto pos = triangle.getPosition();

    // Gets the steer pointing away from nearby boids
    for (auto &boid : boids) {
        auto b_pos = boid.triangle.getPosition();
        auto d = distance(pos, b_pos);

        if (d > 0.f && d < separation_range) {
            auto diff = pos - b_pos;
            normalize(diff);
            steer += (diff /= d); // Steer away, weighted by distance
            in_range++;
        }
    }

    if (in_range > 0) {
        steer /= in_range;
    }

    if (magnitude(steer) > 0.f) {
        normalize(steer);
        steer = (steer * get_max_speed()) - get_velocity();
        limit(steer, get_max_force());
    }

    return steer;
}

/**
 * Calculates the alignment force for a boid. This function aligns a boid's
 * velocity with the average velocity of nearby boids.
 *
 * @param boids A reference to a vector of all Boids in the simulation.
 * @return Vector2f representing the steering force for alignment.
 */
Vector2f Boid::alignment(vector<Boid> &boids) {
    float alignment_range = 50.f;
    float in_range = 0;
    Vector2f avg_velocity(0.f, 0.f);
    auto pos = triangle.getPosition();

    // Get the average velocity of boids within range
    for (auto &boid : boids) {
        auto b_pos = boid.triangle.getPosition();
        auto d = distance(pos, b_pos);

        if (d < alignment_range && d > 0) {
            avg_velocity += boid.get_velocity();
            in_range++;
        }
    }

    // If there are boids in the range, steer towards the average alignment of the boids in the flock
    if (in_range > 0) {
        avg_velocity /= in_range;
        normalize(avg_velocity);
        avg_velocity *= get_max_speed();
        auto steer = avg_velocity - get_velocity();
        limit(steer, get_max_force());
        return steer;
    }

    return Vector2f(0.f, 0.f);
}

/**
 * Calculates the cohesion force for a boid. This function steers a boid
 * towards the average position (center of mass) of nearby boids.
 *
 * @param boids A reference to a vector of all Boids in the simulation.
 * @return Vector2f representing the steering force for cohesion.
 */
Vector2f Boid::cohesion(vector<Boid> &boids) {
    float cohesion_range = 50.f;
    float in_range = 0;
    Vector2f center_of_mass(0.f, 0.f);

    // Iterate through the boids to find the center of mass
    for (auto &boid : boids) {
        auto pos = boid.triangle.getPosition();
        auto d = distance(triangle.getPosition(), pos);

        if (d > 0.f && d < cohesion_range) {
            center_of_mass += pos;
            in_range++;
        }
    }

    // If there are boids within the range, steer towards the center of mass
    if (in_range > 0) {
        center_of_mass /= in_range;
        auto steer = center_of_mass - triangle.getPosition();
        normalize(steer);
        return steer;
    }

    return Vector2f(0.f, 0.f);
}

/**
 * Applies flocking behaviors to a boid, combining separation, alignment,
 * and cohesion forces.
 *
 * @param boids A reference to a vector of all Boids in the simulation.
 */
void Boid::flock(vector<Boid> &boids) {
    // Changing the factors here changes the behaviour of the simulation
    auto cohesion_force = cohesion(boids) * 1.5f;
    auto separation_force = separation(boids) * 3.f;
    auto alignment_force = alignment(boids) * 1.f;

    apply_force(separation_force);
    apply_force(alignment_force);
    apply_force(cohesion_force);
}

/**
 * Executes the main behaviors of a boid in the flock. It includes flocking,
 * updating the entity's state, and constraining its movement.
 *
 * @param boids A reference to a vector of all Boids in the simulation.
 */
void Boid::run(vector<Boid> &boids) {
    flock(boids);
    update_entity();
    constrain();
}
