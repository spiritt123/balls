#pragma once
#include <SFML/Graphics.hpp>

const sf::Vector2f operator+(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f& operator+=(const sf::Vector2f& left, const sf::Vector2f& right);

const sf::Vector2f operator-(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f& operator-=(const sf::Vector2f& left, const sf::Vector2f& right);

const sf::Vector2f operator*(const sf::Vector2f& vec, double value);

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec);

