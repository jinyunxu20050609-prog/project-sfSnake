#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <chrono> 	

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_(), grid_(sf::Color::Black)
{
	/*new*/
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"Press [A][S][D] to select the background color: white, black, brown"
		"\n\nPress [G] to show the grid"
		"\n\nPress [J][K][L] to select the grid color: white, black, brown");
	text_.setFillColor(sf::Color::White);
	text_.setCharacterSize(15);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width, textBounds.top);
	text_.setPosition(Game::Width - 10, 10);
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	/*new*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		gridOn_ = !gridOn_;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		grid_.changeGridColor(sf::Color::White);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		grid_.changeGridColor(sf::Color::Black);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		grid_.changeGridColor(sf::Color(150, 75, 0));	
	

	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	/*new*/
	if (gridOn_)
		grid_.drawGridLines(window);	

	/*new*/
	window.draw(text_);	
	
	
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}


void GameScreen::generateFruit()
/*new*/
{
	static std::default_random_engine engine;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();		
	engine.seed(seed);
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - 2 * SnakeNode::Radius);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - 2 * SnakeNode::Radius);
	static std::uniform_int_distribution<int> colorDistribution1(0, 3);
	static std::uniform_int_distribution<int> colorDistribution2RGB(0, 2);
	static std::uniform_int_distribution<int> colorDistribution2BlBr(0, 1);

	static std::vector<sf::Color> RGB{sf::Color(255, 0, 0), sf::Color(0, 255, 0), sf::Color(0, 0, 255)};	
	static std::vector<sf::Color> BlBr{sf::Color(0, 0, 0), sf::Color(150, 75, 0)};			
	if (colorDistribution1(engine))			
	{
		fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),
			RGB[colorDistribution2RGB(engine)]));			
	}
	else									
	{
		fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),
			BlBr[colorDistribution2BlBr(engine)]));				
	}
}

