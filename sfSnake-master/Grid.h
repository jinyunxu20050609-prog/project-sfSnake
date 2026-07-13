/*new*/

#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Grid
{
public:
	Grid(sf::Color gridColor);
	void changeGridColor(sf::Color gridColor);
	void drawGridLines(sf::RenderWindow& window) const;

private:
	static const int cellSize_ = 16;	
	sf::VertexArray gridLines_;				
	sf::Color gridColor_;				
};
}


#endif