#pragma once
#include "Vec3.h"

struct MassPoint
{
	Vec3 pos, vel, accel, origin, force;
	float mass, damp; //kg
	bool movable, useG;

	MassPoint();
	MassPoint(bool _movable, bool _useG);
	MassPoint(Vec3 _pos);
	~MassPoint();
	void Update(float time);

};