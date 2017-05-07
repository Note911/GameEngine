#include <math.h>
#include "Vec3.h"
#pragma once
#define PI 3.14159265358979323846
struct Quat
{
public:
	float x, y, z, w;

	Quat()
	{
		x = y = z = w = 0.f;
	}
	Quat(Vec3 a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		w = 1.f;
	}

	Quat(float _w, Vec3 a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		w = _w;
	}

	Quat(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}

	inline Quat operator+ (const Quat &q) const
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}
	inline void operator+= (const Quat &q)
	{
		*this = *this + q;
	}
	inline Quat operator- (const Quat &q) const
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}
	inline void operator-= (const Quat &q)
	{
		*this = *this - q;
	}
	inline Quat operator* (const Quat &q) const
	{
		Vec3 axisQ = Vec3(q.x, q.y, q.z);
		Vec3 axis = Vec3(x, y, z);
		return Quat(w*q.w - axis.GetDotProduct(axisQ), Vec3(axisQ * w +  axis * q.w + axis.GetCrossProduct(axisQ)));
	}
	inline Quat operator* (const Matrix4 &m) const
	{
		return Quat(x * m.xx + y * m.xy + z * m.xz + w * m.xw,
					x * m.yx + y * m.yy + z * m.yz + w * m.yw,
					x * m.zx + y * m.zy + z * m.zz + w * m.zw,
					x * m.wx + y * m.wy + z * m.wz + w * m.ww);
	}
	inline void operator*= (const Matrix4 &m)
	{
		*this = *this * m;
	}

	inline Quat operator* (float n) const
	{
		return Quat(x * n, y * n, z * n, w * n);
	}
	inline void operator*= (const Quat &q)
	{
		*this = *this * q;
	}
	inline void operator*= (float n)
	{
		*this = *this * n;
	}
	inline void operator*= (const Quat& q)
	{
		*this = *this * q;
	}
	inline Quat operator/ (float n) const
	{
		return Quat(x / n, y / n, z / n, w / n);
	}
	inline void operator/= (float n)
	{
		*this = *this / n;
	}
	inline bool operator== (const Quat &q) const
	{
		return (x == q.x && y == q.y && z == q.z && w == q.w);
	}

	inline bool operator!= (const Quat &q) const
	{
		return (x != q.x || y != q.y || z != q.z || w != q.w);
	}

	inline float GetMagnitude() const
	{
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2) + pow(w,2));
	}

	inline Quat GetNormal() const
	{
		return *this / this->GetMagnitude();
	}

	inline float GetDotProduct(const Quat &q) const
	{
		return w * q.w + x * q.x + y * q.y + z * q.z;
	}
	inline Quat GetConjugate()
	{
		return Quat(x * -1, y * -1, z * -1, w);
	}
	inline Quat GetInverse()
	{
		return GetConjugate() / pow(GetMagnitude(),2);
	}
	inline Quat Rotate(Vec3 v)
	{
		return Quat(*this * v * GetInverse());
	}
	inline Quat Slerp(Quat &end, float t)
	{
		//Convert theta to radians
		float theta = GetAngleBetween(end);
		//Calculate Slerp
		return Quat(*this * (sin((1 - t) * theta) / sin(theta)) + end * (sin((t) * theta) / sin(theta)));
	}
	inline float GetAngleBetween(Quat &q)
	{
		return acos(GetDotProduct(q));
	}
};