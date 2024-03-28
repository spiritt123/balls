#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "field.hpp"
#include "arrow.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");

    Field field(sf::Vector2f(100, 100), sf::Vector2f(400, 600));
    double angle = 0.04;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed )
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
					window.close();
                    break;
                case sf::Keyboard::Left:
                    field.getArrow().rotateLeft(angle);
                    break;
                case sf::Keyboard::Right:
                    field.getArrow().rotateRight(angle);
                    break;
                case sf::Keyboard::Up:
                    field.getArrow().addSize(10);
                    break;
                case sf::Keyboard::Down:
                    field.getArrow().addSize(-10);
                    break;
                case sf::Keyboard::Space:
                    field.addBall();
                    break;
                }

            }
        }
        
        field.update();
        field.render(window);
    }
    return 0;
}
