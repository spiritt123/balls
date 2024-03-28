#include "operatorVector.hpp"

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

const sf::Vector2f operator*(const sf::Vector2f& vec, double value) {
    sf::Vector2f res;
    res.x = vec.x * value; 
    res.y = vec.y * value;
    return res;
}

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec)
{
    stream << vec.x << ":" << vec.y;
}
