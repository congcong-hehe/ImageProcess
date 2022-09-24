// 2022/1/3

#pragma once

#include "Vec.h"
#include <math.h>

namespace Math{

template <typename T>
class Vec<2, T>
{
public:
	union
	{
		struct { T x, y; };
		struct { T u, v; };
		struct { T vec[2]; };
	};

	Vec<2, T>() { x = y = 0; }
	Vec<2, T>(const Vec<2, T>& v) { x = v.x; y = v.y; }
	Vec<2, T>(T _x, T _y) { x = _x; y = _y; }

	T& operator [](size_t index) { return vec[index]; }
	T norm() const { return sqrt(normSquare()); }
	T normSquare() const { return x * x + y * y; }

	Vec<2, T>& operator += (T p) { x += p; y += p; return *this; }
	Vec<2, T>& operator -= (T p) { x -= p; y -= p; return *this; }
	Vec<2, T>& operator *= (T p) { x *= p; y *= p; return *this; }
	Vec<2, T>& operator /= (T p) { x /= p; y /= p; return *this; }

	Vec<2, T>& operator += (const Vec<2, T>& v) { x += v.x; y += v.y; return *this; }
	Vec<2, T>& operator -= (const Vec<2, T>& v) { x -= v.x; y -= v.y; return *this; }

	Vec<2, T> operator + (T p) const { return Vec<2, T>(x + p, y + p); }
	Vec<2, T> operator - (T p) const { return Vec<2, T>(x - p, y - p); }
	Vec<2, T> operator * (T p) const { return Vec<2, T>(x * p, y * p); }
	Vec<2, T> operator / (T p) const { return Vec<2, T>(x / p, y / p); }

	Vec<2, T> operator + (const Vec<2, T>& v) const { return Vec<2, T>(x + v.x, y + v.y); }
	Vec<2, T> operator - (const Vec<2, T>& v) const { return Vec<2, T>(x - v.x, y - v.y); }

	Vec<2, T> operator -() const { return Vec<2, T>(-x, -y); }

	bool operator == (const Vec<2, T>& v) const { return x == v.x && y == v.y; }
	bool operator != (const Vec<2, T>& v) const { return x != v.x && y != v.y; }
};

template <typename T>
inline Vec<2, T> operator +(T p, const Vec<2, T>& v) { return Vec<2, T>(p + v.x, p + v.y); }

template <typename T>
inline Vec<2, T> operator *(T p, const Vec<2, T>& v) { return Vec<2, T>(p * v.x, p * v.y); }

template <typename T>
inline T dot(const Vec<2, T>& v1, const Vec<2, T>& v2) { return v1.x * v2.x + v1.y * v2.y; }

using Vec2i = Vec<2, int>;
using Vec2f = Vec<2, float>;
using Vec2d = Vec<2, double>;

}