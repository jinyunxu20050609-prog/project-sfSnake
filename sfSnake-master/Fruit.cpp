#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, sf::Color color) : color_(color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color_);
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

//sf::FloatRect Fruit::getBounds() const
//{
//	return shape_.getGlobalBounds();
//}

/*new*/
sf::Color Fruit::getColor() const
{
	return color_;
}

sf::Vector2f Fruit::getPosition() const
{
	return shape_.getPosition();
}