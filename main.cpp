#include <SFML/Graphics.hpp>
#include <tgmath.h>

#define GOLDEN 1.61803398875
#define DEGREE_TO_RADIAN 0.0174533

#define LENGTH_FACTOR .75
#define ANGLE_FACTOR 30
#define THICK 2
#define SEC_PER_FRAME 500

sf::Vector2i drawLine(sf::RenderWindow& window, int x, int y, int length, int theta) {
    sf::RectangleShape line(sf::Vector2f(THICK, length));
    line.setOrigin(THICK/2,length);
    
    line.setPosition(x,window.getSize().y-y);
    line.rotate(theta);
    
    line.setFillColor(sf::Color(0, 0, 0));
    window.draw(line);
    
    sf::Vector2i returnVect(x+length*sin(theta*DEGREE_TO_RADIAN),
                            y+length*cos(theta*DEGREE_TO_RADIAN));
    
    return returnVect;
}

void drawTree(sf::RenderWindow& window, int x, int y, int theta,
              int num, int max, int height) {
    if (num > max) return;
    
    sf::Vector2i newCoords = drawLine(window,x,y,height,theta);
    
    drawTree(window,newCoords.x,newCoords.y,theta + ANGLE_FACTOR/num,num+1,max,height*LENGTH_FACTOR);
    drawTree(window,newCoords.x,newCoords.y,theta - ANGLE_FACTOR/num,num+1,max,height*LENGTH_FACTOR);
}

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1300, 800), "Origins");
    
    sf::Clock clock;
    int layers;
    
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

        if (clock.getElapsedTime().asMilliseconds() > SEC_PER_FRAME) {
            clock.restart();
            layers++;
        }
        
        drawTree(window,650,0,0,1,layers,200);
        
        window.display();
        
    } return EXIT_SUCCESS;
}

