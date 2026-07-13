#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);

	/*new*/
	void renderH(sf::RenderWindow& window, float rotationAngle);
	void renderB(sf::RenderWindow& window, float rotationAngle);

	sf::Vector2f getPosition() const;
	//sf::FloatRect getBounds() const;

	static const float Radius;

private:
	sf::CircleShape shape_;
	sf::Vector2f position_;
};
}

#endif