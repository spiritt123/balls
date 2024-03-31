#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "ball.hpp"
#include "arrow.hpp"

class Field {
public:
    Field(const sf::Vector2f& position, const sf::Vector2f& size);
    ~Field();

    void update(Ball& ball, const sf::Vector2f& velocity);
    void checkLeft(Ball& ball, const sf::Vector2f& velocity);
    void checkRight(Ball& ball, const sf::Vector2f& velocity);
    void checkTop(Ball& ball, const sf::Vector2f& velocity);
    void checkBottom(Ball& ball, const sf::Vector2f& velocity);
    void update(double diff_clock);
    Arrow& getArrow();
    void render(sf::RenderWindow& window);
    void addBall();

private:
    void renderBox(sf::RenderWindow& window);
    void renderArrow(sf::RenderWindow& window);
    void renderBalls(sf::RenderWindow& window);

private:
    sf::Vector2f _position;
    sf::Vector2f _size;

private:
    std::list<Ball> _balls;
    Arrow _arrow;
};

