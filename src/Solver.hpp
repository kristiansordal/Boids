#include "Boid.hpp"
class Solver {

  private:
    // Vector2f acceleration = Vector2f(.1f, .1f);
    std::vector<Boid> boids;

    void apply_constraint();
    void apply_acceleration();

  public:
    Solver() = default;
    ~Solver() = default;

    void add_boid(Vector2f position, float angle);
    void draw(RenderWindow &window);
    void update(RenderWindow &window);
};
