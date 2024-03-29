#pragma once
#include "Entity.hpp"
using namespace std;
class Boid : public Entity {
  public:
    Boid(Vector2f point, float angle)
        : Entity(point, angle) {}

    virtual ~Boid() = default;

    Vector2f separation(vector<Boid> &boids);
    Vector2f cohesion(vector<Boid> &boids);
    Vector2f alignment(vector<Boid> &boids);
    void run(vector<Boid> &boids);
    void flock(vector<Boid> &boids);

    bool operator==(const Boid &boid) const {
        return triangle.getPoint(0) == boid.triangle.getPoint(0) && triangle.getPoint(1) == boid.triangle.getPoint(1) &&
               triangle.getPoint(2) == boid.triangle.getPoint(2);
    }
};
