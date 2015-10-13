#include <SFML/Graphics.hpp>
#include <tgmath.h>

#define GOLDEN 1.61803398875
#define DEGREE_TO_RADIAN 0.0174533
#define THICK 1

sf::Vector2i drawLine(sf::RenderWindow& window, int x, int y, int length, int theta) {
    sf::RectangleShape line(sf::Vector2f(THICK, length));
    line.setOrigin(THICK/2,length);
    
    line.setPosition(x,window.getSize().y-y);
    line.rotate(theta);
    
    line.setFillColor(sf::Color(0, 0, 0));
    window.draw(line);
    
    sf::Vector2i returnVect(x+length*cos(theta*DEGREE_TO_RADIAN),
                            y+length*sin(theta*DEGREE_TO_RADIAN));
    
    return returnVect;
}

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1300, 800), "Origins");

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

