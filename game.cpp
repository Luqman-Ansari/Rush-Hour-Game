//============================================================================
// Name        : i210413_E_PFproject.cpp
// Author      : M. Luqman Ansari
// Version     : Latest
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>
#include <time.h>

using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//Initiallizing and declaring all Global Variables
int xI = 48, yI = 752;
int const SIZE_WALL = 148;
int walls[SIZE_WALL]={0};
int obstacle[14]={0};
int score=1;

//random cars axis
int R_car1x = 86 , R_car1y = 410  ;	
int R_car2x = 428, R_car2y = 106  ;
int R_car3x = 580, R_car3y = 334  ;
int R_car4x = 580, R_car4y = 752  ;

//Variables for Storing passenger Coordinates
int pass1x = 1, pass1y = 1;
int pass2x = 1, pass2y = 1;
int pass3x = 1, pass3y = 1;
int pass4x = 1, pass4y = 1;
int car ; // 1 is RED and 2 is Yellow
int speed = 180, pass_count = 0, show_car=0;


//Bool to print indication to print green boxes for destination
bool D_indicator1 = true;
bool D_indicator2 = true;
bool D_indicator3 = true;
bool D_indicator4 = true;

//bool to avoid picking more than one passengers
bool check = true; 

//Variables for Storing destination coordinates
int dest1x = 1, dest1y = 1;
int dest2x = 1, dest2y = 1;
int dest3x = 1, dest3y = 1;
int dest4x = 1, dest4y = 1;

//Variables for storing obstacles coordinates
int bx1 , by1, bx2, by2, bx3, by3,
tx1, ty1, tx2, ty2, tx3, ty3, tx4, ty4;

//Variable which manages the screen to show up
int display_count = 1;

//Name of the Player
string name;

// Timer Variable:
int game_time = 180;

//Function for drawing the Car at x, y coordinate:
void drawCar(int x, int y,float *a) {
	DrawCircle(x,y-3, 5,colors[BLACK]);
	DrawCircle(x+13,y-3, 5,colors[BLACK]);
	DrawSquare(x, y, 11, a);
	DrawSquare(x, y+7, 16, a);
	DrawSquare(x+13, y, 11, a);
	DrawSquare(x-9, y, 11, a);
	DrawSquare(x+10, y, 11, a );
	
	glutPostRedisplay();
}

//Function for drawing Trees at x,y coordinates
void drawTree(int a, int b){
	int tx1=a-4 , ty1=b+22 ,tx2 = a+18 ,ty2 = b+22 ,tx3 = a+7 ,ty3 = b+29;
	DrawTriangle(tx1,ty1,tx2,ty2,tx3,ty3,colors[GREEN]);
	DrawRectangle(tx1+6,ty1-33,9,25, colors[BROWN]);
	DrawTriangle(tx1-6,ty1-15,tx2+6,ty2-15,tx3,ty3-7, colors[GREEN]);
	
}

// Function that validates if Randomly generated coordinates of passenger
// are not the coordinates of any other thing
void validationForPassenger( int &a, int &b, int px1, int py1, int px2, int py2, int px3, int py3, int j )
{
	for( int i = 0; i < SIZE_WALL ; i += 2)
	{
		if ( a == walls[i] +12 and b == walls[i+1] + 11)
		{
			a = 48 + 38*GetRandInRange( 0, 20 );
			b = 30 + 38*GetRandInRange( 0, 20 );
		}
	}
	
	for( int i = 0; i < 14; i += 2 )
	{
		if ( a == obstacle[i] and b == obstacle [i+1] )
		{
			a = 48 + 38*GetRandInRange( 0, 20 );
			b = 30 + 38*GetRandInRange( 0, 20 );
		}
	}
	
	if( a == 48 and b == 752 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
		
	if( a == R_car1x )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( b == R_car2y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == px1 and b == py1 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == px2 and b == py2 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == px3 and b == py3 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if ( b == R_car3y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if ( b == R_car4y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if ( j == 1 )
		validationForPassenger( a, b, px1, py1, px2, py2, px3, py3, j = 2 ); //recurring a function
	
}

// Function that validates if Randomly generated coordinates of 
// an obstacle are not the coordinates of any other thing

void validationForObstacle( int &a, int &b, int ox1, int oy1, int ox2, int oy2, int ox3, int oy3, int ox4, int oy4, int ox5, int oy5, int ox6, int oy6,  int j )
{
	if( a == 48 and b == 752 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
		
	if( a == R_car1x )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( b == R_car2y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox1 and b == oy1 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox2 and b == oy2 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox3 and b == oy3 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox4 and b == oy4 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox5 and b == oy5 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == ox6 and b == oy6 )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if ( b == R_car3y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if ( b == R_car4y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	for( int i = 0; i < SIZE_WALL ; i += 2)
	{
		if ( a == walls[i] +12 and b == walls[i+1] + 11)
		{
			a = 48 + 38*GetRandInRange( 0, 20 );
			b = 30 + 38*GetRandInRange( 0, 20 );
		}
	}
	
	if ( j == 1 )
		validationForObstacle( a, b, ox1, oy1, ox2, oy2, ox3, oy3, ox4, oy4, ox5, oy5, ox6, oy6, j=2 ); 	//recurring a function
	
}
//.....................................

// Function that validates if Randomly generated coordinates of
// Destination are not the coordinates of any other thing
void validationForDestination( int &a, int &b, int j )
{
	
	for( int i = 0; i < SIZE_WALL ; i += 2)
	{
		if( ( a == walls[i] + 12) and ( b == walls[i+1] + 11) )
		{
			a = 48 + 38*GetRandInRange( 0, 20 );
			b = 30 + 38*GetRandInRange( 0, 20 );
		}
	}
	
	for( int i = 0; i < 14; i += 2 )
	{
		if ( a == obstacle[i] and b == obstacle [i+1] )
		{
			a = 48 + 38*GetRandInRange( 0, 20 );
			b = 30 + 38*GetRandInRange( 0, 20 );
		}
		
	}

	if( a == pass1x and b == pass1y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == pass2x and b == pass2y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( a == pass3x and b == pass3y )
	{
		a = 48 + 38*GetRandInRange( 0, 20 );
		b = 30 + 38*GetRandInRange( 0, 20 );
	}
	
	if( j == 1)
		validationForDestination( a, b, j = 2 );	// recurring the function
		
	j++ ;
}

// Function for drawing box at x, y coordinates
void drawBox( int a, int b)
{
	DrawSquare( a-8, b - 7, 30, colors[BURLY_WOOD] );
	DrawLine(a+7, b-7, a+7, b+22, 2, colors[SADDLE_BROWN]);
	DrawLine(a-8, b+8, a+22, b+8, 2, colors[SADDLE_BROWN]);
}

//Function for calculating scores for collision
int score_negative( int scr )
{
	//***score reduction for obstacle collision***
	//for red car
	for ( int i =0; i< 14; i++)
	{
		if ( xI == obstacle[i] and yI == obstacle[i+1] and car == 1 )
			scr -= 2;
	}	
	
	//for yellow car
	for ( int i =0; i< 14; i++)
	{
		if ( xI == obstacle[i] and yI == obstacle[i+1] and car == 2 )
			scr -= 4;
	}	
		
	//***score reduction for car collision***
	//for red car
	if(( xI == R_car1x and (yI >= R_car1y-30 and yI <= R_car1y+30 )) or (( xI >= R_car2x -30 and xI <= R_car2x+30) and yI == R_car2y ) or (( xI >= R_car3x -30 and xI <= R_car3x+30 )and yI == R_car3y ) or (( xI >= R_car4x -30 and xI <= R_car4x+30 )and yI == R_car4y ) and car == 1)
		scr -= 3;
	// for yellow car
	if(( xI == R_car1x and (yI >= R_car1y-30 and yI <= R_car1y+30 )) or (( xI >= R_car2x -30 and xI <= R_car2x+30) and yI == R_car2y ) or (( xI >= R_car3x -30 and xI <= R_car3x+30 )and yI == R_car3y ) or (( xI >= R_car4x -30 and xI <= R_car4x+30 )and yI == R_car4y ) and car == 2)
		scr -= 2;
		
	//***score reduction for Passenger collision***
	if( (xI == pass1x and yI == pass1y) or (xI == pass2x and yI == pass2y) or (xI == pass3x and yI == pass3y) or (xI == pass4x and yI == pass4y) )
		scr -= 5;
		
	return scr;
}

// Function for drawing passengers at x, y coordinates
void drawPassenger( int a, int b)
{
	DrawLine( a+8, b+3 , a+8, b+18 , 2, colors[BLACK] );
	DrawLine(a+2 , b-8 , a+8, b+3  , 2, colors[BLACK] ); 
	DrawLine(a+14, b-8 , a+8, b+3  , 2, colors[BLACK] ); 
	DrawLine(a+2 , b+3 , a+8, b+10 , 2, colors[BLACK] ); 
	DrawLine(a+14, b+3 , a+8, b+10 , 2, colors[BLACK] ); 
	DrawCircle( a+8, b+16  , 5, colors[BLACK]);
}

//function that draws all the walls and store there x,y coordinates in an array 
void drawWalls()
{
	int j=0;
	for(int i=0; i<3; i++)
	{	
		int x1= 124-12+38*i, y1= 676-11;
		DrawSquare( x1 , y1 , 39, colors[BLACK] );
		walls[j] = x1;
		walls[j+1] = y1;
		j=j+2;
	}
	
	for(int i=0; i<11; i++)
	{
		int x2= 390-12+38*i, y2 = 676-11;
		DrawSquare( x2 , y2 ,39 , colors[BLACK] );
		DrawSquare( x2+5,y2 ,39 , colors[BLACK] );
		walls[j] = x2;
		walls[j+1] = y2;
		j=j+2;
	}
	
	int x3= 314-12, y3= 638-11;
	DrawSquare( x3 , y3 ,39 , colors[BLACK] );
	walls[j] = x3;
	walls[j+1] = y3;
	j=j+2;
	
	int x4 = 314-12, y4 = 600-11;
	DrawSquare( x4 , y4 ,39 , colors[BLACK] );
	walls[j] = x4;
	walls[j+1] = y4;
	j=j+2;
	
	int x5 = 314-12, y5 = 562-11;
	DrawSquare( x5 , y5 ,39 , colors[BLACK] );	
	walls[j] = x5;
	walls[j+1] = y5;
	j=j+2;
	
	int x6 = 504-12, y6 = 600-11;  
	DrawSquare( x6 , y6 ,39 , colors[BLACK] );
	walls[j] = x6;
	walls[j+1] = y6;
	j=j+2;
	
	int x7= 504-12, y7= 562-11; 
	DrawSquare( x7 , y7 ,39 , colors[BLACK] );
	walls[j] = x7;
	walls[j+1] = y7;
	j=j+2;
	
	int x8 = 504-12, y8 =  524-11;
	DrawSquare( x8 , y8 ,39 , colors[BLACK] );
	walls[j] = x8;
	walls[j+1] = y8;
	j=j+2;

	int x9= 504-12, y9= 486-11;
	DrawSquare( x9 , y9 ,39 , colors[BLACK] );
	walls[j] = x9;
	walls[j+1] = y9;
	j=j+2;
	
	int x10= 504-12, y10= 448-11;
	DrawSquare( x10 , y10 ,39 , colors[BLACK] );
	walls[j] = x10;
	walls[j+1] = y10;
	j=j+2;
	
	int x11 = 504-12, y11 = 410-11;  
	DrawSquare( x11 , y11 ,39 , colors[BLACK] );
	walls[j] = x11;
	walls[j+1] = y11;
	j=j+2;
	
	
	int x12 = 732-12, y12 = 600-11 ;
	DrawSquare( x12 , y12 ,39 , colors[BLACK] );
	walls[j] = x12;
	walls[j+1] = y12;
	j=j+2;
	
	int x13= 732-12, y13= 562-11;
	DrawSquare( x13 , y13 ,39 , colors[BLACK] );
	walls[j] = x13;
	walls[j+1] = y13;
	j=j+2;
	
	int x14 = 732-12, y14 = 524-11;
	DrawSquare( x14 , y14 ,39 , colors[BLACK] );
	walls[j] = x14;
	walls[j+1] = y14;
	j=j+2;
	
	int x15= 732-12 , y15= 486-11  ;
	DrawSquare( x15 , y15 ,39 , colors[BLACK] );
	walls[j] = x15;
	walls[j+1] = y15;
	j=j+2;
	
	int x16 = 732-12 , y16 = 448-11;
	DrawSquare( x16 , y16 ,39 , colors[BLACK] );
	walls[j] = x16;
	walls[j+1] = y16;
	j=j+2;
	
	
	int x17= 162-12 , y17= 486-11;
	DrawSquare( x17 , y17 ,39 , colors[BLACK] );
	walls[j] = x17;
	walls[j+1] = y17;
	j=j+2;
	
	int x18= 162-12, y18= 448-11;
	DrawSquare( x18 , y18 ,39 , colors[BLACK] );
	walls[j] = x18;
	walls[j+1] = y18;
	j=j+2;
	
	
	int x19 = 390-12, y19 = 410-11;
	DrawSquare( x19 , y19 ,39 , colors[BLACK] );
	walls[j] = x19;
	walls[j+1] = y19;
	j=j+2;
	
	int x20 = 390-12, y20= 486-11;
	DrawSquare( x20 , y20 ,39 , colors[BLACK] );
	walls[j] = x20;
	walls[j+1] = y20;
	j=j+2;
	
	
	int x21= 238-12 , y21 = 334-11 ;
	DrawSquare( x21 , y21 ,39 , colors[BLACK] );
	walls[j] = x21;
	walls[j+1] = y21;
	j=j+2;
	
	int x22= 238-12 , y22 = 296-11 ;
	DrawSquare( x22 , y22 ,39 , colors[BLACK] );
	walls[j] = x22;
	walls[j+1] = y22;
	j=j+2;
	
	int x23 = 238-12 , y23 = 258-11;
	DrawSquare( x23 , y23 ,39 , colors[BLACK] );
	walls[j] = x23;
	walls[j+1] = y23;
	j=j+2;
	
	int x24= 238-12 , y24= 220-11 ;
	DrawSquare( x24 , y24 ,39 , colors[BLACK] );
	walls[j] = x24;
	walls[j+1] = y24;
	j=j+2;
	
	int x25= 238-12,  y25= 182-11 ;
	DrawSquare( x25, y25 ,39 , colors[BLACK] );
	walls[j] = x25;
	walls[j+1] = y25;
	j=j+2;
	
	int x26 = 238-12 , y26 = 144-11;
	DrawSquare( x26 , y26 ,39 , colors[BLACK] );
	walls[j] = x26;
	walls[j+1] = y26;
	j=j+2;
	
	int x27 = 238-12, y27 = 106-11 ;
	DrawSquare( x27 , y27 ,39 , colors[BLACK] );
	walls[j] = x27;
	walls[j+1] = y27;
	j=j+2;
	
	
	int x28= 466-12 , y28 = 296-11 ;
	DrawSquare( x28 , y28 ,39 , colors[BLACK] );
	walls[j] = x28;
	walls[j+1] = y28;
	j=j+2;
	
	int x29 = 466-12 , y29 = 258-11 ;
	DrawSquare( x29 , y29 ,39 , colors[BLACK] );
	walls[j] = x29;
	walls[j+1] = y29;
	j=j+2;
	
	int x30 = 580-12 , y30 = 144-11 ;
	DrawSquare( x30 , y30 ,39 , colors[BLACK] );
	walls[j] = x30;
	walls[j+1] = y30;
	j=j+2;
	
	int x31 = 580-12 , y31 = 182-11 ;
	DrawSquare( x31 , y31 ,39 , colors[BLACK] );
	walls[j] = x31;
	walls[j+1] = y31;
	j=j+2;
	
	int x32= 580-12 , y32 = 220-11 ;
	DrawSquare( x32 , y32 ,39 , colors[BLACK] );
	walls[j] = x32;
	walls[j+1] = y32;
	j=j+2;
	
	
	
	
	for(int i=0; i<2; i++)
	{
		int x33= 124-12+38*i , y33= 524-11 ;
		DrawSquare( x33 , y33 ,39 , colors[BLACK] );
		walls[j] = x33;
		walls[j+1] = y33;
		j=j+2;
	}
	
	for(int i=0; i<3; i++)
	{
		int x34= 238-12+38*i , y34= 524-11 ;
		DrawSquare( x34 , y34 ,39 , colors[BLACK] );
		walls[j] = x34;
		walls[j+1] = y34;
		j=j+2;
	}
	
	for(int i=0; i<3; i++)
	{
		int x35= 542-12+38*i , y35= 524-11 ;
		DrawSquare( x35 , y35 ,39 , colors[BLACK] );
		walls[j] = x35;
		walls[j+1] = y35;
		j=j+2;
	}
	
	for(int i=0; i<2; i++)
	{
		int x36= 694-12+38*i , y36= 68-11 ;
		DrawSquare( x36 , y36 ,39 , colors[BLACK] );
		walls[j] = x36;
		walls[j+1] = y36;
		j=j+2;
	}
	
	for(int i=0; i<6; i++)
	{
		int x37 = 580-12+38*i , y37 = 258-11 ;
		DrawSquare( x37 , y37 ,39 , colors[BLACK] );
		DrawSquare( x37+5 , y37 ,39 , colors[BLACK] );
		walls[j] = x37;
		walls[j+1] = y37;
		j=j+2;
	}
	
	for(int i=0; i<5; i++)
	{
		int x38=314-12+38*i , y38 = 220-11 ;
		DrawSquare( x38 , y38 ,39 , colors[BLACK] );
		walls[j] = x38;
		walls[j+1] = y38;
		j=j+2;
	}
	
	for(int i=0; i<3; i++)
	{
		int x39= 314-12+38*i , y39 = 372-11 ;
		DrawSquare( x39 , y39 ,39 , colors[BLACK] );
		walls[j] = x39;
		walls[j+1] = y39;
		j=j+2;
	}
	
	for(int i=0; i<2; i++)
	{
		int x40 = 124-12+38*i , y40 = 258-11 ;
		DrawSquare( x40 , y40 ,39 , colors[BLACK] );
		walls[j] = x40;
		walls[j+1] = y40;
		j=j+2;
	}
	
	for(int i=0; i<2; i++)
	{
		int x41 = 124-12+38*i , y41 = 220-11 ;
		DrawSquare( x41 , y41 ,39 , colors[BLACK] );
		walls[j] = x41;
		walls[j+1] = y41;
		j=j+2;
	}
	
	for(int i=0; i<2; i++)
	{
		int x42 = 124-12+38*i , y42 = 182-11 ;
		DrawSquare( x42 , y42 ,39 , colors[BLACK] );
		walls[j] = x42;
		walls[j+1] = y42;
		j=j+2;
	}
}

// Function that draws all the obstacles and store their x-y coordinates in an array
void drawObstacle()
{
	drawBox( bx1, by1 );
	drawBox( bx2, by2 );
	drawBox( bx3, by3 );
	
	drawTree(tx1, ty1);
	drawTree(tx2, ty2);
	drawTree(tx3, ty3);
	drawTree(tx4, ty4);
	
	int k = 0;
	obstacle[k]= bx1;
	obstacle[k+1]= by1;
	k+=2;
	obstacle[k]= bx2;
	obstacle[k+1]= by2;
	k+=2;
	obstacle[k]= bx3;
	obstacle[k+1]= by3;
	k+=2;
	obstacle[k]= tx1;
	obstacle[k+1]= ty1;
	k+=2;
	obstacle[k]= tx2;
	obstacle[k+1]= ty2;
	k+=2;
	obstacle[k]= tx3;
	obstacle[k+1]= ty3;
	k+=2;
	obstacle[k]= tx4;
	obstacle[k+1]= ty4;
	k+=2;
}

//Function for drawing the start Page
void start_page()
{
	
	DrawString( 79, 660, "Welcome to RUSH HOUR!", colors[WHITE]);
	DrawString( 85, 620, "Made by Luqman Ansari_i210413", colors[WHITE]);
	DrawString( 100, 450, "Press 'X' to continue!", colors[WHITE]);
	
}

//Function for drawing the menu page
void menu_page()
{
	DrawRectangle( 0, 730, 1500, 60, colors[BLACKO]);
	DrawString( 450, 750," MENU", colors[WHITE]);
	DrawRoundRect(350, 460, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 425, 500," PLAY GAME", colors[WHITE]);
	DrawRoundRect(350, 260, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 410, 300," LEADER BOARD\n", colors[WHITE]);
}

//Function for drawing page that shows Player's Name
void name_page()
{
	DrawRectangle( 0, 730, 1500, 60, colors[BLACKO]);
	DrawString( 450, 750," Name: ", colors[WHITE]);
	DrawString( 240, 600," Your Name:", colors[WHITE]);
	DrawRoundRect(350, 360, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 450, 400,name, colors[WHITE]);
}

//Function for Drawing Car Selection Page
void car_page()
{
	DrawRectangle( 0, 730, 1500, 60, colors[BLACKO]);
	DrawString( 450, 750," Car Selection: ", colors[WHITE]);
	DrawString( 420, 650," Select Your Car: ", colors[WHITE]);
	DrawRoundRect(350, 460, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 435, 500," RED CAR", colors[WHITE]);
	DrawRoundRect(350, 260, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 410, 300," YELLOW CAR", colors[WHITE]);
	DrawRoundRect(350, 60, 300, 100, colors[SLATE_GRAY], 10 );
	DrawString( 410, 100," RANDOM CAR", colors[WHITE]);
}

//Function for drawing all the maps, passengers, walls and cars for the game display
void game_page()
{
	DrawRectangle( 0, 795, 1500, 60, colors[BLACK]);
	DrawString( 450, 815," Lets Play! ", colors[WHITE]);
	DrawString( 830, 500, "Passenger Satus: ", colors[BLACK]);
	//Display Score
	DrawString( 850, 770, "Score = ", colors[BLACK]);
	DrawString( 940, 770, Num2Str(score) , colors[BLACK]);
	
	DrawString( 860, 570, " Timer:  " , colors[BLACK]) ;
	DrawString( 950, 570, Num2Str(game_time) , colors[BLACK]) ;
	DrawString( 986, 570, "s" , colors[BLACK]) ;
		
	//**************BORDERS********************
	DrawLine( 30  , 10  , 30  , 790 , 13 , colors[BLACK] );//left border
	DrawLine( 805 , 10  , 805 , 790 , 13 , colors[BLACK] );//right border
	DrawLine( 30  , 10  , 805 , 10  , 13 , colors[BLACK] );//lower border
	DrawLine( 30  , 790 , 805 , 790 , 13 , colors[BLACK] );//upper border
	
	//*************LINES FOR ROAD*************
	
	for( int i = 0; i <19 ; i++)
	{
		int L_x = 74 + 38*i;
		DrawLine( L_x  , 790 , L_x  , 10  , 1  , colors[BLACK] );
	}
		
	//***********walls*************
	
	drawWalls();
		
	drawPassenger( pass1x, pass1y );
	drawPassenger( pass2x, pass2y );	
	drawPassenger( pass3x, pass3y );
	drawPassenger( pass4x, pass4y );
	
	if ( !D_indicator1 )
	{
		DrawSquare( dest1x-12, dest1y-11, 38 , colors[DARK_GREEN]);
		DrawString( 850, 450, "Picked ", colors[GREEN]);
	}
	
	if ( !D_indicator2 )
	{
		DrawSquare( dest2x-12, dest2y-11, 38 , colors[DARK_GREEN]);
		DrawString( 850, 450, "Picked ", colors[GREEN]);
	}
		
	if ( !D_indicator3 )
	{
		DrawSquare( dest3x-12, dest3y-11, 38 , colors[DARK_GREEN]);
		DrawString( 850, 450, "Picked ", colors[GREEN]);
	}
	
	if ( !D_indicator4 )
	{
		DrawSquare( dest4x-12, dest4y-11, 38 , colors[DARK_GREEN]);
		DrawString( 850, 450, "Picked ", colors[GREEN]);
	}
		
	drawObstacle();
	
	drawCar( R_car1x , R_car1y , colors[GREEN]);
	drawCar( R_car2x , R_car2y , colors[ROYAL_BLUE]);
	drawCar( R_car3x , R_car3y , colors[THISTLE]);
	
	if( show_car >= 1)
		drawCar( R_car4x , R_car4y , colors[THISTLE]);
		

	if( car == 1)
		drawCar(xI,yI,colors[RED]);
	
	if( car == 2 )
		drawCar(xI,yI,colors[GOLD]);
		

}

//Function for displaying Total Score at the End
void end_page()
{
	DrawRectangle( 0, 730, 1500, 60, colors[BLACKO]);
	DrawString( 450, 750," TOTAL SCORE ", colors[WHITE]);
	DrawString( 390, 600,"Your Time Ended...", colors[WHITE]);
	DrawString( 390, 550,"Your Total Score Was:", colors[WHITE]);
	DrawRoundRect(420, 410, 100, 100, colors[SLATE_GRAY], 10 );
	DrawString( 470, 450, Num2Str(score), colors[WHITE]);

	if ( score >= 100 )
		DrawString( 350, 300,"Congratulations! You have Won!", colors[WHITE]);
	else
		DrawString( 350, 300,"You Failed! Better Luck Next Time", colors[WHITE]);
	DrawString( 800, 50,"Press [Esc] to exit.", colors[WHITE]);
}

//Function for displaying leaderboard
void leaderboard_page()
{
	DrawRectangle( 0, 730, 1500, 60, colors[BLACKO]);
	DrawString( 450, 750," LEADERBOARDS ", colors[WHITE]);
	DrawString( 100, 550,"1. ", colors[WHITE]);
	DrawString( 100, 510,"2. ", colors[WHITE]);
	DrawString( 100, 470,"3. ", colors[WHITE]);
	DrawString( 100, 430,"4. ", colors[WHITE]);
	DrawString( 100, 390,"5. ", colors[WHITE]);
	DrawString( 100, 350,"6. ", colors[WHITE]);
	DrawString( 100, 310,"7. ", colors[WHITE]);
	DrawString( 100, 270,"8. ", colors[WHITE]);
	DrawString( 100, 230,"9. ", colors[WHITE]);
	DrawString( 100, 190,"10. ", colors[WHITE]);
}

// Function used for moving cars other than Player's Taxi
bool flag1 = true;
bool flag2 = true;
bool flag3 = true;
bool flag4 = true;
void moveCar( int &m, int upper_limit, int lower_limit, bool &flag ) {
	int MOVE = 10;
	if (m > 10 && flag) {
		m  -= MOVE;
		//cout << "going down"<<endl;
		if(m  < lower_limit )
			
			flag = false;

	}
	else if (m  < 1010 && !flag) {
		//cout << "go up"<<endl;
		m  += MOVE;
		if (m  > upper_limit)
			flag = true;
	}	
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	InitRandomizer();
	
	
	if( display_count == 1)		//Displays Start Page
	{
	glClearColor(0, 0, 0, 0 /*Alpha component*/); 
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			
		start_page();
		
	}	
	
	if( display_count == 2)		//Displays Menu
	{
		glClearColor(0, 0, 0, 0 /*Alpha component*/); 
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			
		menu_page();
	}
		
	if( display_count == 3)		//Displays Name page
	{
		glClearColor(0, 0, 0, 0 /*Alpha component*/); 
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			
		name_page();
	}	
	
	if( display_count == 4 )		//Displays Car's Page
	{
		glClearColor(0, 0, 0, 0 /*Alpha component*/); 
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			
		car_page();
	}
	
	if( display_count == 5)		//Displays Game Page
	{
		glClearColor(0.827, 0.827, 0.827, 0 /*Alpha component*/); 
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		
		game_page();
	}	
	
	if( display_count == 6 )		//Displays End Page
	{
		glClearColor(0, 0, 0, 0 /*Alpha component*/); 
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
		end_page();
	}
	
	if( display_count == 7 )
	{
		glClearColor(0, 0, 0, 0 /*Alpha component*/); 
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
		leaderboard_page();
	}
	
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
 
void NonPrintableKeys(int key, int x, int y) {
	int MOVE;
	
	if( car == 1)
		MOVE = 19;
	
	if( car == 2 )
		MOVE = 38;
	
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) 
	{
		xI -= MOVE;
		cout<<"\nLeft key is Pressed";
		
		for( int i =0; i < SIZE_WALL ; i+=2)		//check for wall collision
			{
			if( xI - 12 == walls[i] and yI - 11 == walls[i+1])
				{
					cout<<"\n*You can't move throuh Walls*";
					xI += MOVE;
				}
		}
		score=score_negative( score );
	} 
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{	
		xI += MOVE;
		cout<<"\nRight key is Pressed";
		
		for( int i =0; i < SIZE_WALL ; i+=2)		//check for wall collision
			{
			if( xI - 12 == walls[i] and yI - 11 == walls[i+1])
				{
					cout<<"\n*You can't move throuh Walls*";
					xI -= MOVE;
				}
		}
		score=score_negative( score );
		
	}
	 else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
	{
		yI += MOVE;
		cout<<"\nUp key is Pressed";
		
		for( int i =0; i < SIZE_WALL ; i+=2)			//check for wall colision
		{
			if( xI - 12 == walls[i] and yI - 11 == walls[i+1])
				{
					cout<<"\n*You can't move throuh Walls*";
					yI -= MOVE;
				}
		}
		score=score_negative( score );
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) 
	{	
		yI -= MOVE;
		cout<<"\nDown key is Pressed";
		
		for( int i =0; i < SIZE_WALL ; i+=2)		//check for wall colision
		{
			if( xI - 12 == walls[i] and yI - 11 == walls[i+1])
				{
					cout<<"\n*You can't move throuh Walls*";
					yI += MOVE;
				}
		}
		score=score_negative( score );
	}
	
	//keeps the car in the board
	if( xI < 30 )
	{
		cout<<"\n*You cant go outside playing area*";
		xI = xI + MOVE; 
	}
	
	if( xI > 805 )
	{
		cout<<"\n*You cant go outside playing area*";
		xI = xI - MOVE; 
	}
	
	if( yI < 10 )
	{
		cout<<"\n*You cant go outside playing area*";
		yI = yI + MOVE; 
	}
	
	if( yI > 763 )
	{
		cout<<"\n*You cant go outside playing area*";
		yI = yI - MOVE; 
	}
	
	
	
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	//cout<<endl<<xI<<endl<<yI<<endl;
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
 
void PrintableKeys(unsigned char key, int x, int y) {
	InitRandomizer();
	int i = 1;
	
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	
	if (key == 120 || key == 88 /* X key ASCII*/) {
		display_count = 2;
			
	}	

	if (key == 32 /* Space Bar ASCII*/)
	{
		// Checks if car is in range of passenger
		if (check and( ( xI == pass1x and yI == pass1y + 38) or ( xI == pass1x and yI == pass1y - 38 ) or ( xI == pass1x - 38 and yI == pass1y ) or ( xI == pass1x + 38 and yI == pass1y)))
		{
			check = false;
			pass1x = 1000;
			pass1y = 1000;
			D_indicator1 = false;
		}
		
		//checks if car is on destination area
		if ( !D_indicator1  and xI == dest1x and yI == dest1y)
		{
			D_indicator1 = true; 
			pass_count ++;
			check = true;
			pass1x = 48 + 38*GetRandInRange( 0, 20 );
			pass1y = 30 + 38*GetRandInRange( 0, 20 );
			score += 10;
			
			validationForPassenger( pass1x, pass1y, pass2x, pass2y, pass3x, pass3y, pass4x, pass4y, i );
		}
		
		// Checks if car is in range of passenger
		if (check and (( xI == pass2x and yI == pass2y + 38) or ( xI == pass2x and yI == pass2y - 38 ) or ( xI == pass2x - 38 and yI == pass2y ) or ( xI == pass2x + 38 and yI == pass2y)))
		{
			check = false;
			pass2x = 1000;
			pass2y = 1000;
			D_indicator2 = false;
		}
		
		//checks if car is in destination area
		if ( !D_indicator2  and xI == dest2x and yI == dest2y)
		{
			check = true;
			pass_count ++;
			D_indicator2 = true; 
			pass2x = 48 + 38*GetRandInRange( 0, 20 );
			pass2y = 30 + 38*GetRandInRange( 0, 20 );
			score += 10;
			validationForPassenger( pass2x, pass2y,  pass1x, pass1y, pass3x, pass3y, pass4x, pass4y, i );
		}
		
		// Checks if car is in range of passenger
		if (check and (( xI == pass3x and yI == pass3y + 38) or ( xI == pass3x and yI == pass3y - 38 ) or ( xI == pass3x - 38 and yI == pass3y ) or ( xI == pass3x + 38 and yI == pass3y)))
		{
			check = false;
			pass3x = 1000;
			pass3y = 1000;
			D_indicator3 = false;
		}
		
		//Checks if car is in destination area
		if ( !D_indicator3  and xI == dest3x and yI == dest3y)
		{
			check = true;
			pass_count ++;
			D_indicator3 = true; 
			pass3x = 48 + 38*GetRandInRange( 0, 20 );
			pass3y = 30 + 38*GetRandInRange( 0, 20 );
			score += 10;
			validationForPassenger( pass3x, pass3y, pass2x, pass2y, pass1x, pass1y, pass4x, pass4y, i );
		}
		
		// Checks if car is in range of passenger
		if (check and (( xI == pass4x and yI == pass4y + 38) or ( xI == pass4x and yI == pass4y - 38 ) or ( xI == pass4x - 38 and yI == pass4y ) or ( xI == pass4x + 38 and yI == pass4y)))
		{
			check = false;
			pass4x = 1000;
			pass4y = 1000;
			D_indicator4 = false;
		}
		
		//checks if car is in destination area
		if ( !D_indicator4  and xI == dest4x and yI == dest4y)
		{
			check = true;
			pass_count ++;
			D_indicator4 = true; 
			pass4x = 48 + 38*GetRandInRange( 0, 20 );
			pass4y = 30 + 38*GetRandInRange( 0, 20 );
			score += 10;
			validationForPassenger( pass4x, pass4y, pass2x, pass2y, pass3x, pass3y, pass1x, pass1y, i );
		}
		//Increases speed for every two drops of passenger
		if(pass_count != 0)
		{
			if ( pass_count % 2 == 0 )
			{
				if(speed > 10)
					speed -= 10;
				show_car ++;
			}
		}
			
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// Move Other Cars
	moveCar( R_car1y, 676, 106, flag1 );
	moveCar( R_car2x, 580, 280, flag2 );
	moveCar( R_car3x, 732, 466, flag3 );
	moveCar( R_car4x, 732, 428, flag4 );
	
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(speed , Timer, 0);
}

//Runs the game timer
void game_timer(int m) {

	game_time --;
	if( game_time == 0)
		display_count = 6;
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000 , game_timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	//Used to navigating to different displays by clciking left mouse button
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		if( display_count == 2 and x >= 350 and x<= 650 and y >= 235 and y <= 313)
			display_count = 3;
		else if( display_count == 2 and x>= 350 and x<= 650 and y >= 397 and y <=477)
		{
			display_count = 7;
		}
		else if( display_count == 3 and x>= 350 and x <=650 and y >= 315 and y<= 398 )
		{
			display_count = 4;
		}
		else if( display_count == 4 and x>= 350 and x <=650 and y >= 232 and y<= 315 )
		{
			car = 1;
			display_count = 5;
		}	
		else if( display_count == 4 and x>= 350 and x <=650 and y >= 396 and y<= 480 )
		{
			car = 2;
			display_count = 5;
		}	
		else if( display_count == 4 and x>= 350 and x <=650 and y >= 563 and y<= 643 )
		{
			car = GetRandInRange(1, 2);
			display_count = 5;
		}	
	}
	 else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;
			cout<<endl<<xI<<endl<<yI<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
 
 
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	int num;
	int *p = new int;
	*p = 1;	//dynamic memory allocation
	//int i= 1; 
	
	
	score=0;	//initializes the score
	InitRandomizer(); // seed the random number generator...

	cout<<"\nEnter Your Name: ";
	cin>>name;
	
	drawWalls();
	drawObstacle();
		
	//Random Co-ordinates for Passengers, Obstacles and it destination...
	pass1x = 48 + 38*GetRandInRange( 0, 20 );
	pass1y = 30 + 38*GetRandInRange( 0, 20 );
	pass2x = 48 + 38*GetRandInRange( 0, 20 );
	pass2y = 30 + 38*GetRandInRange( 0, 20 );
	pass3x = 48 + 38*GetRandInRange( 0, 20 );
	pass3y = 30 + 38*GetRandInRange( 0, 20 );
	pass4x = 48 + 38*GetRandInRange( 0, 20 );
	pass4y = 30 + 38*GetRandInRange( 0, 20 );
	dest1x = 48 + 38*GetRandInRange( 0, 20 );
	dest1y = 30 + 38*GetRandInRange( 0, 20 );
	dest2x = 48 + 38*GetRandInRange( 0, 20 );
	dest2y = 30 + 38*GetRandInRange( 0, 20 );
	dest3x = 48 + 38*GetRandInRange( 0, 20 );
	dest3y = 30 + 38*GetRandInRange( 0, 20 );
	dest4x = 48 + 38*GetRandInRange( 0, 20 );
	dest4y = 30 + 38*GetRandInRange( 0, 20 );
	bx1 = 48 + 38*GetRandInRange( 0, 20 );
	by1 = 30 + 38*GetRandInRange( 0, 20 );
	bx2 = 48 + 38*GetRandInRange( 0, 20 );
	by2 = 30 + 38*GetRandInRange( 0, 20 );
	bx3 = 48 + 38*GetRandInRange( 0, 20 );
	by3 = 30 + 38*GetRandInRange( 0, 20 );
	tx1 = 48 + 38*GetRandInRange( 0, 20 );
	ty1 = 30 + 38*GetRandInRange( 0, 20 );
	tx2 = 48 + 38*GetRandInRange( 0, 20 );
	ty2 = 30 + 38*GetRandInRange( 0, 20 );
	tx3 = 48 + 38*GetRandInRange( 0, 20 );
	ty3 = 30 + 38*GetRandInRange( 0, 20 );
	tx4 = 48 + 38*GetRandInRange( 0, 20 );
	ty4 = 30 + 38*GetRandInRange( 0, 20 );
	
	//Validation of all randomly generated Points
	validationForPassenger( pass1x, pass1y, pass2x, pass2y, pass3x, pass3y, pass4x, pass4y,*p);
	validationForPassenger( pass2x, pass2y, pass1x, pass1y, pass3x, pass3y, pass4x, pass4y,*p);
	validationForPassenger( pass3x, pass3y, pass1x, pass1y, pass2x, pass2y, pass4x, pass4y,*p);
	validationForPassenger( pass4x, pass4y, pass1x, pass1y, pass3x, pass3y, pass2x, pass2y,*p);
	
	validationForDestination( dest1x, dest1y,*p);
	validationForDestination( dest2x, dest2y,*p);
	validationForDestination( dest3x, dest3y,*p);
	validationForDestination( dest4x, dest4y,*p);
	
	validationForObstacle( bx1, by1, bx2, by2, bx3, by3, tx1, ty1, tx2, ty2, tx3, ty3, tx4, ty4,*p) ;
	validationForObstacle( bx2, by2, bx1, by1, bx3, by3, tx1, ty1, tx2, ty2, tx3, ty3, tx4, ty4,*p) ;
	validationForObstacle( bx3, by3, bx2, by2, bx1, by1, tx1, ty1, tx2, ty2, tx3, ty3, tx4, ty4,*p) ;
	validationForObstacle( tx1, ty1, bx2, by2, bx3, by3, bx1, by1, tx2, ty2, tx3, ty3, tx4, ty4,*p) ;
	validationForObstacle( tx2, ty2, bx2, by2, bx3, by3, tx1, ty1, bx1, by1, tx3, ty3, tx4, ty4,*p) ;
	validationForObstacle( tx3, ty3, bx2, by2, bx3, by3, tx1, ty1, tx2, ty2, bx1, by1, tx4, ty4,*p) ;
	validationForObstacle( tx4, ty4, bx2, by2, bx3, by3, tx1, ty1, tx2, ty2, tx3, ty3, bx1, by1,*p) ;
	
		
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Luqman Ansari_i210413"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(1000.0, game_timer, 0);
		
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	delete p;
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
