/*
 * Tester.cpp
 * Author: Eric Leadbetter
 * Date: September 7th, 2014
 * Class: 605.401 Programming in C++, Hal Pierson and Doug Ferguson
 * Purpose: The program constructs a triangle object with three side-length
 *          parameters and then prints out the type of triangle by comparing
 *          the side lengths. This main class generates one Triangle from the
 *          user's input and outputs the type. It then generates five more
 *          Triangles using programmatically specified side-length values to
 *          evaluate the Triangle class's identification system (one for each
 *          possible triangle type, and one for each possible matching pair
 *          of sides in an isoceles).
 * Algorithm: A simple comparison of the side length values determines what
 *            type of triangle it is:
 *            * equilateral: all sides the same length,
 *            * isoceles: two sides the same length,
 *            * scalene: no sides the same length.
 * Input: The program takes three integer inputs from the user (standard in).
 * Output: The program outputs (to standard out) the type of triangle the
 *         sides specified by the user defines, and then five test cases.
 */
#include "Triangle.h"

using namespace std;

int main()
{
    int side1 = 10; //Initial definition of the test cases' side 1 value
    int side2 = 10; //Initial definition of the test cases' side 2 value
    int side3 = 10; //Initial definition of the test cases' side 3 value
    
    //Create the user-specified triangle and output its type.
    cout << "Building first triangle from user input." << endl;
	Triangle t0; //Create Triangle using empty constructor to get user input
	cout << "Triangle 0 is: " << t0.getType() << endl;
	cout << "=============" << endl;

	//Create the equilateral triangle and output its type.
    cout << "Equilateral test. Parameters: \n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t1 (side1, side2, side3); //Create Triangle with params for test 1
    cout << "Triangle 1 is: " << t1.getType() << endl;
    cout << "=============" << endl;

    side2 = 20; //Reassign side2 to differ from 1 and 3 for first isoceles test

    //Create the isoceles triangle with sides 1 and 3 equal, output type
    cout << "Isoceles test 1 (side1 == side3). Parameters: \n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t2 (side1, side2, side3); //Create Triangle with params for test 2
    cout << "Triangle 2 is: " << t2.getType() << endl;
    cout << "=============" << endl;

    side1 = 20; //Reassign side1 so side1 and side2 are equal for second isoceles test

    //Create isoceles with sides 1 and 2 equal, output type
    cout << "Isoceles test 2 (side1 == side2). Parameters: \n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t3 (side1, side2, side3); //Create Triangle with params for test 3
    cout << "Triangle 3 is: " << t3.getType() << endl;
    cout << "=============" << endl;

    side2 = 10; //Reassign side2 so side2 and side3 are equal for third isoceles test

    //Create isoceles with sides 2 and 3 equal, output type
    cout << "Isoceles test 3 (side 2 == side3). Parameters: \n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t4 (side1, side2, side3); //Create Triangle with params for test 4
    cout << "Triangle 4 is: " << t4.getType() << endl;
    cout << "=============" << endl;

    side3 = 30; //Reassign side3 so all sides are different for scalene test

    //Create scalene, output type.
    cout << "Scalene test. Parameters: \n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t5 (side1, side2, side3); //Create Triangle with params for test 5
    cout << "Triangle 5 is: " << t5.getType() << endl;
    cout << "=============" << endl;

    return 0;
} // end main()
