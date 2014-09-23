/*
 * Point.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulate a geometric point (x,y) and some contents at that point.
 */
#ifndef Point_H
#define Point_H

class Point
{
	public:
		Point() // Default constructor, makes point at (0, 0) with empty contents.
			: x(0), y(0), contents(' '){}
		Point(int x, int y);
		Point(const Point &p );
		int getX( void ) const;
		int getY( void ) const;
		char getContents( void ) const;
		bool isEmpty( void ) const;
		void setContents( char contents );
	private:
		int x; // X value of the point.
		int y; // Y value of the point.
		char contents; // The contents at the point.
}; // end class Point

#endif
