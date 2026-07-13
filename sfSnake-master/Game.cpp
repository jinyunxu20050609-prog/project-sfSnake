#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/After_All_-_boomboombeckett.mp3");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		/*new*/
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::A)
				bgColor_ = sf::Color::White;
			else if (event.key.code == sf::Keyboard::S)
				bgColor_ = sf::Color::Black;
			else if (event.key.code == sf::Keyboard::D)
				bgColor_ = sf::Color(150, 75, 0);
		}
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	/*new*/
	window_.clear(bgColor_);
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;
		

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}