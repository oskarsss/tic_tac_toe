#ifndef LINE
#define LINE
#include <SFML/Graphics.hpp>
class Line {
	public:
		Line(sf::Vector2f size = sf::Vector2f(0,0), sf::Vector2f position = sf::Vector2f(0,0), sf::Color color = sf::Color(0,0,0), float rotate=0);
		
		sf::Vector2f getSize();
		sf::Vector2f getPosition();
		sf::Color getColor();
		float getRotate();

	private:
		sf::Vector2f size;
		sf::Vector2f position;
		sf::Color color;
		float rotate;

};


#endif
