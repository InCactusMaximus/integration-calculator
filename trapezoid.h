/*
 * trapezoid.h
 *
 *  Created on: Oct 9, 2020
 *      Author: lukeh
 */

#ifndef TRAPEZOID_H_
#define TRAPEZOID_H_

using namespace std;

class Trapezoid
{
private:
		double p1[2];	// These arrays hold the x and y values of each point, [0] being x and [1] being y
		double p2[2];
		double area;

		double AbsoluteValue(double value) // Returns the absolute value of a given double
		{
			if (value < 0)
				return value * -1;
			else
				return value;
		}

		double GetTriangle(double pt1[], double pt2[]) // Returns the area of a triangle given two points. Area is always returned positive
		{
			return (AbsoluteValue(pt2[1] - pt1[1]) * (pt2[0] - pt1[0])) / 2;
		}

		double GetRectangle(double pt1[], double pt2[], bool positive) // Returns the area of the rectangle part of the trapezoid. Area is always returned positive.
		{
			double side;

			if (positive == false) {
				if (pt1[1] < pt2[1])
					side = pt2[1];
				else
					side = pt1[1];
			}

			else {
				if (pt1[1] > pt2[1])
					side = pt2[1];
				else
					side = pt1[1];
			}

			return (AbsoluteValue(side) * (pt2[0] - pt1[0]));
		}

		double GetxIntercept(double pt1[], double m) // This uses point-slope formula to find the x intercept
		{
			double xIntercept = (pt1[1] - (pt1[1] - m * pt1[0])) / m;

			return xIntercept;
		}

public:
		Trapezoid()
		{
			p1[0] = p2[0] = p1[1] = p2[1] = 0.0;
			area = 0.0;
		}

		void SetPoint1(double x, double y) // Sets the start point of the trapezoid
		{
			p1[0] = x;
			p1[1] = y;
		}

		void SetPoint2(double x, double y) // Sets the end point of the trapezoid
		{
			p2[0] = x;
			p2[1] = y;
		}

		double GetArea()
		{
			double slope;
			double xIntercept;

			if (p1[1] < 0 && p2[1] < 0)	// If points are below 0 on the y axis area must be negative
			{
				area = (GetTriangle(p1, p2) + GetRectangle(p1, p2, false));
				return area * -1;
			}

			else if (p1[1] > 0 && p2[1] > 0) // If points are above 0, area is positive
			{
				area = (GetTriangle(p1, p2) + GetRectangle(p1, p2, true));
				return area;
			}

			else	// If 1 point is above and 1 is below, finding area must be done with two triangles instead of a trapezoid
			{
				slope = (p1[0] - p1[1]) / (p2[0] - p1[0]);  // Gets slope of the line between the two points
				xIntercept = GetxIntercept(p1, slope);		// Finds the x-intercept, which will be used as the middle point
				double middle[2]; 							// Sets this middle point to (xIntercept, 0)
				middle[0] = xIntercept;
				middle[1] = 0;

				if (p1[1] > 0 && p2[1] < 0)	// If p1 is above and p2 is below, then the first triangle is positive and the second is negative
				{
					area = GetTriangle(p1, middle) + (GetTriangle(middle, p2) * -1);
					return area;
				}
				area = (GetTriangle(p1, middle) * -1) + (GetTriangle(middle, p2));	// Vice versa
				return area;
			}
		}
};



#endif /* TRAPEZOID_H_ */
