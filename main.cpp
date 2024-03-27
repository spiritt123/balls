#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const sf::Vector2f operator+(const sf::Vector2f& left, const sf::Vector2f& right) {
    sf::Vector2f res;
    res.x = left.x + right.x;
    res.y = left.y + right.y;
    return res;
}
sf::Vector2f& operator+=(const sf::Vector2f& left, const sf::Vector2f& right) {
    sf::Vector2f res;
    res.x = left.x + right.x;
    res.y = left.y + right.y;
    return res;
}
const sf::Vector2f operator-(const sf::Vector2f& left, const sf::Vector2f& right) {
    sf::Vector2f res;
    res.x = left.x - right.x;
    res.y = left.y - right.y;
    return res;
}
sf::Vector2f& operator-=(const sf::Vector2f& left, const sf::Vector2f& right) {
    sf::Vector2f res;
    res.x = left.x - right.x;
    res.y = left.y - right.y;
    return res;
}
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
    sf::Vector2f res;
    res.x = vec.x * cos(angle) - vec.y * sin(angle);
    res.y = vec.x * sin(angle) + vec.y * cos(angle);
    vec = res;
}

sf::Vector2f createVector(const sf::Vector2f& start, const sf::Vector2f& stop)
{
    sf::Vector2f res;
    res.x = stop.x - start.x;
    res.y = stop.y - start.y;
    return res;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	const float R = 400;
	const int N = 200;
	double phi = 2 * M_PI / N;

    sf::Vector2f arrow(600, 600);
    sf::Vector2f start_point(600, 700);
    double angle = 0.05;

    sf::CircleShape circle;
    circle.setRadius(5);
    circle.setPosition(start_point);
    circle.setOrigin(sf::Vector2f(5, 5));
    sf::Vector2f v;
    bool isBall = false;
    double left = 400, right = 800, top = 200, bottom = 700;

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
                    if (arrow.y > 680 && arrow.x < 600)
                        break;
                    arrow -= start_point;
                    route(arrow, -angle * M_PI);
                    arrow += start_point;
                    break;
                case sf::Keyboard::Right:
                    if (arrow.y > 680 && arrow.x > 600)
                        break;
                    arrow -= start_point;
                    route(arrow, angle * M_PI);
                    arrow += start_point;
                    break;
                case sf::Keyboard::Space:
                    v = createVector(start_point, arrow);
                    v.x = v.x / 400;
                    v.y = v.y / 400;
                    isBall = true;
                    break;
                }

            }
        }

        if (isBall)
        {
            double lenght = len(v);
            sf::Vector2f pos = circle.getPosition();
            sf::Vector2f newPosition = circle.getPosition() + v;
            if (newPosition.x < left)
            {
                double k = v.y / v.x;
                double y = (left - pos.x) * k + pos.y; 
                sf::Vector2f dot(left, y);
                sf::Vector2f nv = createVector(dot, newPosition);
                flipV(nv);
                flipV(v);
                newPosition = dot + nv;
            }
            if (newPosition.x > right)
            {
                double k = v.y / v.x;
                double y = (right - pos.x) * k + pos.y; 
                sf::Vector2f dot(right, y);
                sf::Vector2f nv = createVector(dot, newPosition);
                flipV(nv);
                flipV(v);
                newPosition = dot + nv;
            }
            if (newPosition.y < top)
            {
                double k = v.x / v.y;
                double x = (top - pos.y) * k + pos.x; 
                sf::Vector2f dot(x, top);
                sf::Vector2f nv = createVector(dot, newPosition);
                flipH(nv);
                flipH(v);
                newPosition = dot + nv;
            } 
            if (newPosition.y > bottom)
            {
                double k = v.x / v.y;
                double x = (bottom - pos.y) * k + pos.x; 
                sf::Vector2f dot(x, bottom);
                sf::Vector2f nv = createVector(dot, newPosition);
                flipH(nv);
                flipH(v);
                newPosition = dot + nv;
            } 
            circle.setPosition(newPosition);
        }

        window.clear();
        sf::Vertex line[] =
        {
            sf::Vertex(arrow),
            sf::Vertex(start_point)
        };

        window.draw(line, 2, sf::Lines);
        window.draw(circle);

        sf::Vertex box[] =
        {
            sf::Vertex(sf::Vector2f(left, top)),
            sf::Vertex(sf::Vector2f(right, top)),
            sf::Vertex(sf::Vector2f(right, top)),
            sf::Vertex(sf::Vector2f(right, bottom)),
            sf::Vertex(sf::Vector2f(right, bottom)),
            sf::Vertex(sf::Vector2f(left, bottom)),
            sf::Vertex(sf::Vector2f(left, bottom)),
            sf::Vertex(sf::Vector2f(left, top))
        };
        window.draw(box, 8, sf::Lines);

        window.display();
    }
    return 0;
}
