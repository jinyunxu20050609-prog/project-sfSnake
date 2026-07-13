/*new*/

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Game.h"

using namespace sfSnake;

Grid::Grid(sf::Color gridColor) : gridColor_(gridColor) 
{
    	
    	const int numCellsX = static_cast<int>(1.0f * Game::Width / cellSize_);
    	const int numCellsY = static_cast<int>(1.0f * Game::Height / cellSize_);

    	
    	gridLines_ = sf::VertexArray(sf::Lines, (numCellsX + numCellsY) * 2);

    	
    	for (int i = 0; i < numCellsY; ++i)
    	{
        	gridLines_[(i * 2)].position = sf::Vector2f(0, i * cellSize_);
        	gridLines_[(i * 2) + 1].position = sf::Vector2f(Game::Width, i * cellSize_);
        	gridLines_[(i * 2)].color = gridColor_;
        	gridLines_[(i * 2) + 1].color = gridColor_;
    	}

    	for (int i = 0; i < numCellsX; ++i)
    	{
        	gridLines_[(numCellsY * 2) + (i * 2)].position = sf::Vector2f(i * cellSize_, 0);
        	gridLines_[(numCellsY * 2) + (i * 2) + 1].position = sf::Vector2f(i * cellSize_, Game::Height);
        	gridLines_[(numCellsY * 2) + (i * 2)].color = gridColor_;
        	gridLines_[(numCellsY * 2) + (i * 2) + 1].color = gridColor_;
    	}
}

void Grid::drawGridLines(sf::RenderWindow& window) const
{
	window.draw(gridLines_);
}

void Grid::changeGridColor(sf::Color gridColor)
{
	if (gridColor_ != gridColor)
	{
		gridColor_ = gridColor;
		for (std::size_t i = 0; i < gridLines_.getVertexCount(); ++i)
			gridLines_[i].color = gridColor_;			
	}
}