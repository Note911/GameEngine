#include <math.h>
#pragma once
struct Vec2
{
public:

	float x,y;

	Vec2()
	{
		x = y = 0.0;
	}

	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline Vec2 operator+ (const Vec2 &v) const
	{
		Vec2 tmp = Vec2(x+v.x,y+v.y);
		return tmp;
	}
	inline Vec2 operator+ (float n) const
	{
		return Vec2(x+n,y+x);
	}
	inline void operator+= (const Vec2 &v)
	{
		*this = *this + v;
	}
	inline void operator+= (float n)
	{
		*this = *this + n;
	}
	inline Vec2 operator- (const Vec2 &v) const
	{
		Vec2 tmp = Vec2(x-v.x,y-v.y);
		return tmp;
	}
	inline Vec2 operator- (float n) const
	{
		return Vec2(x-n,y-n);
	}
	inline void operator-= (const Vec2 &v)
	{
		*this = *this - v;
	}
	inline void operator-= (float n)
	{
		*this = *this - n;
	}
	inline Vec2 operator* (float n) const
	{
		Vec2 tmp = Vec2(x*n,y*n);
		return tmp;
	}

	inline void operator*= (float n)
	{
		*this = *this * n;
	}

	inline Vec2 operator/ (float n) const
	{
		if(n != 0)
		{
			Vec2 tmp = Vec2(x/n,y/n);
			return tmp;
		}
		else
			return *this;
	}

	inline void operator/= (float n)
	{
		if(n != 0)
			*this = *this / n;
	}

	inline bool operator== (const Vec2 &v) const
	{
		return (x == v.x && y == v.y);
	}

	inline bool operator!= (const Vec2 &v) const
	{
		return (x != v.x || y != v.y);
	}

	inline float GetMagnitude() const
	{
		return sqrt(this->x * this->x + this->y *this->y);
	}

	inline Vec2 GetNormal() const
	{
		return *this / this->GetMagnitude();
	}

	inline float GetDotProduct(const Vec2 &v) const
	{
		return x*v.x + y*v.y;
	}

	inline float GetCrossProduct(const Vec2 &v) const
	{

	}

	inline float GetProjection(Vec2 v) const
	{
		return this->GetDotProduct(v.GetNormal());
	}
};