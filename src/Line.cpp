#include "Line.h"

Line::Line(sf::Vector2f size, sf::Vector2f position , sf::Color color , float rotate){
this-> size = size;
this-> position = position;
this-> color = color;
this-> rotate = rotate;
}

sf::Vector2f Line::getSize(){
	return this-> size;
}

sf::Vector2f Line::getPosition(){
	return this-> position;
}
sf::Color Line::getColor(){
	return this-> color;
}

float Line::getRotate(){
	return this-> rotate;
}

