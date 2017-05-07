#include "MathUtilites.h"

Matrix4 Translation::GetTranslation(Vec3 point)
{
	Matrix4 translation = Matrix4();
	translation.xw = point.x;
	translation.yw = point.y;
	translation.zw = point.z;
	return translation;
}

Vec3 Translation::TranslateByMultiply(Vec3 point, Matrix4 translation)
{
	Quat tmp = Quat(point);
	tmp *= translation;
	return Vec3(tmp.x, tmp.y, tmp.z);
}
Vec3 Translation::TranslateByAddition(Vec3 point, Vec3 translation)
{
	return point + translation;
}