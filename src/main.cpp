#include "Solver.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Boids Simulation");
    sf::Clock dt_clock, fps;
    Solver solver;
    for (int i = 0; i < 10; i++) {
        solver.add_boid(Vector2f(400.f, 300.f), rand() % 360);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        solver.update(window);
        window.display();
    }

    return 0;
}
