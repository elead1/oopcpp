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
	contents = ' ';
}

Point::Point( const Point &p )
{
	x = p.getX();
	y = p.getY();
	contents = p.getContents();
}

int Point::getX( void ) const
{
	return x;
}

int Point::getY( void ) const
{
	return y;
}

void Point::setContents(char contents)
{
	Point::contents = contents;
}

char Point::getContents( void ) const
{
	return contents;
}

bool Point::isEmpty( void )
{
	if(contents == ' ')
	{
		return true;
	}
	return false;
}
