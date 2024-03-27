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
double distant(const sf::Vector2f& first, const sf::Vector2f& second)
{
    double dx = second.x - first.x;
    double dy = second.y - first.y;

    return sqrt(dx * dx + dy * dy);
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	const float R = 400;
	const int N = 200;
	double phi = 2 * M_PI / N;

    sf::Vector2f arrow(600, 600);
    sf::Vector2f start_point(600, 700);
    double angle = 0.05;

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
                }

            }
        }

        window.clear();
        sf::Vertex line[] =
        {
            sf::Vertex(arrow),
            sf::Vertex(start_point)
        };

        window.draw(line, 2, sf::Lines);
        window.display();
    }
    return 0;
}
