#include <math.h>
#pragma once
struct Vec3
{
public:

	float x,y,z;

	Vec3()
	{
		x = y = z = 0.0;
	}

	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline Vec3 operator+ (const Vec3 &v) const
	{
		return Vec3(x+v.x,y+v.y,z+v.z);
	}
	inline Vec3 operator+ (float n) const
	{
		return Vec3(x+n,y+n,z+n);
	}
	inline void operator+= (float n)
	{
		*this = *this + n;
	}
	inline void operator+= (const Vec3 &v)
	{
		*this = *this + v;
	}
	inline Vec3 operator- (const Vec3 &v) const
	{
		return Vec3(x-v.x,y-v.y,z-v.z);
	}
	inline Vec3 operator- (float n) const
	{
		return Vec3(x-n,y-n,z-n);
	}
	inline void operator-= (const Vec3 &v)
	{
		*this = *this - v;
	}
	inline void operator-= (float n)
	{
		*this = *this - n;
	}

	inline Vec3 operator* (float n) const
	{
		return Vec3(x*n,y*n,z*n);
	}

	inline void operator*= (float n)
	{
		*this = *this * n;
	}

	inline Vec3 operator/ (float n) const
	{
		if(n != 0)
			return Vec3(x/n,y/n,z/n);
		else
			return *this;
	}

	inline void operator/= (float n)
	{
		if(n != 0)
			*this = *this / n;
	}

	inline bool operator== (const Vec3 &v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	inline bool operator!= (const Vec3 &v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	inline float GetMagnitude() const
	{
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	}

	inline Vec3 GetNormal() const
	{
		return *this / this->GetMagnitude();
	}

	inline float GetDotProduct(const Vec3 &v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	inline Vec3 GetCrossProduct(const Vec3 &v) const
	{
		return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	inline float GetProjection(const Vec3 &v) const
	{
		return this->GetDotProduct(v.GetNormal());
	}
};