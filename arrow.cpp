#include "arrow.hpp"
#include "operatorVector.hpp"

#include <cmath>

Arrow::Arrow(const sf::Vector2f& position, const sf::Vector2f& direction, double size)
    : _position(position)
    , _direction(direction)
    , _size(size)
{
}

Arrow::~Arrow() {}

void Arrow::render(sf::RenderWindow& window)
{
    sf::Vertex line[] =
    {
        sf::Vertex(_position),
        sf::Vertex(_position + _direction * _size)
    };

    window.draw(line, 2, sf::Lines);
}

void Arrow::rotate(double angle)
{
    sf::Vector2f res;
    res.x = _direction.x * cos(angle) - _direction.y * sin(angle);
    res.y = _direction.x * sin(angle) + _direction.y * cos(angle);
    _direction = res;
}

void Arrow::rotateLeft(double angle)
{
    if (_direction.y > -0.1f && _direction.x < 0.f)
        return;
    rotate(-angle * M_PI);
}

void Arrow::rotateRight(double angle)
{
    if (_direction.y > -0.1f && _direction.x > 0.f)
        return;
    rotate(angle * M_PI);
}

void Arrow::setSize(double size)
{
    _size = size;
}

sf::Vector2f Arrow::getPosition()
{
    return _position;
}

sf::Vector2f Arrow::getDirection()
{
    return _direction;
}

double Arrow::getSize()
{
    return _size;
}

void Arrow::addSize(double add)
{
    if (_size + add > 100 || _size + add < 0)
        return;
    _size += add;
}


