/*
 * Point.c
 * Author: eric
 * Purpose: 
 */

#include "Point.h"

Point::Point(int x, int y)
{
	Point::x = x;
	Point::y = y;
	contents = '\0';
}

int Point::getX( void )
{
	return x;
}

int Point::getY( void )
{
	return y;
}

void Point::setContents(char contents)
{
	Point::contents = contents;
}

char Point::getContents( void )
{
	return contents;
}
