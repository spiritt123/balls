#include "ball.hpp"
#include <time.h>

Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& velocity, double radius, size_t live_count)
    : _position(position)
    , _velocity(velocity)
    , _radius(radius)
    , _live_count(live_count)
{
    srand(time(NULL));
    _color.r = rand()%256;
    _color.g = rand()%256;
    _color.b = rand()%256;
    _color.a = 255;
    _diff_color = 250 / live_count;
}

Ball::~Ball() {}

void Ball::setPosition(const sf::Vector2f& position)
{
    _position = position;
}

void Ball::setVelocity(const sf::Vector2f& velocity)
{
    _velocity = velocity;
}

void Ball::setRadius(double radius)
{
    _radius = radius;
}

void Ball::setLiveCount(size_t live_count)
{
    _live_count = live_count;
}

sf::Vector2f Ball::getPosition() const
{
    return _position;
}

sf::Vector2f Ball::getVelocity() const
{
    return _velocity;
}

double Ball::getRadius() const
{
    return _radius;
}

size_t Ball::getLiveCount() const
{
    return _live_count;
}

void Ball::decLiveCount()
{
    --_live_count;
    _color.a -= _diff_color;
}

sf::Color Ball::getColor() const
{
    return _color;
}


