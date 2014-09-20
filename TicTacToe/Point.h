/*
 * Point.h
 * Author: Eric Leadbetter
 * Purpose: 
 */

class Point
{
	public:
		Point(int x, int y);
		int getX( void );
		int getY( void );
		char getContents( void );
		void setContents( char contents );
	private:
		int x;
		int y;
		char contents;
};
