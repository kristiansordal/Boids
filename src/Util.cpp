#include "Util.hpp"
// Get the distance between two vectors
float distance(Vector2f a, Vector2f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }

// Get the magnitude of a vector
float magnitude(Vector2f v) { return sqrt(v.x * v.x + v.y * v.y); }

// Limit a vector's magnitude to a maximum
void limit(Vector2f &v, float max) {
    auto mag = magnitude(v);
    if (mag > max) {
        v.x = (v.x / mag) * max;
        v.y = (v.y / mag) * max;
    }
}

// Normalize (turn into unit vector)
void normalize(Vector2f &v) {
    auto mag = magnitude(v);
    if (mag > 0) {
        v /= mag;
    }
}
