#include "Matrix2.h"
#include "Vec3.h"
#include "Quat.h"
#include <iostream>
using namespace std;
#pragma once
struct Matrix3
{
public:
	float xx, xy, xz;
	float yx, yy, yz;
	float zx, zy, zz;

	Matrix3()
	{
		xx = yy = zz = 1.f;
		xy = xz = yx = yz = zx = zy = 0.f;
	}

	Matrix3(const Vec3 &v)
	{
		xx = v.x;
		yy = v.y;
		zz = v.z;
		xy = xz = yx = yz = zx = zy = 0.f;
	}

	Matrix3(const Quat &q)
	{
		xx = 1-pow(q.y,2) - pow(q.z,2); 
		xy = 2 * q.x * q.y - 2 * q.w * q.z; 
		xz = 2 * q.x * q.z - 2 * q.w * q.y;
		yx = 2 * q.x * q.y - 2 * q.w * q.z; 
		yy = 1-pow(q.x,2) - pow(q.z,2); 
		yz = 2 * q.y * q.z - 2 * q.w * q.x;
		zx = 2 * q.x * q.z - 2 * q.w * q.y; 
		zy = 2 * q.y * q.z - 2 * q.w * q.x; 
		zz =  1-pow(q.x,2) - pow(q.y,2);
	}

	Matrix3(Vec3 &x, Vec3 &y, Vec3 &z)
	{
		xx = x.x; xy = x.y; xz = x.z;
		yx = y.x; yy = y.y; yz = y.z;
		zx = z.x; zy = z.y; zz = z.z;
	}

	Matrix3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, float _zx, float _zy, float _zz)
	{
		xx = _xx, xy = _xy; xz = _xz;
		yx = _yx; yy = _yy; yz = _yz;
		zx = _zx; zy = _zy; zz = _zz;
	}

	inline Matrix3  operator+ (const Matrix3 &m) const
	{
		return Matrix3(xx + m.xx, xy + m.yx, xz + m.xz, yz + m.yx, yy + m.yy, yz + m.yz, zx + m.zx, zy + m.zy, zz + m.zz);
	}

	inline void operator+= (const Matrix3 &m)
	{
		*this = *this + m;
	}

	inline Matrix3 operator- (const Matrix3 &m) const
	{
		return Matrix3(xx - m.xx, xy - m.yx, xz - m.xz, yz - m.yx, yy - m.yy, yz - m.yz, zx - m.zx, zy - m.zy, zz - m.zz);
	}

	inline void operator-= (const Matrix3 &m)
	{
		*this = *this - m;
	}

	inline Matrix3 operator* (const Matrix3 &m) const
	{
		Matrix3 t = m.GetTranspose();
		return Matrix3(Vec3(xx * t.xx + xy * t.xy + xz * t.xz, xx * t.yx + xy * t.yy + xz * t.yz, xx * t.zx + xy * t.zy + xz * t.zz),
					   Vec3(yx * t.xx + yy * t.xy + yz * t.xz, yx * t.yx + yy * t.yy + yz * t.yz, yx * t.zx + yy * t.zy + yz * t.zz),
					   Vec3(zx * t.xx + zy * t.xy + zz * t.xz, zx * t.yx + zy * t.yy + zz * t.yz, zx * t.zx + zy * t.zy + zz * t.zz));
	}

	inline Matrix3 operator* (float n) const
	{
		return Matrix3(xx * n, xy * n, xz * n, yx * n, yy * n, yz * n, zx * n, zy * n, zz * n);
	}

	inline void operator*= (const Matrix3 &m)
	{
		*this = *this * m;
	}

	inline void operator*= (float n)
	{
		*this = *this * n;
	}
	
	inline Matrix3 GetTranspose() const
	{
		return Matrix3(xx, yx, zx, xy, yy, zy, xz, yz, zz);
	}

	inline Matrix3 GetCofactor() const
	{
		return Matrix3(Vec3(Matrix2(yy, yz, zy, zz).GetDeterminant(), -Matrix2(yx, yz, zx, zz).GetDeterminant(), Matrix2(yx, yy, zx, zy).GetDeterminant()),
					   Vec3 (-Matrix2(xy, xz, zy, zz).GetDeterminant(), Matrix2(xx, xz, zx, zz).GetDeterminant(), -Matrix2(xx, xy, zx, zy).GetDeterminant()),
					   Vec3(Matrix2(xy, xz, yy, yz).GetDeterminant(), -Matrix2(xx, xz, yx, yz).GetDeterminant(), Matrix2(xx, xy, yx, yy).GetDeterminant()));
	}

	inline float GetDeterminant() const
	{
		return xx * Matrix2(yy, yz, zy, zz).GetDeterminant() - xy * Matrix2(yx, yz, zx, zz).GetDeterminant() + xz * Matrix2(yx, yy, zx, zy).GetDeterminant();
	}

	inline Matrix3 GetAdjugate() const
	{
		return GetCofactor().GetTranspose();
	}
	inline Matrix3 GetInverse() const
	{
		if(GetDeterminant() != 0)
			return GetAdjugate() * (1 / GetDeterminant());
		else
			return *this;
	}
	inline const Vec3 ToVec3() const
	{
		return Vec3(xx, yy, zz);
	}
	inline void Print() const
	{
		cout << xx  << "\t" << xy << "\t" << xz << "\n" << yx  << "\t" << yy << "\t" << yz << "\n" << zx  << "\t" << zy << "\t" << zz << "\n";
	}
};