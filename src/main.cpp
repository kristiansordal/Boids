#include "Flock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <random>
using namespace sf;

int main() {
    RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    auto window_height = 800;
    auto window_width = 800;
    window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
    window.setFramerateLimit(60);

    // Randomize the position and angle of each boid
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_real_distribution<float> distribution_width(0.0, (float)window_width);
    uniform_real_distribution<float> distribution_height(0.0, (float)window_height);
    uniform_real_distribution<float> distribution_angle(0.0, 360.0);
    auto bg = Color(52, 49, 48);

    Flock flock;
    for (int i = 0; i < 500; i++) {
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
            // Handle mouse button pressed event
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Vector2f mouse_pos = static_cast<Vector2f>(Mouse::getPosition(window));
                auto angle = distribution_angle(generator);
                flock.add_boid(mouse_pos, angle);
            }
        }

        // Continuously update the simulation
        window.clear(bg);
        flock.update(window);
        window.display();
    }

    return 0;
}
