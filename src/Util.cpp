#include "Util.hpp"
float distance(Vector2f a, Vector2f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }
float magnitude(Vector2f v) { return sqrt(v.x * v.x + v.y * v.y); }
void limit(Vector2f &v, float max) {
    auto mag = magnitude(v);
    if (mag > max) {
        v.x /= mag;
        v.y /= mag;
    }
}
Vector2f normalize(Vector2f v) { return v / magnitude(v); }
