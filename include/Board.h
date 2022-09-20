#ifndef BOARD
#define BOARD

class Board {
	public :

	Board();
	int& get(int a, int b, int c);
	~Board();
	void copy(Board&);

	private:
	
	int* data;
	const int dim_a = 10;
	const int dim_b = 3;
	const int dim_c = 3;
	
};


#endif
