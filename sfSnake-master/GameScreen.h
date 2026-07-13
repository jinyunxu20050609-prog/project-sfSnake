#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Grid.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();

private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	/*new*/
	bool gridOn_ = false;
	sf::Font font_;
	sf::Text text_;
	Grid grid_;
};
}

#endif