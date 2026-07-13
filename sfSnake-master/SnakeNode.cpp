#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include "Game.h"

using namespace sfSnake;

const float SnakeNode::Radius = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Green);
	shape_.setRadius(SnakeNode::Radius);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

//sf::FloatRect SnakeNode::getBounds() const
//{
//	return shape_.getGlobalBounds();
//}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}


/*new*/
void SnakeNode::renderH(sf::RenderWindow& window, float rotationAngle)
{
	static bool isInitialized = false;
	static sf::Texture textureHead;
	static sf::Sprite spriteHead;
	
	if (!isInitialized)
	{
		textureHead.loadFromFile("pics/snakehead.png");		
	
    	spriteHead.setTexture(textureHead);
    	spriteHead.setOrigin(spriteHead.getGlobalBounds().width / 2, spriteHead.getGlobalBounds().height / 2); 

	
    	spriteHead.setScale((2.2 * Radius) / spriteHead.getGlobalBounds().width * 1.3, 
			(2.2 * Radius) / spriteHead.getGlobalBounds().height * 1.3);		
	
		isInitialized = true;
	}

	spriteHead.setRotation(rotationAngle);

    spriteHead.setPosition(getPosition());

    window.draw(spriteHead); 
}


/*new*/
void SnakeNode::renderB(sf::RenderWindow& window, float rotationAngle)
{
	static bool isInitialized = false;
	static sf::Texture textureBody;
	static sf::Sprite spriteBody;
	
	if (!isInitialized)
	{
		textureBody.loadFromFile("pics/snakebody.jpg");		
	
    	spriteBody.setTexture(textureBody);
    	spriteBody.setOrigin(spriteBody.getGlobalBounds().width / 2, spriteBody.getGlobalBounds().height / 2); 

	
    	spriteBody.setScale((2.2 * Radius) / spriteBody.getGlobalBounds().width, (2.2 * Radius) / spriteBody.getGlobalBounds().height);
	
		isInitialized = true;
	}

	spriteBody.setRotation(rotationAngle);

    spriteBody.setPosition(getPosition());

    window.draw(spriteBody); 
}