#include "Triangle.h"

using namespace std;

Triangle::Triangle()
{
	side1 = 0;
	side2 = 0;
	side3 = 0;

	cout << "Enter first side length: ";
	cin >> side1;
	cout << "Enter second side length: ";
	cin >> side2;
	cout << "Enter third side length: ";
	cin >> side3;
}

Triangle::Triangle(int s1, int s2, int s3)
{
    side1 = s1;
    side2 = s2;
    side3 = s3;
}

char* Triangle::getType()
{
    if((side1 == side2) and (side2 == side3))
    {
        return "equilateral";
    }
    else if((side1 == side2) || (side2 == side3) || (side1 == side3))
    {
        return "isoceles";
    }
    else
    {
        return "scalene";
    }
}
