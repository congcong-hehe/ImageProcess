// 2022/1/3

#pragma once

namespace Math{

template <size_t N, typename T>
class Vec
{
	T& operator [](size_t index);
	T norm() const;
	T normSquare() const;
	Vec<N, T>& operator += (T p);
	Vec<N, T>& operator -= (T p);
	Vec<N, T>& operator *= (T p);
	Vec<N, T>& operator /= (T p);
	Vec<N, T>& operator += (const Vec<N, T> &v);
	Vec<N, T>& operator -= (const Vec<N, T> &v);
	Vec<N, T> operator + (T p) const;
	Vec<N, T> operator - (T p) const;
	Vec<N, T> operator * (T p) const;
	Vec<N, T> operator / (T p) const;
	Vec<N, T> operator + (const Vec<N, T>& v) const;
	Vec<N, T> operator - (const Vec<N, T>& v) const;
	Vec<N, T> operator -() const;
	bool operator == (const Vec<N, T>& v) const;
	bool operator != (const Vec<N, T>& v) const;
};

template <size_t N, typename T>
inline Vec<N, T> operator +(T p, const Vec<N, T> &v);

template <size_t N, typename T>
inline Vec<N, T> operator *(T p, const Vec<N, T> &v);

template <size_t N, typename T>
inline T dot(const Vec<N, T>& v1, const Vec<N, T>& v2);

}
