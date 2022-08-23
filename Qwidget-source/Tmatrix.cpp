#include "Tmatrix.h"
#include <iostream>
#include <time.h>

Tmatrix::Tmatrix(int x, int y) : x_res(x), y_res(y)
{
     matrix = new int *[y_res];

    for (int i =0; i < y_res; i++) 
    {
        matrix[i] = new int [x_res];
    }
    
}

Tmatrix::~Tmatrix()
{
    for(int i=0; i< y_res; i++)
		delete [] matrix[i];
		
	delete [] *matrix;
}

void Tmatrix::setPixel(int x, int y, int val)
{
	matrix[x][y] = val;
}

void Tmatrix::print()
{
	
    for(int y=0; y<y_res ;y++)
	{
		for(int x=0; x< x_res; x++)
		{
			if(matrix[y][x] == 0) std::cout<< "  ";
			if(matrix[y][x] == 1) std::cout<< "* ";
			if(matrix[y][x] == 2) std::cout<< "X ";
			
		}
		std::cout << "\n";
	}
       
}

void Tmatrix::fill_rand()
{
    srand(time(NULL));

    for(int y=0; y<y_res ;y++)
	{
		for(int x=0; x< x_res; x++)
		{
			//wygenerowanie liczb z zakresu [-9; 9]
			matrix[y][x]=1;// rand()%2; 
			
		}
		
	}

}