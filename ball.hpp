#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(const sf::Vector2f& position = sf::Vector2f(0, 0), 
         const sf::Vector2f& velocity = sf::Vector2f(0, 0), 
         double radius = 5, size_t live_count = 10);
    ~Ball();

    void setPosition(const sf::Vector2f& position);
    void setVelocity(const sf::Vector2f& velocity);
    void setRadius(double radius);
    void setLiveCount(size_t live_count);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    double getRadius() const;
    size_t getLiveCount() const;

    void decLiveCount();
    sf::Color getColor() const;

private:
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    double _radius;
    size_t _live_count;

    sf::Color _color;
    uint8_t _diff_color;

};



