#include "Util.hpp"
float distance(Vector2f a, Vector2f b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }
float magnitude(Vector2f v) { return sqrt(v.x * v.x + v.y * v.y); }
Vector2f normalize(Vector2f v) { return v / magnitude(v); }
