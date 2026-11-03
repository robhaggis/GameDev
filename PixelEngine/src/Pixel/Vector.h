#pragma once

#include "Core.h"
#include <cmath>

namespace Pixel
{
	template<typename T>
	struct Vec2
	{
		T x;T y;

		//Comparison
		bool operator==(const Vec2& a) const			{ return x == a.x && y == a.y; }
		bool operator!=(const Vec2& a) const			{ return !(*this == a); }
		
		//Negation
		Vec2 operator-() const							{ return { -x, -y }; }

		//Scalar Operations
		Vec2& operator+=(T a)							{ x += a; y += a; return *this; }
		Vec2& operator-=(T a)							{ x -= a; y -= a; return *this; }
		Vec2& operator*=(T a)							{ x *= a; y *= a; return *this; }
		Vec2& operator/=(T a)							{ x /= a; y /= a; return *this; }
		Vec2 operator+(T a) const						{ Vec2 r = *this; r += a; return r; }
		Vec2 operator-(T a) const						{ Vec2 r = *this; r -= a; return r; }
		Vec2 operator*(T a) const						{ Vec2 r = *this; r *= a; return r; }
		Vec2 operator/(T a) const						{ Vec2 r = *this; r /= a; return r; }
		friend Vec2 operator+(T s, const Vec2& v)		{ return v + s; }
		friend Vec2 operator*(T s, const Vec2& v)		{ return v * s; }
		friend Vec2 operator-(T s, const Vec2& v)		{ return { s - v.x, s - v.y }; }
		friend Vec2 operator/(T s, const Vec2& v)		{ return { s / v.x, s / v.y }; }

		//Vector Operations
		Vec2& operator+=(const Vec2& a)					{ x += a.x; y += a.y; return *this; }
		Vec2& operator-=(const Vec2& a)					{ x -= a.x; y -= a.y; return *this; }
		Vec2& operator*=(const Vec2& a)					{ x *= a.x; y *= a.y; return *this; }
		Vec2& operator/=(const Vec2& a)					{ x /= a.x; y /= a.y; return *this; }
		Vec2 operator+(const Vec2& a) const				{ Vec2 r = *this; r += a; return r; }
		Vec2 operator-(const Vec2& a) const				{ Vec2 r = *this; r -= a; return r; }
		Vec2 operator*(const Vec2& a) const				{ Vec2 r = *this; r *= a; return r; }
		Vec2 operator/(const Vec2& a) const				{ Vec2 r = *this; r /= a; return r; }

		T dot (const Vec2& a) const						{ return (x * a.x) + (y * a.y); }
		friend T dot(const Vec2& a, const Vec2& b)		{ return (a.x * b.x) + (a.y * b.y); }
		T lengthSquared() const							{ return (x * x) + (y * y); }
		T length() const								{ return std::sqrt(lengthSquared()); }
		Vec2& normalize()								{ T l = length(); if (l != T(0)) { x /= l; y /= l; } return *this; }
		Vec2 normalized() const							{ Vec2 r = *this; r.normalize(); return r; }
		
	};


	template<typename T>
	struct Vec3
	{
		T x;T y;T z;

		//Comparison
		bool operator==(const Vec3& a) const			{ return x == a.x && y == a.y && z == a.z; }
		bool operator!=(const Vec3& a) const			{ return !(*this == a); }

		//Negation
		Vec3 operator-() const							{ return { -x, -y, -z }; }

		//Scalar Operations
		Vec3& operator+=(T a)							{ x += a; y += a; z += a; return *this; }
		Vec3& operator-=(T a)							{ x -= a; y -= a; z -= a; return *this; }
		Vec3& operator*=(T a)							{ x *= a; y *= a; z *= a; return *this; }
		Vec3& operator/=(T a)							{ x /= a; y /= a; z /= a; return *this; }
		Vec3 operator+(T a) const						{ Vec3 r = *this; r += a; return r; }
		Vec3 operator-(T a) const						{ Vec3 r = *this; r -= a; return r; }
		Vec3 operator*(T a) const						{ Vec3 r = *this; r *= a; return r; }
		Vec3 operator/(T a) const						{ Vec3 r = *this; r /= a; return r; }
		friend Vec3 operator+(T s, const Vec3& v)		{ return v + s; }
		friend Vec3 operator*(T s, const Vec3& v)		{ return v * s; }
		friend Vec3 operator-(T s, const Vec3& v)		{ return { s - v.x, s - v.y, s - v.z }; }
		friend Vec3 operator/(T s, const Vec3& v)		{ return { s / v.x, s / v.y, s / v.z}; }

		//Vector Operations
		Vec3& operator+=(const Vec3& a)					{ x += a.x; y += a.y; z += a.z; return *this; }
		Vec3& operator-=(const Vec3& a)					{ x -= a.x; y -= a.y; z -= a.z; return *this; }
		Vec3& operator*=(const Vec3& a)					{ x *= a.x; y *= a.y; z *= a.z; return *this; }
		Vec3& operator/=(const Vec3& a)					{ x /= a.x; y /= a.y; z /= a.z; return *this; }
		Vec3 operator+(const Vec3& a) const				{ Vec3 r = *this; r += a; return r; }
		Vec3 operator-(const Vec3& a) const				{ Vec3 r = *this; r -= a; return r; }
		Vec3 operator*(const Vec3& a) const				{ Vec3 r = *this; r *= a; return r; }
		Vec3 operator/(const Vec3& a) const				{ Vec3 r = *this; r /= a; return r; }


		T dot(const Vec3& a) const						{ return (x * a.x) + (y * a.y) + (z * a.z); }
		friend T dot(const Vec3& a, const Vec3& b)		{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
		Vec3 cross(const Vec3& a) const					{ return { y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x }; }
		friend Vec3 cross(const Vec3& a, const Vec3& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
		T lengthSquared() const							{ return (x * x) + (y * y) + (z * z); }
		T length() const								{ return std::sqrt(lengthSquared()); }
		Vec3& normalize()								{ T l = length(); if (l != T(0)) { x /= l; y /= l; z /= l; } return *this; }
		Vec3 normalized() const							{ Vec3 r = *this; r.normalize(); return r; }
	};


	template<typename T>
	struct Vec4
	{
		T x; T y; T z;T w;

		//Comparison
		bool operator==(const Vec4& a) const			{ return x == a.x && y == a.y && z == a.z && w == a.w; }
		bool operator!=(const Vec4& a) const			{ return !(*this == a); }

		//Negation
		Vec4 operator-() const							{ return { -x, -y, -z, -w }; }

		//Scalar Operations								 
		Vec4& operator+=(T a)							{ x += a; y += a; z += a; w += a; return *this; }
		Vec4& operator-=(T a)							{ x -= a; y -= a; z -= a; w -= a; return *this; }
		Vec4& operator*=(T a)							{ x *= a; y *= a; z *= a; w *= a; return *this; }
		Vec4& operator/=(T a)							{ x /= a; y /= a; z /= a; w /= a; return *this; }
		Vec4 operator+(T a) const						{ Vec4 r = *this; r += a; return r; }
		Vec4 operator-(T a) const						{ Vec4 r = *this; r -= a; return r; }
		Vec4 operator*(T a) const						{ Vec4 r = *this; r *= a; return r; }
		Vec4 operator/(T a) const						{ Vec4 r = *this; r /= a; return r; }
		friend Vec4 operator+(T s, const Vec4& v)		{ return v + s; }
		friend Vec4 operator*(T s, const Vec4& v)		{ return v * s; }
		friend Vec4 operator-(T s, const Vec4& v)		{ return { s - v.x, s - v.y, s - v.z, s-v.w}; }
		friend Vec4 operator/(T s, const Vec4& v)		{ return { s / v.x, s / v.y, s / v.z, s / v.w }; }

		//Vector Operations
		Vec4& operator+=(const Vec4& a)					{ x += a.x; y += a.y; z += a.z; w += a.w; return *this;}
		Vec4& operator-=(const Vec4& a)					{ x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }
		Vec4& operator*=(const Vec4& a)					{ x *= a.x; y *= a.y; z *= a.z; w *= a.w; return *this; }
		Vec4& operator/=(const Vec4& a)					{ x /= a.x; y /= a.y; z /= a.z; w /= a.w; return *this; }
		Vec4 operator+(const Vec4& a) const				{ Vec4 r = *this; r += a; return r; }
		Vec4 operator-(const Vec4& a) const				{ Vec4 r = *this; r -= a; return r; }
		Vec4 operator*(const Vec4& a) const				{ Vec4 r = *this; r *= a; return r; }
		Vec4 operator/(const Vec4& a) const				{ Vec4 r = *this; r /= a; return r; }

		T dot(const Vec4& a) const						{ return (x * a.x) + (y * a.y) + (z * a.z) + (w * a.w); }
		friend T dot(const Vec4& a, const Vec4& b)		{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); }
		T lengthSquared() const							{ return (x * x) + (y * y) + (z * z) + (w*w); }
		T length() const								{ return std::sqrt(lengthSquared()); }
		Vec4& normalize()								{ T l = length(); if (l != T(0)) { x /= l; y /= l; z /= l; w /= l; } return *this; }
		Vec4 normalized() const							{ Vec4 r = *this; r.normalize(); return r; }
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int>;

	using Vec4f = Vec4<float>;
	using Vec4d = Vec4<double>;
	using Vec4i = Vec4<int>;
}