#include "MathUtilites.h"

Matrix4 Scale::GetScale(Vec3 scale)
{
	return Matrix4(scale);
}

Quat Scale::ScalePoint(Quat point, Matrix4 scale)
{
	return point * scale;
}