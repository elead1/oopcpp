/*
 * Point.c
 * Author: Eric Leadbetter
 * Purpose: Encapsulate a geometric point (x,y) and some contents at that point.
 */

#include "Point.h"

/*
 * Point( int, int )
 * Purpose: Create a new point at the given (x, y) coordinates with empty contents.
 * Input: x, y - the x and y coordinates of this point.
 */
Point::Point(int x, int y)
{
	Point::x = x;
	Point::y = y;
	contents = ' ';
}

/*
 * Point( const Point & )
 * Purpose: Create a copy of the given Point.
 * Input: A Point with coordinates and contents to be copied.
 */
Point::Point( const Point &p )
{
	x = p.getX();
	y = p.getY();
	contents = p.getContents();
}

/*
 * getX( void ) const
 * Purpose: Return the Point's x coordinate.
 * Output: The Point's x coordinate.
 */
int Point::getX( void ) const
{
	return x;
}

/*
 * getY( void ) const
 * Purpose: Return the Point's y coordinate.
 * Output; The Point's y coordinate.
 */
int Point::getY( void ) const
{
	return y;
}

/*
 * setContents( char )
 * Purpose: Set the Point's contents to the parameter.
 * Input: contents - a character to set the Point's contents to.
 */
void Point::setContents(char contents)
{
	Point::contents = contents;
}

/*
 * getContents( void ) const
 * Purpose: Return the Point's contents.
 * Output: The Point's contents.
 */
char Point::getContents( void ) const
{
	return contents;
}

/*
 * isEmpty( void ) const
 * Purpose: Determine if the Point is empty or not.
 * Output: true if the contents are still empty (' '), else false.
 */
bool Point::isEmpty( void ) const
{
	if(contents == ' ')
	{
		return true;
	}
	return false;
}
