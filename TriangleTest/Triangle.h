/*
 * Triangle.h
 * Purpose: To encapsulate the basic characteristics of a geometric triangle.
 */
#include <iostream>

class Triangle
{
    private:
        int sideLengths[3];
    
    public: 
        Triangle();
        Triangle(int s1, int s2, int s3);
        char* getType(); 
}; //end class Triangle

