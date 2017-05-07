#include "MassPoint.h"
#include "Spring.h"
#include <math.h>
#include <GL/glut.h>

Spring::Spring()
{
	*p1 = MassPoint();
	*p2 = MassPoint();
	p1->movable = false;
	K = 180.0f;
	rest = 1.0f;
	restPos.x = p2->pos.x - p1->pos.x;
	restPos.y = p2->pos.y - p1->pos.y;
	restPos.z = p2->pos.z - p1->pos.z;
	restDistance = sqrt(pow(restPos.x,2) + pow(restPos.y,2) + pow(restPos.z,2));
}

Spring::Spring(MassPoint *_p1, MassPoint *_p2)
{
	p1 = _p1;
	p2 = _p2;
	K = 180.0f;
	rest = 1.0f;
	restPos.x = p2->pos.x - p1->pos.x;
	restPos.y = p2->pos.y - p1->pos.y;
	restPos.z = p2->pos.z - p1->pos.z;
	restDistance = sqrt(pow(restPos.x,2) + pow(restPos.y,2) + pow(restPos.z,2));
}

Spring::~Spring()
{
}

void Spring::Render()
{
	glPushMatrix();
	glTranslatef(p1->pos.x,p1->pos.y,p1->pos.z);
	glTranslatef(p2->pos.x,p2->pos.y,p2->pos.z);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(p1->pos.x,p1->pos.y,p1->pos.z);
	glVertex3f(p2->pos.x,p2->pos.y,p2->pos.z);
	glEnd();
}

void Spring::Update(float time)
{
	if(p1->movable)
	{
		p1->accel.x = p1->force.x / p1->mass;
		p1->accel.y = p1->force.y / p1->mass;
		p1->accel.z = p1->force.z / p1->mass;
		//Dampening
		if(fabs(p1->vel.x * rest) < fabs(p1->accel.x))
			p1->accel.x -= rest * p1->vel.x;
		if(fabs(p1->vel.y * rest) < fabs(p1->accel.y))
			p1->accel.y -= rest * p1->vel.y;
		if(fabs(p1->vel.z * rest) < fabs(p1->accel.z))
			p1->accel.z -= rest * p1->vel.z;
		//Add Gravity
		if(p1->useG)
			p1->accel.y -= 9.8;
			//p1->pos.y -= 0.098;

		p1->vel.x += p1->accel.x * time;
		p1->vel.y += p1->accel.y * time;
		p1->vel.z += p1->accel.z * time;

		p1->pos.x += p1->vel.x * time + (0.5f * p1->accel.x) * time * time;
		p1->pos.y += p1->vel.y * time + (0.5f * p1->accel.y) * time * time;
		p1->pos.z += p1->vel.z * time + (0.5f * p1->accel.z) * time * time;
	}

	if(p2->movable)
	{
		p2->accel.x = p2->force.x / p2->mass;
		p2->accel.y = p2->force.y / p2->mass;
		p2->accel.z = p2->force.z / p2->mass;

		//Dampening
		if(fabs(p2->vel.x * rest) < fabs(p2->accel.x))
			p2->accel.x -= rest * p2->vel.x;
		if(fabs(p2->vel.y * rest) < fabs(p2->accel.y))
			p2->accel.y -= rest * p2->vel.y;
		if(fabs(p2->vel.z * rest) < fabs(p2->accel.z))
			p2->accel.z -= rest * p2->vel.z;
		//Add Gravity
		if(p2->useG)
			p2->accel.y -= 9.8;
			/*p2->pos.y -= 0.098;*/
	
		p2->vel.x += p2->accel.x * time;
		p2->vel.y += p2->accel.y * time;
		p2->vel.z += p2->accel.z * time;

		p2->pos.x += p2->vel.x * time + (0.5f * p2->accel.x) * time * time;
		p2->pos.y += p2->vel.y * time + (0.5f * p2->accel.y) * time * time;
		p2->pos.z += p2->vel.z * time + (0.5f * p2->accel.z) * time * time;
	}
}

Vec3 Spring::GetForce()
{
	/*Vec3 force;
	force.x = -K*(p2->pos.x - p1->pos.x);
	force.y = -K*(p2->pos.y - p1->pos.y);
	force.z = -K*(p2->pos.z - p1->pos.z);
	return force;*/

	Vec3 force, Direction;

	Direction.x = p2->pos.x - p1->pos.x;
	Direction.y = p2->pos.y - p1->pos.y;		
	Direction.z = p2->pos.z - p1->pos.z;

	Direction.x /= sqrt(pow(Direction.x,2) + pow(Direction.y,2) + pow(Direction.z,2));
	Direction.y /= sqrt(pow(Direction.x,2) + pow(Direction.y,2) + pow(Direction.z,2));
	Direction.z /= sqrt(pow(Direction.x,2) + pow(Direction.y,2) + pow(Direction.z,2));

	force.x = -K*((p2->pos.x - p1->pos.x) - (Direction.x * restDistance));
	force.y = -K*((p2->pos.y - p1->pos.y) - (Direction.y * restDistance));
	force.z = -K*((p2->pos.z - p1->pos.z) - (Direction.z * restDistance));

	return force;
}
