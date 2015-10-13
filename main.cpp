#include <SFML/Graphics.hpp>

#define GOLDEN 1.61803398875

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1300*GOLDEN, 1300), "Origins");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color(255,255,255));

        window.display();
    } return EXIT_SUCCESS;
}

void drawTree(sf::RenderWindow& window, int x, int y, int theta, int num, int max) {
    
}