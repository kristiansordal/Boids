#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
float distance(Vector2f a, Vector2f b);
float magnitude(Vector2f v);
void limit(Vector2f &v, float max);
Vector2f normalize(Vector2f v);
