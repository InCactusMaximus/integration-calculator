#include <iostream>
#include <string.h>
#include "trapezoid.h"
#include <math.h>

using namespace std;

double func(double x)
{
	double y;
	y = (pow(x, 3.0)) + (2 * pow(x, 2.0)) + (5 * x) + 7;
	return y;
}

void GetInput(int& start, int& end, int& num)
{
	do {
			cout << "Enter the starting point of integration" << endl;
			cin >> start;
			cout << "Enter the ending point of integration" << endl;
			cin >> end;

	} while (end < start);

	cout << "How many trapezoids would you like to use?" << endl;
	cin >> num;

}

double** SetPoints(int start, int end, int num)
{
	double** arr;
	double pointDist;

	arr = new double*[num + 1];

	for (int i = 0; i < num + 1; i++)
	{
		arr[i] = new double[2];
 	}

	arr[0][0] = start;
	arr[num][0] = end;
	pointDist = ((end * 1.0) - (start * 1.0)) / (num * 1.0);

	for (int i = 0; i < num + 1; i++)
	{
		if (i != 0 && i != num)
			arr[i][0] = arr[i - 1][0] + pointDist;

		arr[i][1] = func(arr[i][0]);
	}

	for (int i = 0; i < num + 1; i++)
	{
		cout << "Point " << (i + 1) << " x: " << arr[i][0]
			 << "  y: " << arr[i][1] << endl;
	}

	cout << endl;

	return arr;
}

Trapezoid* SetTraps(double **pArr, int num)
{
	Trapezoid* arr;
	arr = new Trapezoid[num];

	for (int i = 0; i < num; i++)
	{
		arr[i].SetPoint1(pArr[i][0], pArr[i][1]);
		arr[i].SetPoint2(pArr[i + 1][0], pArr[i + 1][1]);
	}

	return arr;
}

double SumArea(Trapezoid *arr, int num)	// Sums up the area of each trapezoid in the array
{
	double totalArea = 0;
    double currentArea;


	for (int i = 0; i < num; i++)
	{
		currentArea = arr[i].GetArea();
		totalArea += currentArea;
		cout << "Area of trap " << (i + 1) << ": " << currentArea << endl;
		cout << "Total area:" << totalArea << endl;
	}

	return totalArea;
}

int main()
{
	int trapNum, startPoint, endPoint;
	double result;
	Trapezoid *trapArr;
	double **pointArr;

	GetInput(startPoint, endPoint, trapNum);

	pointArr = SetPoints(startPoint, endPoint, trapNum);

	trapArr = SetTraps(pointArr, trapNum);

	result = SumArea(trapArr, trapNum);

	cout << endl << "The approximate area under the curve is: " << result;

	delete[] trapArr;
	delete[] pointArr;

	return 0;
}




