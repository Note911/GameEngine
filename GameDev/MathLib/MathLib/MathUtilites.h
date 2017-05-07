#include "MatrixMath.h"

static class Translation
{
public:
	static Matrix4 GetTranslation(Vec3 point);
	static Vec3 TranslateByMultiply(Vec3 point, Matrix4 translation);
	static Vec3 TranslateByAddition(Vec3 point, Vec3 translation);
};

static class Rotation
{
public:
	static Matrix3 GetRotX3D(float theta);
	static Matrix4 GetRotX4D(float theta);
	static Matrix3 GetRotY3D(float theta);
	static Matrix4 GetRotY4D(float theta);
	static Matrix3 GetRotZ3D(float theta);
	static Matrix4 GetRotZ4D(float theta);
	static Matrix3 GetRot(float yaw, float pitch, float roll);
	static Matrix3 GetRotAboutAxis(Vec3 axis, float theta);
};

static class Scale
{
public:
	static Matrix4 GetScale(Vec3 scale);
	static Quat ScalePoint(Quat point, Matrix4 scale);
};

static class Interpolation
{
public:
	static Quat Slerp(float t, Quat _q1, Quat _q2);
	static Quat Lerp(float t, Quat _q1, Quat _q2);
};

static class Quatratic
{
	static float GetDiscriminant(float a, float b, float c);
	static Vec2 GetRoots(float a, float b, float c);
	static void SolveQuatratic(float a, float b, float c, int &numSol, Vec2 *results);
};
