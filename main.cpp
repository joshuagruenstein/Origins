#include <SFML/Graphics.hpp>
#include <tgmath.h>

#define GOLDEN 1.61803398875
#define DEGREE_TO_RADIAN 0.0174533

#define THICK 2
#define SEC_PER_FRAME 500
#define SOIL_HEIGHT 400

double angle = 35;
double length = 200;
double lengthFactor = 0.75;

sf::Vector2i drawLine(sf::RenderWindow& window, int x, int y, int length, int theta, sf::Color color) {
    sf::RectangleShape line(sf::Vector2f(THICK, length));
    line.setOrigin(THICK/2,length);
    line.setFillColor(color);
    line.setOutlineColor(color);
    
    line.setPosition(x,window.getSize().y-y);
    line.rotate(theta);
    
    window.draw(line);
    
    sf::Vector2i returnVect(x+length*sin(theta*DEGREE_TO_RADIAN),
                            y+length*cos(theta*DEGREE_TO_RADIAN));
    
    return returnVect;
}

void drawTree(sf::RenderWindow& window, int x, int y, int theta,
              int num, int max, int height, sf::Color color) {
    if (num > max) return;
    
    sf::Vector2i newCoords = drawLine(window,x,y,height,theta, color);
    
    drawTree(window,newCoords.x,newCoords.y,theta + angle/num,num+1,max,height*lengthFactor, color);
    drawTree(window,newCoords.x,newCoords.y,theta - angle/num,num+1,max,height*lengthFactor, color);
}

void drawWeirdTree(sf::RenderWindow& window, int x, int y, int theta,
                   int num, int max, int height, sf::Color color) {
    if (num > max) return;
    
    sf::Vector2i newCoords = drawLine(window,x,y,height,theta, color);
    
    drawWeirdTree(window,newCoords.x,newCoords.y,theta + angle,num+1,max,height*lengthFactor, color);
    drawWeirdTree(window,newCoords.x,newCoords.y,theta - angle,num+1,max,height*lengthFactor, color);
}

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(2000, 1500), "Origins", sf::Style::Fullscreen);
    sf::RectangleShape soil(sf::Vector2f(window.getSize().x,SOIL_HEIGHT));
    soil.setFillColor(sf::Color::White);
    soil.setOutlineColor(sf::Color::White);
    soil.setPosition(0,window.getSize().y-SOIL_HEIGHT);
    
    sf::Clock clock;
    int layers = 5;
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
                else if (event.key.code == sf::Keyboard::Period) {
                    if (layers < 10) layers++;
                } else if (event.key.code == sf::Keyboard::Comma) {
                    if (layers > 0) layers--;
                }
            }
        }
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (angle>15) angle -= 0.2;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (angle<60) angle += 0.2;
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)) {
            if (length>50) length -= 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) {
            if (length<350) length += 1;
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (lengthFactor>.5) lengthFactor -= .002;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (lengthFactor<.9) lengthFactor += .002;
        }
        
        weird = (sf::Keyboard::isKeyPressed(sf::Keyboard::W));

        window.clear(sf::Color(0,0,0));
        window.draw(soil);
        
        if (weird) {
            drawWeirdTree(window,window.getSize().x/2,SOIL_HEIGHT,0,1,layers,length,sf::Color::White);
            drawWeirdTree(window,window.getSize().x/2,SOIL_HEIGHT,180,1,8,length/2.5,sf::Color::Black);
        }
        else {
            drawTree(window,window.getSize().x/2,SOIL_HEIGHT,0,1,layers,length,sf::Color::White);
            drawTree(window,window.getSize().x/2,SOIL_HEIGHT,180,1,8,length/2.5,sf::Color::Black);
        }
        
        window.display();
        
    } return EXIT_SUCCESS;
}

