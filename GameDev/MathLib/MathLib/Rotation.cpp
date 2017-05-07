#include "MathUtilites.h"

Matrix3 Rotation::GetRotX3D(float theta)
{
	return Matrix3(1.f,0.f,0.f,
				   0.f,cos(theta),-sin(theta),
				   0.f,sin(theta),cos(theta));
}
Matrix4 Rotation::GetRotX4D(float theta)
{
	return Matrix4(1.f,0.f,0.f,0.f,
				   0.f,cos(theta),-sin(theta),0.f,
				   0.f,sin(theta),cos(theta),0.f,
				   0.f,0.f,0.f,1.f);
}
Matrix3 Rotation::GetRotY3D(float theta)
{
	return Matrix3(cos(theta),0.f,sin(theta),
				   0.f,1.f,0.f,
				   -sin(theta),0.f,cos(theta));
}
Matrix4 Rotation::GetRotY4D(float theta)
{
	return Matrix4(cos(theta),0.f,sin(theta),0.f,
				   0.f,1.f,0.f,0.f,
				   -sin(theta),0.f,cos(theta),0.f,
				   0.f,0.f,0.f,1.f);
}
Matrix3 Rotation::GetRotZ3D(float theta)
{
	return Matrix3(cos(theta),-sin(theta),0.f,
				   sin(theta),cos(theta),0.f,
				   0.f,0.f,1.f);
}
Matrix4 Rotation::GetRotZ4D(float theta)
{
	return Matrix4(cos(theta),-sin(theta),0.f,0.f,
				   sin(theta),cos(theta),0.f,0.f,
				   0.f,0.f,1.f,0.f,
				   0.f,0.f,0.f,1.f);
}

Matrix3 Rotation::GetRot(float yaw, float pitch, float roll)
{
	return Rotation::GetRotZ3D(roll) * Rotation::GetRotY3D(yaw) * Rotation::GetRotX3D(pitch);
}

Matrix3 Rotation::GetRotAboutAxis(Vec3 axis, float theta)
{
	float c = cos(theta);
	float s = sin(theta);
	Matrix3 rot = Matrix3(c + (1 - c) * pow(axis.x,2), (1 - c) * axis.x * axis.y - s * axis.z, (1 - c) * axis.x * axis.z + s * axis.y,
						  (1 - c) * axis.x * axis.y + s * axis.z, c + (1 - c) * pow(axis.y,2), (1 - c) * axis.y * axis.z - s * axis.x,
						  (1 - c) * axis.x * axis.z - s * axis.y, (1 - c) * axis.y * axis.z + s * axis.x, c + (1 - c) * pow(axis.z,2));
	return rot;
}