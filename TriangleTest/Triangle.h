/*
 * Triangle.h
 * Purpose: To encapsulate the basic characteristics of a geometric triangle.
 */
#include <iostream>

class Triangle
{
    private:
		const static int NUMSIDES = 3;
        int sideLengths[NUMSIDES];
    
    public: 
        Triangle();
        Triangle(int s1, int s2, int s3);
        char* getType(); 
}; //end class Triangle

