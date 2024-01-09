#include "Boid.hpp"

void Entity::set_color(Color color) {
    triangle.setFillColor(color);
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(Color::Black);
    view_line[0].color = Color::Red;
    view_line[1].color = Color::Red;
}
