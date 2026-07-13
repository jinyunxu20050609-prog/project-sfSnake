#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Radius,
			Game::Height / 2 - SnakeNode::Radius + (SnakeNode::Radius * 2 * i))));
	}
}


/*new*/
void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction_ != Direction::Down)
		direction_ = Direction::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction_ != Direction::Up)
		direction_ = Direction::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction_ != Direction::Right)
		direction_ = Direction::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction_ != Direction::Left)
		direction_ = Direction::Right;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))		
	{
		auto mousePositioni = sf::Mouse::getPosition(window);	
		sf::Vector2f mousePosition(static_cast<float>(mousePositioni.x), static_cast<float>(mousePositioni.y));
		auto windowSize = window.getSize();

    	if (mousePosition.x >= 0 && mousePosition.x < windowSize.x &&		
        	mousePosition.y >= 0 && mousePosition.y < windowSize.y)
		{
			auto snakePosition = nodes_[0].getPosition();
			
    		sf::Vector2f difference = mousePosition - snakePosition; 	
    		
    		float length = std::sqrt(std::pow(difference.x, 2) + std::pow(difference.y, 2));	

    		if (length > 0.0f) 			
			{
        		directionVector_ = difference / length;		
				direction_ = Direction::Any;
			}
		}
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		/*new*/
		auto difference = it->getPosition() - nodes_[0].getPosition();
		float length = std::sqrt(std::pow(difference.x, 2) + std::pow(difference.y, 2));
		if (length <= SnakeNode::Radius * 2.20)
			toRemove = it;
		//if (it->getBounds().intersects(nodes_[0].getBounds()))
		//	toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		/*new*/
		auto color = toRemove->getColor();		
		if (color == sf::Color::Red)
			grow(3);
		else if (color == sf::Color::Blue)
			grow(2);
		else if (color == sf::Color::Green)
			grow(1);
		fruits.erase(toRemove);
	}
}

void Snake::grow(unsigned count)
{
	/*new*/
	for (unsigned i = 0; i < count; ++i){
		switch (direction_)
		{
		case Direction::Up:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y + 2 * SnakeNode::Radius)));
			break;
		case Direction::Down:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y - 2 * SnakeNode::Radius)));
			break;
		case Direction::Left:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + 2 * SnakeNode::Radius,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		case Direction::Right:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - 2 * SnakeNode::Radius,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		/*new*/
		case Direction::Any:
			nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - 2 * SnakeNode::Radius * getDirectionVector().x,
				nodes_[nodes_.size() - 1].getPosition().y - 2 * SnakeNode::Radius * getDirectionVector().y)));
			break;
		}
	}
}

/*new*/
sf::Vector2f Snake::getDirectionVector() const
{
	return directionVector_;
}


unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	/*new*/
	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		auto difference = headNode.getPosition() - nodes_[i].getPosition();
		float length = std::sqrt(std::pow(difference.x, 2) + std::pow(difference.y, 2));
		if (length <= SnakeNode::Radius * 1.90)		
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move(0, -2 * SnakeNode::Radius);
		break;
	case Direction::Down:
		nodes_[0].move(0, 2 * SnakeNode::Radius);
		break;
	case Direction::Left:
		nodes_[0].move(-2 * SnakeNode::Radius, 0);
		break;
	case Direction::Right:
		nodes_[0].move(2 * SnakeNode::Radius, 0);
		break;
	/*new*/
	case Direction::Any:
		nodes_[0].move(2 * SnakeNode::Radius * getDirectionVector().x,
			2 * SnakeNode::Radius * getDirectionVector().y);
		break;
	}
}

/*new*/
void Snake::render(sf::RenderWindow& window)
{
	static double PI = 3.14159265358979323846;

	float rotationAngle;
	switch (direction_)
	{
	case Direction::Left:
		rotationAngle = -90;
		break;
	case Direction::Right:
		rotationAngle = 90;
		break;
	case Direction::Up:
		rotationAngle = 0;
		break;
	case Direction::Down:
		rotationAngle = 180;
		break;
	case Direction::Any:
    	rotationAngle = atan2(directionVector_.y, directionVector_.x) * (180.0 / PI) + 90;	
		break;
	}
	nodes_[0].renderH(window, rotationAngle);
	for (auto it = ++(nodes_.begin()); it != nodes_.end(); ++it)
	{
		auto difference = it -> getPosition() - (it-1) -> getPosition();
    	float rotationAngleB = atan2(difference.y, difference.x) * (180.0 / PI) + 90;	
		it->renderB(window, rotationAngleB);
	}
}