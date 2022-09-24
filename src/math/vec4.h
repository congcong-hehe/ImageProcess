// created by hyq
// 2022/4/4

#pragma once

#include "vec.h"
#include <math.h>

namespace Math{

template <typename T>
class Vec<4, T>
{
public:
	union
	{
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		struct { T vec[4]; };
	};

	Vec<4, T>() { x = y = z = w = 0; }
	Vec<4, T>(const Vec<4, T>& v) { x = v.x; y = v.y; z = v.z; w = v.w;}
	Vec<4, T>(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w;}
	T& operator [](size_t index) { return vec[index]; }
	T operator [](size_t index) const { return vec[index]; }
	T norm() const { return sqrt(normSquare()); }
	T normSquare() const { return x * x + y * y + z * z + w * w; }

	Vec<4, T>& operator += (T p) { x += p; y += p; z += p; w += p; return *this; }
	Vec<4, T>& operator -= (T p) { x -= p; y -= p; z -= p; w += p; return *this; }
	Vec<4, T>& operator *= (T p) { x *= p; y *= p; z *= p; w *= p; return *this; }
	Vec<4, T>& operator /= (T p) { x /= p; y /= p; z /= p; w /= p; return *this; }

	Vec<4, T>& operator += (const Vec<4, T>& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	Vec<4, T>& operator -= (const Vec<4, T>& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	Vec<4, T> operator + (T p) const { return Vec<4, T>(x + p, y + p, z + p, w + p); }
	Vec<4, T> operator - (T p) const { return Vec<4, T>(x - p, y - p, z - p, z - p); }
	Vec<4, T> operator * (T p) const { return Vec<4, T>(x * p, y * p, z * p, w * p); }
	Vec<4, T> operator / (T p) const { return Vec<4, T>(x / p, y / p, z / p, w / p); }
	Vec<4, T> operator + (const Vec<4, T>& v) const { return Vec<4, T>(x + v.x, y + v.y, z + v.z, w + v.w); }
	Vec<4, T> operator - (const Vec<4, T>& v) const { return Vec<4, T>(x - v.x, y - v.y, z - v.z, w - v.w); }
	Vec<4, T> operator -() const { return Vec<4, T>(-x, -y, -z, -w); }

	bool operator == (const Vec<4, T>& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator != (const Vec<4, T>& v) const { return x != v.x && y != v.y && z != v.z && w != v.w; }
};

template <typename T>
inline Vec<4, T> operator +(T p, const Vec<4, T>& v) { return Vec<4, T>(p + v.x, p + v.y, p + v.z, p + v.w); }

template <typename T>
inline Vec<4, T> operator *(T p, const Vec<4, T>& v) { return Vec<4, T>(p * v.x, p * v.y, p * v.z, p * v.w); }

template <typename T>
inline T dot(const Vec<4, T>& v1, const Vec<4, T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }

using Vec4i = Vec<4, int>;
using Vec4f = Vec<4, float>;
using Vec4d = Vec<4, double>;

}