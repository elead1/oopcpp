// Triangle.cpp
//
#include "Triangle.h"

using namespace std;

/*
 * Triangle( void )
 * Purpose: Create a new Triangle, accepting user input for the side lengths.
 * Input: (from standard input) three integers for side lengths.
 * Postcondition: New Triangle object's side1, side2, and side3 parameters are equal to the
 *                respective user inputs.
 */
Triangle::Triangle()
{
	sideLengths[0] = 0; //Initialize side1 value
	sideLengths[1] = 0; //Initialize side2 value
	sideLengths[2] = 0; //Initialize side3 value

	cout << "Enter first side length: ";
	cin >> sideLengths[0];
	cout << "Enter second side length: ";
	cin >> sideLengths[1];
	cout << "Enter third side length: ";
	cin >> sideLengths[2];
} // end Triangle()

/*
 * Triangle( int s1, int s2, int s3 )
 * Purpose: Create a Triangle object with the parameters as side lengths.
 * Input: s1, s2, and s3 are the lengths that will be assigned to side1, side2, and side3, respectively.
 * Postcondition: New Triangle object's sides are set to the parameters.
 */
Triangle::Triangle(int s1, //Length of side 1
		int s2, //Length of side 2
		int s3) //Length of side 3
{
    sideLengths[0] = s1;
    sideLengths[1] = s2;
    sideLengths[2] = s3;
} //end Triangle(s1, s2, s3)

/*
 * getType( void )
 * Purpose: Evaluates equality of the Triangle's side lengths to determine
 *          the type of the Triangle, and returns that type.
 * Output: A char* string stating the Triangle's type.
 */
char* Triangle::getType()
{
	//If all sides are equal, its an equilateral
    if((sideLengths[0] == sideLengths[1])
    		and (sideLengths[1] == sideLengths[2]))
    {
        return "equilateral";
    }
    //If any two sides are equal, its an isoceles
    else if((sideLengths[0] == sideLengths[1])
    		|| (sideLengths[1] == sideLengths[2])
    		|| (sideLengths[0] == sideLengths[2]))
    {
        return "isoceles";
    }
    //Otherwise, its a scalene
    else
    {
        return "scalene";
    }
} //end getType()
