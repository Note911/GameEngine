#include "Vec2.h"
#pragma once

struct Matrix2
{
public:
	float xx,xy,yx,yy;

	Matrix2()
	{
		xx = yy = 1.f;
		xy = yx = 0.f;
	}

	Matrix2(Vec2 x, Vec2 y)
	{
		xx = x.x; xy = x.y;
		yx = y.x; yy = y.y;
	}

	Matrix2(float _xx, float _xy, float _yx, float _yy)
	{
		xx = _xx; xy = _xy;
		yx = _yx; yy = _yy;
	}

	inline Matrix2  operator+ (const Matrix2 &m) const
	{
		return Matrix2(xx + m.xx, xy + m.xy, yx + m.yx, yy + m.yy);
	}

	inline void operator+= (const Matrix2 &m)
	{
		*this = *this + m;
	}

	inline Matrix2 operator- (const Matrix2 &m) const
	{
		return Matrix2(xx - m.xx, xy - m.xy,yx - m.yx, yy - m.yy);
	}

	inline void operator-= (const Matrix2 &m)
	{
		*this = *this - m;
	}

	inline Matrix2 operator* (const Matrix2 &m) const
		{
		Matrix2 t = m.GetTranspose();
		return Matrix2(Vec2(xx * t.xx + xy * t.xy, xx * t.yx + xy * t.yy),
					   Vec2(yx * t.xx + yy * t.xy, yx * t.yx + yy * t.yy));
	}

	inline void operator*= (const Matrix2 &m)
	{
		*this = *this * m;
	}
	
	inline Matrix2 GetTranspose() const
	{
		return Matrix2(Vec2(xx,yx),Vec2(xy,yy));
	}

	inline float GetDeterminant() const
	{
		return xx * yy - xy * yx;
	}

	inline Matrix2 GetInverse() const
	{
		return GetTranspose();
	}
};