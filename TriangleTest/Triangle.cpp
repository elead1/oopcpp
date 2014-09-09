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
	int tmp = -1; //Temporary variable to receive user input.
	sideLengths[0] = -1; //Initialize side1 value
	sideLengths[1] = -1; //Initialize side2 value
	sideLengths[2] = -1; //Initialize side3 value

	//Loop through number of sides to get values from user.
	for(int i = 0; i < NUMSIDES; i++)
	{
		//While loop with tmp variable to validate user input. While tmp is -1, input is not valid.
		while(tmp == -1)
		{
			cout << "Enter side " << i + 1 << " length: ";
			cin >> tmp;
			//If cin.fail(), the inputted value was not of the correct type for the assignment.
			if(cin.fail())
			{
				tmp = -1; // Ensure tmp is still set to -1
				cin.clear(); // Clear cin
				cin.ignore(); // Ignore remaining entries on cin
			}
		}
		sideLengths[i] = tmp; // Assign the clean tmp value to the appropriate sideLength index
		tmp = -1; // Reset tmp to -1 for next assignment
	}
	cout << "User-input side lengths: "
		 << sideLengths[0]
		 << "," << sideLengths[1]
		 << "," << sideLengths[2] << endl;
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
    //If any two sides are equal, its an isosceles
    else if((sideLengths[0] == sideLengths[1])
    		|| (sideLengths[1] == sideLengths[2])
    		|| (sideLengths[0] == sideLengths[2]))
    {
        return "isosceles";
    }
    //Otherwise, its a scalene
    else
    {
        return "scalene";
    }
} //end getType()
