#pragma once

#include <SFML/Graphics.hpp>

class Arrow {
public:
    Arrow(const sf::Vector2f& position = sf::Vector2f(0, 0), 
          const sf::Vector2f& direction = sf::Vector2f(0, -1), 
          double size = 100);
    ~Arrow();

    void render(sf::RenderWindow& window);
    void rotate(double angle);
    void rotateLeft(double angle);
    void rotateRight(double angle);
    void setSize(double size);

    sf::Vector2f getPosition();
    sf::Vector2f getDirection();
    double getSize();

    void addSize(double add);

private:
    sf::Vector2f _position;
    sf::Vector2f _direction;
    double _size;
};

