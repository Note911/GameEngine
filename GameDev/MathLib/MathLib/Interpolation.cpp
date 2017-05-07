#include "MathUtilites.h"

Quat Interpolation::Slerp(float t, Quat _q1, Quat _q2)
{
	Quat q1 = _q1.GetNormal(); Quat q2 = _q2.GetNormal();
	float theta = q1.GetAngleBetween(q2);
	if(theta > 0.01)
	{
		Quat _qT = q1 * (sin(1 - t) * theta / sin(theta)) + q2 * (sin(t * theta) / sin(theta));
		return _qT;
	}
	else
	{
		return Lerp(t,q1,q2);
	}
}

Quat Interpolation::Lerp(float t, Quat _q1, Quat _q2)
{
	Quat q1 = _q1; Quat q2 = _q2;
	return q1 + (q2 - q1) * t;
}