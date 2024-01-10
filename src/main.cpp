#include "Flock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <random>
using namespace sf;

int main() {
    RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    auto window_height = desktop.height;
    auto window_width = desktop.width;
    std::cout << "W: " << window_width << ", H: " << window_height << std::endl;
    window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);

    window.setFramerateLimit(60);
    Clock dt_clock, fps;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed); // Mersenne Twister engine
    uniform_real_distribution<float> distribution_width(0.0, (float)window_width);
    uniform_real_distribution<float> distribution_height(0.0, (float)window_height);
    uniform_real_distribution<float> distribution_angle(0.0, 360.0);

    Flock flock;
    for (int i = 0; i < 200; i++) {
        auto x = distribution_width(generator);
        auto y = distribution_height(generator);
        auto angle = distribution_angle(generator);
        flock.add_boid(Vector2f(x, y), angle);
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)) {
                window.close();
            }
        }
        window.clear(Color::White);
        flock.update(window);
        window.display();
    }

    return 0;
}
