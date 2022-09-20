#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Button.h"
#include "Window.h"
#include "Board.h"
#include "Line.h"
#include "AI.h"

void addLine(std::vector<Line*>& Lines,sf::Vector2f size, sf::Vector2f position, float rotate, sf::Color color = sf::Color::Black){

	Line* line = new Line(size,position, color, rotate);
	Lines.push_back(line);
	return;
}

void checkForPoint( std::vector<Button*>& Buttons,std::vector<Line*>& Lines,Button* b, int player){
	
	//if(*(b->getValueptr()+81-b->getIndexes().x*9)){//if cell is closed
	if(*(b->getValueptr()+81-b->getIndexes().x*8-b->getIndexes().y*3-b->getIndexes().z)){//if cell is closed
		return;
	}
	int cellNr = b->getIndexes().x;
	int start = cellNr*9;
	int arr[3][3];
	for (int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			arr[i][j] = Buttons[start+i*3+j]->getValue();


	for (int i=0;i<3;++i){
		if (arr[0][i]==arr[1][i]&&arr[1][i]==arr[2][i]&&arr[0][i]!=0){
			*(b->getValueptr()+81-b->getIndexes().x*8-b->getIndexes().y*3-b->getIndexes().z)=player;//we are changing, where button is, not where will be
			addLine(Lines, sf::Vector2f(6, 190), sf::Vector2f(cellNr%3*236+85+75*i, cellNr/3*236+43), 0);
			return;

		}
		if (arr[i][0]==arr[i][1]&&arr[i][1]==arr[i][2]&&arr[i][0]!=0){

			*(b->getValueptr()+81-b->getIndexes().x*8-b->getIndexes().y*3-b->getIndexes().z)=player;//we are changing, where button is, not where will be
			addLine(Lines, sf::Vector2f(6, 190), sf::Vector2f(cellNr%3*236+65, cellNr/3*236+68+75*i), -90);
			return;

		}
		if (arr[0][0]==arr[1][1]&&arr[1][1]==arr[2][2]&&arr[0][0]!=0){
			*(b->getValueptr()+81-b->getIndexes().x*8-b->getIndexes().y*3-b->getIndexes().z)=player;//we are changing, where button is, not where will be
			addLine(Lines, sf::Vector2f(6, 225), sf::Vector2f(cellNr%3*236+85, cellNr/3*236+63), -45);
			return;

		}
		if (arr[0][2]==arr[1][1]&&arr[1][1]==arr[2][0]&&arr[0][2]!=0){
			*(b->getValueptr()+81-b->getIndexes().x*8-b->getIndexes().y*3-b->getIndexes().z)=player;//we are changing, where button is, not where will be
			addLine(Lines, sf::Vector2f(6, 225), sf::Vector2f(cellNr%3*236+236, cellNr/3*236+61), 45);
			return;

		}
	}


}

int clickButton (sf::RenderWindow* Window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines, Button* b){




	int compare = b->getIndexes().y*3+b->getIndexes().z; //compare - block (1 of 9) where we are going

	



	int count=0;
	for (int i = 0; i<81;++i){

		if (Buttons[i]->getValue()!=0){
			++count;
		}
	}
	b->setValue(count%2+1);
	checkForPoint(Buttons,Lines,b, count%2+1);

	//AI here compare = 
	int tempcompare=compare;
	compare = getAImove((b->getValueptr()-b->getIndexes().x*9-b->getIndexes().y*3-b->getIndexes().z), compare);

	for (int i=compare*9;i<compare*9+9;++i){
		if (Buttons[i]->getValue()==0)
			break;
		else if (i == compare*9+8)
			std::cout<<"THE END"<<std::endl;std::cout.flush();
			//Window->close(); ////Add endgame window. output is working if add some other cout outer of for loop
	}

	int temp = 0;
	for (int i=0;i<10;++i){
		if (*(Buttons[81]->getValueptr()+1+i)!=0){
			++temp;
		}
	}
	if (temp ==9)
		std::cout<<"END"<<std::endl;std::cout.flush();
		//Window->close();

	
	checkForPoint(Buttons,Lines,Buttons[tempcompare*9], (count+1)%2+1);



	for (int i =0; i<81;++i){
		if (Buttons[i]->getIndexes().x ==compare)
			Buttons[i]->changeTexture(Buttons[i]->getValue()*75,0);
		else 
			Buttons[i]->changeTexture(Buttons[i]->getValue()*75,75);

	}



	return compare;



}
int doNothing (sf::RenderWindow* Window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines, Button* b){
	std::cout<<"Do nothing";
	std::cout.flush();
	return 0;
}
int redo (sf::RenderWindow* Window, std::vector<Button*>& Buttons,std::vector<Line*>& Lines, Button* b){
	Window->close();
	return 0;
}



static void fillValues(Board& GameArray  , std::vector<Button*>& Buttons, std::vector<Line*> Lines){
	static sf::Image image;
	image.loadFromFile("image.png");
	for (int i =0; i<3;++i){
		for (int j=0;j<3;++j){
			for (int y =0;y<3;++y){

				for (int x=0;x<3;++x){
				sf::Vector2i Cords(52+75*x+236*j,28+75*y+236*i);
				sf::Vector2i Size(75,75);
				
				GameArray.get(i*3+j,y,x) = 0; 
				Button* b = new Button(&image, Cords, Size, &GameArray.get(i*3+j,y,x), clickButton);
				Buttons.push_back(b);
				}
			}
		}

	}
	for(int i =0;i<3;++i)
		for (int j =0;j<3;++j)
			GameArray.get(9,i,j) = 0;
	static sf::Image image2;
	image2.loadFromFile("redo.png");	
	Button* b = new Button(&image2, sf::Vector2i (340,750), sf::Vector2i(30,30), new int (-1), redo);
	Buttons.push_back(b);
	return;	
}


int main (){

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;


	

	try{
		while (1){

			sf::RenderWindow window(sf::VideoMode(800,800), "Nested tic tac toe", sf::Style::Titlebar|sf::Style::Close, settings);
			std::vector<Button*> Buttons ;
			Board GameArray;
			std::vector<Line*> Lines ;

			fillValues(GameArray,Buttons, Lines);


			Window main(&window, Buttons, Lines);

		}
	}catch(...){
		std::cout<<"End of game";
	}
	// Главный цикл приложения: выполняется, пока открыто окно
	/*	while (window.isOpen())
		{
	// Обрабатываем очередь событий в цикле
	sf::Event event;
	while (window.waitEvent(event))
	{
	sf::Image image;
	image.loadFromFile("picture.png");
	sf::Vector2i v(50,60);
	sf::Vector2i v1(75,75);
	Button button(&image,v,v1);
	// Пользователь нажал на «крестик» и хочет закрыть окно?
	if (event.type == sf::Event::Closed)
	window.close(); // тогда закрываем его
	if (event.type == sf::Event::MouseButtonPressed){
	sf::vector2i position = sf::mouse::getposition();
	sf::vector2i window_pos = window.getposition();
	//	std::cout<<position.x-window_pos.x << " " << position.y-window_pos.y<<std::endl;
	button.checkclick(sf::vector2i(position.x-window_pos.x,position.y-window_pos.y));
	}
	// Установка цвета фона
	window.clear(sf::Color(68,59,49 ));


	//DrawLine(&window,500 ,150, SuperW, 90); 
	//	DrawLine(&window,100 ,150, 15.4, 0); 
	sf::Text text;

	// select the font
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
	// error...
	}
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("Hello world");

	DrawButton(&window,button);
	// set the character size
	text.setCharacterSize(74); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Red);

	// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.move(150,60);

	// inside the main loop, between window.clear() and window.display()
	window.draw(text);
	// Отрисовка окна
	window.display();
	}


	}

	 */




	return 0;
}
