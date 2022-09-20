 
#include "Window.h"
#include <iostream>

Window::Window(sf::RenderWindow* window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines){
	refreshWindow(window,Buttons,Lines);
	int activeField=-1;
	
	while (window->isOpen())
	{
		// Обрабатываем очередь событий в цикле
		sf::Event event;
		while (window->waitEvent(event))
		{			
			if (event.type == sf::Event::Closed){
				window->close(); // тогда закрываем его
				throw "end of game";
			}
			if (event.type != sf::Event::MouseMoved){
				refreshWindow(window,Buttons,Lines);
				window->display();
			}


			if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2i position = sf::Mouse::getPosition();
				sf::Vector2i window_pos = window->getPosition();
				for (auto b : Buttons){
					if(b->checkClick(sf::Vector2i(position.x-window_pos.x,position.y-window_pos.y))){//everything here into job to do
						if (b->getValue()==-1){
							window->close(); 						
						}
						else {
							if (activeField ==-1)
								activeField=b->doTheJob(window,Buttons,Lines);

							if (b->getValue()==0 && b->getIndexes().x==activeField)
								activeField=b->doTheJob(window,Buttons,Lines);
						}
												
					


					}
				}
			}

			
		}
	}
}
void Window::drawButton(sf::RenderWindow *window,Button* b){
	sf::Texture texture;
	texture = b->getTexture();
	
// Создаем спрайт и устанавливаем ему нашу текстуру
	sf::Sprite sprite(texture);

	sprite.move (b->getCords().x,b->getCords().y);
	
	// Отрисовка спрайта	 
	window->draw(sprite);
}
void Window::drawLine(sf::RenderWindow *window, Line* l){
	sf::RectangleShape line (l->getSize());
	line.setPosition(l->getPosition());
	line.setFillColor(l->getColor());
	line.rotate(l->getRotate());
	window->draw(line);


}

void Window::refreshWindow(sf::RenderWindow* window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines){
	window->clear(sf::Color(68,59,49 ));
	for (auto b : Buttons){
		drawButton(window, b);
	}
	for (auto l : Lines){
		drawLine(window,l);
	}
}


