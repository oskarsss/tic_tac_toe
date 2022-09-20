#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include "Line.h"
#include <bitset>
#include <iostream>

class Button {
	public:
		Button (sf::Image* Image  ,sf::Vector2i Cords,sf::Vector2i Size =  sf::Vector2i(75,75), int* Value=new int (0), int(*)(sf::RenderWindow*, std::vector<Button*>& ,std::vector<Line*>&, Button*)=nullptr);
		~Button();
		sf::Vector2i getCords();
		sf::Image* getImage();
		sf::Vector2i getSize();
		sf::Texture getTexture();
		int getValue();
		int* getValueptr();
		sf::Vector3i getIndexes();

		void setTexture(sf::Texture);
		void setValue(int);
		void setState(int);

		void changeTexture(int, int);
		bool checkClick(sf::Vector2i);
		int doTheJob(sf::RenderWindow*, std::vector<Button*>& ,std::vector<Line*>&);


	private:
		sf::Image* Image;
		sf::Vector2i Cords;
		sf::Vector2i Size;
		sf::Texture Texture;
		sf::Vector3i Indexes;
		int *Value;
		int(*fcnptr)(sf::RenderWindow* , std::vector<Button*>& ,std::vector<Line*>&, Button*);
};



#endif
