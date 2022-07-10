#include "Ttransform.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Ttransform::Ttransform()
{
    srand( time( NULL ) );
    Tpixel matrix[IMG_RES][IMG_RES];

    for(int x=0; x < IMG_RES; x++)
    {
        for(int y=0; y< IMG_RES; y++)
        {
            raw_matrix[x][y].set_color(rand()%2);
        }
    }
}

void Ttransform::show()
{
    for(int x=0; x < IMG_RES; x++)
    {
        for(int y=0; y< IMG_RES; y++)
        {
            cout<< raw_matrix[x][y].show_color() << "[" << raw_matrix[x][y].show_x_corrd() <<"]"<<"[" << raw_matrix[x][y].show_y_corrd()  <<"]"<< "  "; 
        }
        cout<< endl;
    }
}

void Ttransform::adjust()
{

}