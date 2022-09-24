// created by hyq
// 2021/10/22

#pragma once

#include "vec.h"
#include <math.h>

namespace Math{

template <typename T>
class Vec<3, T>
{
public:
	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T vec[3]; };
	};

	Vec<3, T>() { x = y = z = 0; }
	Vec<3, T>(const Vec<3, T>& v) { x = v.x; y = v.y; z = v.z; }
	Vec<3, T>(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }
	T& operator [](size_t index) { return vec[index]; }
	T norm() const { return sqrt(normSquare()); }
	T normSquare() const { return x * x + y * y + z * z; }
	Vec<3, T> normalization() const {return *this / norm(); }

	Vec<3, T>& operator += (T p) { x += p; y += p; z += p; return *this; }
	Vec<3, T>& operator -= (T p) { x -= p; y -= p; z -= p; return *this; }
	Vec<3, T>& operator *= (T p) { x *= p; y *= p; z *= p; return *this; }
	Vec<3, T>& operator /= (T p) { x /= p; y /= p; z /= p; return *this; }

	Vec<3, T>& operator += (const Vec<3, T>& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vec<3, T>& operator -= (const Vec<3, T>& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vec<3, T> operator + (T p) const { return Vec<3, T>(x + p, y + p, z + p); }
	Vec<3, T> operator - (T p) const { return Vec<3, T>(x - p, y - p, z - p); }
	Vec<3, T> operator * (T p) const { return Vec<3, T>(x * p, y * p, z * p); }
	Vec<3, T> operator / (T p) const { return Vec<3, T>(x / p, y / p, z / p); }
	Vec<3, T> operator + (const Vec<3, T>& v) const { return Vec<3, T>(x + v.x, y + v.y, z + v.z); }
	Vec<3, T> operator - (const Vec<3, T>& v) const { return Vec<3, T>(x - v.x, y - v.y, z - v.z); }
	Vec<3, T> operator -() const { return Vec<3, T>(-x, -y, -z); }

	bool operator == (const Vec<3, T>& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator != (const Vec<3, T>& v) const { return x != v.x && y != v.y && z != v.z; }
};

template <typename T>
inline Vec<3, T> operator +(T p, const Vec<3, T>& v) { return Vec<3, T>(p + v.x, p + v.y, p + v.z); }

template <typename T>
inline Vec<3, T> operator *(T p, const Vec<3, T>& v) { return Vec<3, T>(p * v.x, p * v.y, p * v.z); }

template <typename T>
inline T dot(const Vec<3, T>& v1, const Vec<3, T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

template <typename T>
inline Vec<3, T> cross(const Vec<3, T>& v1, const Vec<3, T>& v2) 
	{ return Vec<3, T> (v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y); }

using Vec3i = Vec<3, int>;
using Vec3f = Vec<3, float>;
using Vec3d = Vec<3, double>;

}