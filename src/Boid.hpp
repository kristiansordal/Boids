#include "Entity.hpp"
class Boid : public Entity {
  public:
    Boid(Vector2f point, float angle)
        : Entity(point, angle) {}

    virtual ~Boid() = default;
};
