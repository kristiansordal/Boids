#include "Boid.hpp"
#include "Util.hpp"
using namespace std;
using namespace sf;

void Entity::set_color(Color color) {
    triangle.setFillColor(color);
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(Color::Black);
}

Vector2f Boid::separation(vector<Boid> &boids) {
    float range = 20.f;
    float in_range = 0;
    Vector2f steer(0.f, 0.f);
    auto pos = triangle.getPosition();

    for (auto &boid : boids) {
        auto b_pos = boid.triangle.getPosition();
        auto d = distance(pos, b_pos);

        if (d < range && d > 0.f) {
            steer += normalize(pos - b_pos) / d;
            in_range++;
        }
    }

    if (in_range > 0) {
        steer = normalize(steer) * get_max_speed() + get_velocity();
        limit(steer, get_max_force());
    }

    return steer;
}
Vector2f Boid::alignment(vector<Boid> &boids) {
    float range = 50.f;
    float in_range = 0;
    Vector2f avg_velocity(0.f, 0.f);
    auto pos = triangle.getPosition();

    for (auto &boid : boids) {
        auto b_pos = boid.triangle.getPosition();
        auto d = distance(pos, b_pos);

        if (d < range && d > 0) {
            avg_velocity += boid.get_velocity();
            in_range++;
        }
    }

    if (in_range > 0) {
        avg_velocity = normalize(avg_velocity / in_range) * get_max_speed();
        avg_velocity -= get_velocity();
        limit(avg_velocity, get_max_force());
        return avg_velocity;
    }

    return Vector2f(0.f, 0.f);
}

Vector2f Boid::cohesion(vector<Boid> &boids) {
    float range = 50.f;
    float in_range = 0;
    Vector2f center_of_mass(0.f, 0.f);

    for (auto &boid : boids) {
        auto pos = boid.triangle.getPosition();
        auto d = distance(triangle.getPosition(), pos);

        if (d < range && d > 0.f) {
            center_of_mass += pos;
            in_range++;
        }
    }

    if (in_range > 0) {
        center_of_mass /= in_range;
        return target(center_of_mass);
    } else {
        return Vector2f(1.f, 1.f);
    }
}
void Boid::flock(vector<Boid> &boids) {
    [[maybe_unused]] auto cohesion_force = cohesion(boids) * 1.5f;
    [[maybe_unused]] auto separation_force = separation(boids) * 1.f;
    [[maybe_unused]] auto alignment_force = alignment(boids) * 1.f;
    apply_force(cohesion_force);
    apply_force(separation_force);
    apply_force(alignment_force);
}

void Boid::run(vector<Boid> &boids) {
    constrain();
    flock(boids);
    update_entity(1.f / 60.f);
}
