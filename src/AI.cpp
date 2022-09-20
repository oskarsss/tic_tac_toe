#include <iostream>
#include "AI.h"
#include "Board.h"
#include <cstdlib>


int getAImove(int* start, int compare){
	Board* GameArray = new Board();
	for (int i=0; i<10;++i){
		for (int j=0;j<3;++j){
			for (int x=0;x<3;++x){
				GameArray->get(i,j,x) = *(start+i*9+j*3+x);
			//	std::cout<<GameArray->get(i,j,x)<<"\t";std::cout.flush();
			}
	//	std::cout<<std::endl;
		}
	}
	//std::cout<<"____________________\n";
	int count=0;
	for (int i = 0; i<81;++i){

		if (*(start+i)!=0){
			++count;
		}
	}
	int move = -1;
	std::cout<<findBestMove(5, -10, move, GameArray, compare, count%2)<<std::endl;
	//findBestMove(5, -10, move, GameArray, compare, count%2);
	srand(time(0));
	for (int i =0;i<3;++i){
		for (int j =0; j<3;++j){
			if (GameArray-> get(compare,i,j)==0){
				move = compare *9 + i*3 + j;
			}
		}
	}
	



	*(start + move) = count%2+1;
	//std::cout<<move<<std::endl;
	return (move%9) ;
			


}

int findBestMove(int depth,int value,int& move, Board* b, int compare, bool player){
	if (depth == 0 ){
		return value;
	}

	value = 0;
	for (int i=0;i<3;++i){
		for (int j=0;j<3;++j){
			if (b->get(9,i,j) ==player +1)
				value+=10;
			else if (b->get(9,i,j) == !player +1)
				value-=10;
		}
	}/*
	for (int i=0;i<9;++i){
		for (int j=0;j<2;++j){
			for (int x=0;x<2;++x){
				if (b->get(9,i/3,i%3==0)){

					if (b->get(i,j,x)==b->get(i,j+1,x)&&b->get(i,j,x)==player+1) {
						++value;
					}
					if (b->get(i,j,x)==b->get(i,j,x+1)&&b->get(i,j,x)==player+1){
						++value;
					}
					if (b->get(i,j,x)==b->get(i,j+1,x)&&b->get(i,j,x)==!player+1) {
						--value;
					}
					if (b->get(i,j,x)==b->get(i,j,x+1)&&b->get(i,j,x)==!player+1){
						--value;
					}

				}
			}
		}
	}
*/

		int temp;
	for (int i=0;i<3;++i){
		for (int j=0;j<3;++j){
			if (b->get(compare, i, j) == 0){
				Board* b1 = new Board();
				b1->copy(*b);
				b1->get(compare,i,j) = player;
				checkForPoints(b1,player);
				//std::cout<<value<<std::endl;
				if (temp = findBestMove(depth-1,value,move, b1, i*3+j, !player)>value){
					value = temp;
					move = compare*9+i*3+j;
					if(value!=1);
					std::cout<<move<<"\t"<<value<<std::endl;
				}	
			}

		}
	}
	return value;







}


void checkForPoints(Board* b, bool player){
	for(int i=0;i<9;++i){
		for(int j=0; j<3;++j){

			if (b->get(i,0,j)==b->get(i,1,j)&&b->get(i,1,j)==b->get(i,2,j)&&b->get(i,0,j)!=0){
				b->get(9,i/3,i%3)=player+1;//we are changing, where button is, not where will be
				return;

			}
			if (b->get(i,j,0)==b->get(i,j,1)&&b->get(i,j,1)==b->get(i,j,2)&&b->get(i,j,0)!=0){

				b->get(9,i/3,i%3)=player+1;//we are changing, where button is, not where will be
				return;

			}
			if (b->get(i,0,0)==b->get(i,1,1)&&b->get(i,1,1)==b->get(i,2,2)&&b->get(i,0,0)!=0){
				b->get(9,i/3,i%3)=player+1;//we are changing, where button is, not where will be
				return;

			}
			if (b->get(i,0,2)==b->get(i,1,1)&&b->get(i,1,1)==b->get(i,2,0)&&b->get(i,0,2)!=0){
				b->get(9,i/3,i%3)=player+1;//we are changing, where button is, not where will be
				return;

			}


		}
	}
}

