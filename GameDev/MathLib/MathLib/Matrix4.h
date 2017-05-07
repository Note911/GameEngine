#include "Matrix2.h"
#include "Vec3.h"
#include "Quat.h"
#include <iostream>
using namespace std;
#pragma once
struct Matrix4
{
public:
	float xx, xy, xz, xw;
	float yx, yy, yz, yw;
	float zx, zy, zz, zw;
	float wx, wy, wz, ww;

	Matrix4()
	{
		xx = yy = zz = ww = 1.f;
		xy = xz = xw = yx = yz = yw = zx = zy = zw = wx = wy = wz = 0.f;
	}

	Matrix4(const Quat v)
	{
		xx = v.x;
		yy = v.y;
		zz = v.z;
		ww = v.w;
		xy = xz = xw = yx = yz = yw = zx = zy = zw = wx = wy = wz = 0.f;
	}

	Matrix4(Quat x, Quat y, Quat z, Quat w)
	{
		xx = x.x; xy = x.y; xz = x.z; xw = x.w;
		yx = y.x; yy = y.y; yz = y.z; yw = y.w;
		zx = z.x; zy = z.y; zz = z.z; zw = z.w;
		wx = w.x; wy = w.y; wz = w.z; ww = w.w;
	}

	Matrix4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz,  float _zw, float _wx, float _wy, float _wz,  float _ww)
	{
		xx = _xx, xy = _xy; xz = _xz; xw = _xw;
		yx = _yx; yy = _yy; yz = _yz; yw = _yw;
		zx = _zx; zy = _zy; zz = _zz; zw = _zw;
		wx = _wx; wy = _wy; wz = _wz; ww = _ww;
	}

	inline Matrix4  operator+ (const Matrix4 &m) const
	{
		return Matrix4(xx + m.xx, xy + m.yx, xz + m.xz, xw + m.xw,
					   yx + m.yx, yy + m.yy, yz + m.yz, yw + m.yw,
					   zx + m.zx, zy + m.zy, zz + m.zz, zw + m.zw,
					   wx + m.wx, wy + m.wy, wz + m.wz, ww + m.ww);
	}

	inline void operator+= (const Matrix4 &m)
	{
		*this = *this + m;
	}

	inline Matrix4 operator- (const Matrix4 &m) const
	{
		return Matrix4(xx - m.xx, xy - m.yx, xz - m.xz, xw - m.xw,
					   yx - m.yx, yy - m.yy, yz - m.yz, yw - m.yw,
					   zx - m.zx, zy - m.zy, zz - m.zz, zw - m.zw,
					   wx - m.wx, wy - m.wy, wz - m.wz, ww - m.ww);
	}

	inline void operator-= (const Matrix4 &m)
	{
		*this = *this - m;
	}

	inline Matrix4 operator* (const Matrix4 &m) const
	{
		Matrix4 t = m.GetTranspose();
		return Matrix4(xx * t.xx + xy * t.xy + xz * t.xz + xw * t.xw, xx * t.yx + xy * t.yy + xz * t.yz + xw * t.yw, xx * t.zx + xy * t.zy + xz * t.zz + xw * t.zw, xx * t.wx + xy * t.wy + xz * t.wz + xw * t.ww,
					   yx * t.xx + yy * t.xy + yz * t.xz + yw * t.xw, yx * t.yx + yy * t.yy + yz * t.yz + yw * t.yw, yx * t.zx + yy * t.zy + yz * t.zz + yw * t.zw, yx * t.wx + yy * t.wy + yz * t.wz + yw * t.ww,
					   zx * t.xx + zy * t.xy + zz * t.xz + zw * t.xw, zx * t.yx + zy * t.yy + zz * t.yz + zw * t.yw, zx * t.zx + zy * t.zy + zz * t.zz + zw * t.zw, zx * t.wx + zy * t.wy + zz * t.wz + zw * t.ww,
					   wx * t.xx + wy * t.xy + wz * t.xz + ww * t.xw, wx * t.yx + wy * t.yy + wz * t.yz + ww * t.yw, wx * t.zx + wy * t.zy + wz * t.zz + ww * t.zw, wx * t.wx + wy * t.wy + wz * t.wz + ww * t.ww);
	}

	inline Matrix4 operator* (float n) const
	{
		return Matrix4(xx * n, xy * n, xz * n, xw * n,
					   yx * n, yy * n, yz * n, yw * n,
					   zx * n, zy * n, zz * n, zw * n,
					   wx * n, wy * n, wz * n, ww * n);
	}

	inline void operator*= (const Matrix4 &m)
	{
		*this = *this * m;
	}

	inline void operator*= (float n)
	{
		*this = *this * n;
	}
	
	inline Matrix4 GetTranspose() const
	{
		return Matrix4(xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww);
	}
	inline void Print() const
	{
		cout << xx  << "\t" << xy << "\t" << xz << "\t" << xw << "\n" 
			 << yx  << "\t" << yy << "\t" << yz << "\t" << yw << "\n"
			 << zx  << "\t" << zy << "\t" << zz << "\t" << zw << "\n"
			 << wx  << "\t" << wy << "\t" << wz << "\t" << ww << "\n";
	}
};