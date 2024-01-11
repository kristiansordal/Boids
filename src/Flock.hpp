#pragma once
#include "Boid.hpp"
class Flock {

  private:
    std::vector<Boid> boids;
    void apply_constraint();

  public:
    Flock() = default;
    ~Flock() = default;

    void add_boid(Vector2f position, float angle);
    void draw(RenderWindow &window);
    void update(RenderWindow &window);
    void set_new_color(int id, Color color);
    Boid &get_boid(int id);
    int size() { return boids.size(); }
    void flocking();
};
