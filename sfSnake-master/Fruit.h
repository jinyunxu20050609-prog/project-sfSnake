#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position, sf::Color color);

	void render(sf::RenderWindow& window);

	//sf::FloatRect getBounds() const;

	/*new*/
	sf::Color getColor() const;

	sf::Vector2f getPosition() const;

private:
	sf::CircleShape shape_;

	static const float Radius;

	/*new*/
	sf::Color color_;
};
}

#endif