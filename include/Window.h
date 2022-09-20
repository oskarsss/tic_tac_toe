#ifndef WINDOW
#define WINDOW
#include <SFML/Graphics.hpp>	
#include "Button.h"
#include "Line.h"

class Window{
	public:
	Window(sf::RenderWindow* Window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines);
		
	private:
	
        void drawButton(sf::RenderWindow *window,Button* b);
	void drawLine(sf::RenderWindow *window, Line* l);
	int changeTexture(std::vector<Button*>&, Button*);
	void refreshWindow(sf::RenderWindow* window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines);
};



#endif

