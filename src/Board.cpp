#include "Board.h"
#include <iostream>

Board::Board(){
	data = new int[Board::dim_a * Board::dim_b * Board::dim_c];
}
Board::~Board(){
	delete[] data;
}
int& Board::get(int a, int b, int c) {
	return data[(Board::dim_a-1) * a + (Board::dim_b) * b + c];
}

void Board::copy (Board& b){
	for (int i=0;i<10;++i){
		for(int j =0;j<3;++j){
			for(int x = 0; x<3;++x){
				this->data[i*9+j*3+x] = b.get(i,j,x);
			}
		}
	}
}

