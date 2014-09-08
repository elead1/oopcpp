#include <iostream>
#include "Triangle.h"
using namespace std;

int main()
{
    int side1 = 10;
    int side2 = 10;
    int side3 = 10;
    
    cout << "Equilateral test.\n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t1 (side1, side2, side3);
    cout << "Triangle 1 is: " << t1.getType() << endl;
    cout << "=============" << endl;

    side2 = 20;

    cout << "Isoceles test 1 (side1 == side3).\n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t2 (side1, side2, side3);
    cout << "Triangle 2 is: " << t2.getType() << endl;
    cout << "=============" << endl;

    side1 = 20;

    cout << "Isoceles test 2 (side1 == side2).\n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t3 (side1, side2, side3);
    cout << "Triangle 3 is: " << t3.getType() << endl;
    cout << "=============" << endl;

    side2 = 10;

    cout << "Isoceles test 3 (side 2 == side3).\n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t4 (side1, side2, side3);
    cout << "Triangle 4 is: " << t4.getType() << endl;
    cout << "=============" << endl;

    side3 = 30;

    cout << "Scalene test.\n\tside1 = " << side1 << "\n\tside2 = " << side2 << "\n\tside3 = " << side3 << endl;
    cout << "=============" << endl;
    Triangle t5 (side1, side2, side3);
    cout << "Triangle 5 is: " << t5.getType() << endl;
    cout << "=============" << endl;

    return 0;
} 
