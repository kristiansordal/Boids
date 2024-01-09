#pragma once
#include "Boid.hpp"
class Solver {

  private:
    std::vector<Boid> boids;
    void apply_constraint();

  public:
    Solver() = default;
    ~Solver() = default;

    void add_boid(Vector2f position, float angle);
    void draw(RenderWindow &window);
    void update(RenderWindow &window);
};
