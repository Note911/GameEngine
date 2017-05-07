#include "Cloth.h"
#include <GL/glut.h>
#include <stdio.h>

Cloth::Cloth()
{
	length = 3;
	width = 3;
	numSprings = (5 + (width - 2) * 4 ) * (length - 1) + (1 * width - 1);
	massPoints = new MassPoint**[width];
	springs = new Spring*[numSprings];
	for(int i = 0; i < width; ++i)
	{
		massPoints[i] = new MassPoint*[length];
	}
	for(int y = 0; y < length; ++y)
		for(int x = 0; x < width; ++x)
		{
			massPoints[x][y] = new MassPoint(Vec3(0,0,0));

		}
		int c = 0;
	for(int y = 0; y < length - 1; ++y)
		for(int x = 0; x < width; ++x)
		{
			if(x == 0)
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y + 1]);
				c++;
			}
			else if(x == width - 1)
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x - 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
			}
			else
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x - 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y]);
				c++;
			}
		}
	for(int i = 0; i < width - 1; ++i)
	{
		springs[c] = new Spring(massPoints[i][length-1], massPoints[i+1][length-1]);
		c++;
	}
	/*for(int i = 0; i < width; ++i)
		massPoints[i][0]->movable = false;*/
	massPoints[0][0]->movable = false;
	massPoints[width-1][0]->movable = false;
}

Cloth::Cloth(int _length, int _width)
{
	length = _length;
	width = _width;
	if(length < 2)
		length = 2;
	if(width < 2)
		width = 2;
	numSprings = (5 + (width - 2) * 4 ) * (length - 1) + (1 * width - 1);
	massPoints = new MassPoint**[width];
	springs = new Spring*[numSprings];
	for(int i = 0; i < width; ++i)
	{
		massPoints[i] = new MassPoint*[length];
	}
	for(int y = 0; y < length; ++y)
		for(int x = 0; x < width; ++x)
		{
			massPoints[x][y] = new MassPoint(Vec3(float(0.5*x) - 0.25 * width,-10.0f,float(-0.5 * y) + 15));

		}
		int c = 0;
	for(int y = 0; y < length - 1; ++y)
		for(int x = 0; x < width; ++x)
		{
			if(x == 0)
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y + 1]);
				c++;
			}
			else if(x == width - 1)
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x - 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
			}
			else
			{
				springs[c] = new Spring(massPoints[x][y], massPoints[x - 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y + 1]);
				c++;
				springs[c] = new Spring(massPoints[x][y], massPoints[x + 1][y]);
				c++;
			}
		}
	for(int i = 0; i < width - 1; ++i)
	{
		springs[c] = new Spring(massPoints[i][length-1], massPoints[i+1][length-1]);
		c++;
	}
	for(int i = 0; i < width; ++i)
	{
		massPoints[i][0]->movable = false;
		//massPoints[i][length-1]->movable = false;
	}
	/*for(int i = 0; i < length - 1; ++i)
	{
		massPoints[width-1][i]->movable = false;
		massPoints[0][i]->movable = false;
	}*/
	/*massPoints[0][0]->movable = false;
	massPoints[width-1][0]->movable = false;*/
}

Cloth::~Cloth()
{
	for(int y = 0; y < length; ++y)
		for(int x = 0; x < width; ++x)
			delete massPoints[x][y];
	for(int y = 0; y < length; ++y)
		delete[] massPoints[y];
	delete[] massPoints;
	for(int i = 0; i < numSprings; ++i)
		delete springs[i];
	delete[] springs;

}

void Cloth::Render()
{
	for(int i = 0; i < numSprings; ++i)
		springs[i]->Render();
}

void Cloth::Update(float time)
{
	UpdateForces();
	/*for(int i = 0; i < numSprings; ++i)
		springs[i]->Update(time);*/
	for(int y = 0; y < length; ++y)
		for(int x = 0; x < width; ++x)
			massPoints[x][y]->Update(time);
}

void Cloth::UpdateForces()
{
	for(int i = 0; i < numSprings; ++i)
	{
		springs[i]->p1->force = Vec3(0,0,0);
		springs[i]->p2->force = Vec3(0,0,0);
	}
	for(int i = 0; i < numSprings; ++i)
	{
		springs[i]->p1->force.x += springs[i]->GetForce().x * -1;
		springs[i]->p1->force.y += springs[i]->GetForce().y * -1;
		springs[i]->p1->force.z += springs[i]->GetForce().z * -1;
		springs[i]->p2->force.x += springs[i]->GetForce().x;
		springs[i]->p2->force.y += springs[i]->GetForce().y;
		springs[i]->p2->force.z += springs[i]->GetForce().z;
	}
	/*for(int y = 0; y < length; ++y)
		for(int x = 0; x < width; ++x)
		{
			printf("(%i, %i)  ",x,y);
			printf("x: %f, y: %f, z: %f \n",massPoints[x][y]->force.x, massPoints[x][y]->force.y, massPoints[x][y]->force.z);
		}*/
}