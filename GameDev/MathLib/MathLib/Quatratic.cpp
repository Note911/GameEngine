#include "MathUtilites.h"

float Quatratic::GetDiscriminant(float a, float b, float c)
{
	//Calculate the discriminant using b^2 - 4ac

	if(a == 0 && b == 0)
		//Not Valid Equation
		return 0;

	else if(a == 0 && b != 0)
		//Use x = -c/b
		return -c/b;
	else if(a != 0)
		//Use x = b^2 - 4ac
		return pow(b,2) - 4 * a * c;

}

Vec2 Quatratic::GetRoots(float a, float b, float c)
{
	Vec2 roots = Vec2();
	roots.x = (-b + sqrt(pow(b,2) - 4 * a * c)) / 2 * a;
	roots.y = (-b - sqrt(pow(b,2) - 4 * a * c)) / 2 * a;
	return roots;
}

void Quatratic::SolveQuatratic(float a, float b, float c, int &numSol, Vec2 *results)
{
	float d = GetDiscriminant(a,b,c);
	if(d > 0)
	{
		//There are two roots
		*results = GetRoots(a,b,c);
		numSol = 2;
	}
	else if (d = 0)
	{
		//There is one root
		results->x = -b/2 * a;
		numSol = 1;
	}
	else if (d < 0)
	{
		//There are no roots
		*results = Vec2();
		numSol = 0;
	}
}
