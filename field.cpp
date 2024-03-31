#include "field.hpp"
#include "operatorVector.hpp"
#include <cmath>
#include <iostream>

Field::Field(const sf::Vector2f& position, const sf::Vector2f& size)
    : _position(position)
    , _size(size)
{
    sf::Vector2f arrow_position = sf::Vector2f(_position.x + _size.x / 2, _position.y + _size.y);
    _arrow = Arrow(arrow_position);
}

Field::~Field() {}

double len(const sf::Vector2f& vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}
double distant(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return len(second - first);
}

void flipH(sf::Vector2f& vec)
{
    vec.y = -1 * vec.y;
}

void flipV(sf::Vector2f& vec)
{
    vec.x = -1 * vec.x;
}

void route(sf::Vector2f& vec, double angle)
{
}

sf::Vector2f createVector(const sf::Vector2f& start, const sf::Vector2f& stop)
{
    sf::Vector2f res;
    res.x = stop.x - start.x;
    res.y = stop.y - start.y;
    return res;
}

bool isDotIntoBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& dot)
{
    if (dot.x < position.x || dot.x > position.x + size.x)
        return false;
    if (dot.y < position.y || dot.y > position.y + size.y)
        return false;
    return true;
}

void Field::update(Ball& ball, const sf::Vector2f& velocity)
{
    if (ball.getLiveCount() == 0)
        return;
    if (len(velocity) < 0.0001)
        return;
    sf::Vector2f newPosition = ball.getPosition() + velocity;
    double R = ball.getRadius();
    sf::Vector2f border(R, R);
    if (isDotIntoBox(_position + border, _size - (border * 2), newPosition))
    {
        ball.setPosition(newPosition);
        return;
    }

    checkLeft(ball, velocity);
    checkRight(ball, velocity);
    checkTop(ball, velocity);
    checkBottom(ball, velocity);
}

void Field::checkLeft(Ball& ball, const sf::Vector2f& velocity)
{
    sf::Vector2f pos = ball.getPosition();
    double R = ball.getRadius();
    double k = velocity.y / velocity.x;
    double y = (_position.x + R - pos.x) * k + pos.y;
    if (y < _position.y + R || y > _position.y + _size.y - R)
        return;
    
    sf::Vector2f dot(_position.x + R, y); // точка удара о стенку
    if (len(createVector(pos, dot)) > len(velocity))
        return;
    ball.decLiveCount();

    sf::Vector2f v = ball.getVelocity(); // обновить направление скорости
    flipV(v);
    ball.setVelocity(v);

    sf::Vector2f nv = createVector(dot, pos + velocity); // образобать оставшееся перемещение
    flipV(nv);
    ball.setPosition(dot); // считать, что шар прилип
    update(ball, nv); // обработать остатоное перемещение после удара
}

void Field::checkRight(Ball& ball, const sf::Vector2f& velocity)
{
    double R = ball.getRadius();
    sf::Vector2f pos = ball.getPosition();
    double k = velocity.y / velocity.x;
    double y = (_position.x - R + _size.x - pos.x) * k + pos.y;
    if (y < _position.y + R || y > _position.y + _size.y - R)
        return;
    sf::Vector2f dot(_position.x + _size.x - R, y); // точка удара о стенку
    if (len(createVector(pos, dot)) > len(velocity))
        return;
    ball.decLiveCount();

    
    sf::Vector2f v = ball.getVelocity(); // обновить направление скорости
    flipV(v);
    ball.setVelocity(v);

    sf::Vector2f nv = createVector(dot, pos + velocity); // образобать оставшееся перемещение
    flipV(nv);
    ball.setPosition(dot); // считать, что шар прилип
    update(ball, nv); // обработать остатоное перемещение после удара
}

void Field::checkTop(Ball& ball, const sf::Vector2f& velocity)
{
    double R = ball.getRadius();
    sf::Vector2f pos = ball.getPosition();
    double k = velocity.x / velocity.y;
    double x = (_position.y + R - pos.y) * k + pos.x;
    if (x < _position.x + R || x > _position.x + _size.x - R)
        return;
    sf::Vector2f dot(x, _position.y + R); // точка удара о стенку
    if (len(createVector(pos, dot)) > len(velocity))
        return;
    ball.decLiveCount();

    
    sf::Vector2f v = ball.getVelocity(); // обновить направление скорости
    flipH(v);
    ball.setVelocity(v);

    sf::Vector2f nv = createVector(dot, ball.getPosition() + velocity); // образобать оставшееся перемещение
    flipH(nv);
    ball.setPosition(dot); // считать, что шар прилип
    update(ball, nv); // обработать остатоное перемещение после удара
}

void Field::checkBottom(Ball& ball, const sf::Vector2f& velocity)
{
    double R = ball.getRadius();
    sf::Vector2f pos = ball.getPosition();
    double k = velocity.x / velocity.y;
    double x = (_position.y + _size.y - R - pos.y) * k + pos.x;
    if (x < _position.x + R || x > _position.x + _size.x - R)
        return;
    sf::Vector2f dot(x, _position.y + _size.y - R); // точка удара о стенку
    if (len(createVector(pos, dot)) > len(velocity))
        return;
    ball.decLiveCount();

    
    sf::Vector2f v = ball.getVelocity(); // обновить направление скорости
    flipH(v);
    ball.setVelocity(v);

    sf::Vector2f nv = createVector(dot, ball.getPosition() + velocity); // образобать оставшееся перемещение
    flipH(nv);
    ball.setPosition(dot); // считать, что шар прилип
    update(ball, nv); // обработать остатоное перемещение после удара
}

void Field::update(double diff_clock)
{
    for (auto &b : _balls)
    {
        update(b, b.getVelocity() * diff_clock);
    }
    _balls.erase(std::remove_if(_balls.begin(), _balls.end(), [=](const Ball& b){ return !b.getLiveCount(); }), _balls.end());
}

Arrow& Field::getArrow()
{
    return _arrow;
}

void Field::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(210, 177, 142));
    renderBox(window);
    renderArrow(window);
    renderBalls(window);
    window.display();
}

void Field::addBall()
{
    sf::Vector2f v = _arrow.getDirection() * _arrow.getSize();
    sf::Vector2f pos = _arrow.getPosition() + v;
    Ball ball(pos, v, 25);
    _balls.push_back(ball);
}

void Field::renderBox(sf::RenderWindow& window)
{
    sf::Vector2f lt = _position;
    sf::Vector2f lb = _position + sf::Vector2f(0, _size.y);
    sf::Vector2f rt = _position + sf::Vector2f(_size.x, 0);
    sf::Vector2f rb = _position + _size;
    sf::Vertex box[] =
    {
        sf::Vertex(lt),
        sf::Vertex(rt),
        sf::Vertex(rt),
        sf::Vertex(rb),
        sf::Vertex(rb),
        sf::Vertex(lb),
        sf::Vertex(lb),
        sf::Vertex(lt)
    };
    window.draw(box, 8, sf::Lines);
}

void Field::renderArrow(sf::RenderWindow& window)
{
    _arrow.render(window);
}

void Field::renderBalls(sf::RenderWindow& window)
{
    sf::CircleShape circle;

    for (const auto& b : _balls)
    {
        circle.setRadius(b.getRadius());
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOrigin(sf::Vector2f(b.getRadius(), b.getRadius()));
        circle.setPosition(b.getPosition());
        circle.setFillColor(b.getColor());

        window.draw(circle);
    }
}


