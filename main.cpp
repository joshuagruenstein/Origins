#include <SFML/Graphics.hpp>
#include <tgmath.h>

#define GOLDEN 1.61803398875
#define DEGREE_TO_RADIAN 0.0174533

#define LENGTH_FACTOR .8
#define THICK 2
#define SEC_PER_FRAME 500

int angleFactor = 35;

sf::Vector2i drawLine(sf::RenderWindow& window, int x, int y, int length, int theta) {
    sf::RectangleShape line(sf::Vector2f(THICK, length));
    line.setOrigin(THICK/2,length);
    
    line.setPosition(x,window.getSize().y-y);
    line.rotate(theta);
    
    line.setFillColor(sf::Color(255, 255, 255));
    window.draw(line);
    
    sf::Vector2i returnVect(x+length*sin(theta*DEGREE_TO_RADIAN),
                            y+length*cos(theta*DEGREE_TO_RADIAN));
    
    return returnVect;
}

void drawTree(sf::RenderWindow& window, int x, int y, int theta,
              int num, int max, int height) {
    if (num > max) return;
    
    sf::Vector2i newCoords = drawLine(window,x,y,height,theta);
    
    drawTree(window,newCoords.x,newCoords.y,theta + angleFactor/num,num+1,max,height*LENGTH_FACTOR);
    drawTree(window,newCoords.x,newCoords.y,theta - angleFactor/num,num+1,max,height*LENGTH_FACTOR);
}

void drawWeirdTree(sf::RenderWindow& window, int x, int y, int theta,
                   int num, int max, int height) {
    if (num > max) return;
    
    sf::Vector2i newCoords = drawLine(window,x,y,height,theta);
    
    drawWeirdTree(window,newCoords.x,newCoords.y,theta + angleFactor,num+1,max,height*LENGTH_FACTOR);
    drawWeirdTree(window,newCoords.x,newCoords.y,theta - angleFactor,num+1,max,height*LENGTH_FACTOR);
}

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(2000, 1500), "Origins", sf::Style::Fullscreen);
    
    sf::Clock clock;
    int layers;
    int lowLayers;
    bool weird;
    
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else if (event.key.code == sf::Keyboard::Up) {
                    if (layers < 15) layers++;
                } else if (event.key.code == sf::Keyboard::Down) {
                    if (layers > 0) layers--;
                } else if (event.key.code == sf::Keyboard::W)
                    weird = true;
                else if (event.key.code == sf::Keyboard::Q)
                    weird = false;
                else if (event.key.code == sf::Keyboard::Left) {
                    if (angleFactor>0) angleFactor--;
                } else if (event.key.code == sf::Keyboard::Right) {
                    if (angleFactor<90) angleFactor++;
                }
            }
        }

        window.clear(sf::Color(0,0,0));
        
        if (weird) {
            drawWeirdTree(window,window.getSize().x/2,120,0,1,layers,350);
            drawWeirdTree(window,window.getSize().x/2,200,180,1,8,90);
        }
        else {
            drawTree(window,window.getSize().x/2,120,0,1,layers,350);
            drawTree(window,window.getSize().x/2,200,180,1,8,90);
        }
        
        
        
        window.display();
        
    } return EXIT_SUCCESS;
}

