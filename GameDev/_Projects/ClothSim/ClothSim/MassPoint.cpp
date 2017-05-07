#include "MassPoint.h"
#include "math.h"
#include "Randomizer.h"

V_Randomizer rand = V_Randomizer();
MassPoint::MassPoint()
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	origin = pos;
	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;
	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;
	force.x = 0.0f;
	force.y = 0.0f;
	force.z = 0.0f;
	mass = 1.0f; //kg
	damp = 1.0f;
	movable = true;
	useG = true;
}

MassPoint::MassPoint(bool _movable, bool _useG)
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	origin = pos;
	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;
	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;
	force.x = 0.0f;
	force.y = 0.0f;
	force.z = 0.0f;
	mass = fabs(rand.box_muller(0.0,2.0));
	damp = 1.0f;
	movable = _movable;
	useG = _useG;
}
MassPoint::MassPoint(Vec3 _pos)
{
	pos.x = _pos.x;
	pos.y = _pos.y;
	pos.z = _pos.z;
	origin.x = pos.x;
	origin.y = pos.y;
	origin.z = pos.z;
	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;
	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;
	force.x = 0.0f;
	force.y = 0.0f;
	force.z = 0.0f;
	mass = 1.0f;
	damp = 1.0f;
	movable = true;
	useG = true;
}

MassPoint::~MassPoint()
{
}

void MassPoint::Update(float time)
{
	if(movable)
	{
		accel.x = force.x / mass - damp * vel.x;
		accel.y = force.y / mass - damp * vel.y;
		accel.z = force.z / mass - damp * vel.z;

		//Add Gravity
		if(useG)
			accel.y -= 9.8f;
			//pos.y -= 0.098;

		vel.x += accel.x * time;
		vel.y += accel.y * time;
		vel.z += accel.z * time;

		pos.x += vel.x * time + (0.5f * accel.x) * time * time;
		pos.y += vel.y * time + (0.5f * accel.y) * time * time;
		pos.z += vel.z * time + (0.5f * accel.z) * time * time;
	}
}