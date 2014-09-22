/*
 * Point.h
 * Author: Eric Leadbetter
 * Purpose: 
 */
#ifndef Point_H
#define Point_H

class Point
{
	public:
		Point()
			: x(0), y(0), contents(' '){}
		Point(int x, int y);
		Point(const Point &p );
		int getX( void ) const;
		int getY( void ) const;
		char getContents( void ) const;
		bool isEmpty( void );
		void setContents( char contents );
	private:
		int x;
		int y;
		char contents;
};

#endif
