#include "Flock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

int main() {
    int width = 800;
    int height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Boids Simulation");
    sf::Clock dt_clock, fps;

    Flock flock;
    for (int i = 0; i < 100; i++) {
        flock.add_boid(Vector2f((float)(rand() % width), (float)(rand() % height)), rand() % 360);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        flock.update(window);
        window.display();
    }

    return 0;
}
