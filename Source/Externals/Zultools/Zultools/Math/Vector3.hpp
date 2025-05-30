#pragma once

#include "math.h"
#include "Vector4.hpp"
#include <Eigen/Dense>

template <typename T>
class Vector3 final 
{
public:
	T x = 0;
	T y = 0;
	T z = 0;

public:
	Vector3<T>();
	Vector3<T>(const Vector4<T>& aVec);

	Vector3<T>(T x, T y, T z);
	Vector3<T>(float ptr[4]);

	float* GetPtr();

	static float Dot(const Vector3<T>& aVec1, const Vector3<T>& aVec2);
	void Normalize();
	Vector3<T> GetNormalized();
	Vector3<T> GetNormalized() const;
	static float Distance(const Vector3<T>& aVec1, const Vector3<T>& aVec2);

	//Returns the squared length of the vector
	T LengthSqr() const;
	//Returns the length of the vector
	T Length() const;


	static Vector3<T> Lerp(const Vector3<T>& aStart, const Vector3<T>& aEnd, const float aPercent);

	float Magnitude();

	static Vector3<T> Cross(const Vector3<T>& aVec1, const Vector3<T>& aVec2);

	Eigen::Vector3f ToEigen();

public:
	void operator+=(const Vector3<T>& aVec);
	void operator/=(const Vector3<T>& aVec);
	void operator*=(const Vector3<T>& aVec);

	T& operator[](int index);

	//template <class OtherVectorClass>
	//Vector3<T>(const OtherVectorClass& aVector) : x(static_cast<T>(aVector.x)), y(static_cast<T>(aVector.y)), z(static_cast<T>(aVector.z))
	//{
	//}

	inline bool operator !=(const Vector3<T>& aVec)
	{
		return (x != aVec.x) || (y != aVec.y) || (z != aVec.z);
 	}

	Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

	template <typename OtherVec>
	explicit operator OtherVec() const
	{
		OtherVec vec;

		vec.x = x;
		vec.y = y;
		vec.z = z;

		return vec;
	}
};

using Vector3f = Vector3<float>;
using Vector3Int = Vector3<int>;


template<typename T>
inline float Vector3<T>::Distance(const Vector3& aVec1, const Vector3& aVec2)
{
	float x = aVec2.x - aVec1.x;
	float y = aVec2.y - aVec1.y;
	float z = aVec2.z - aVec1.z;

	return sqrtf((x * x) + (y * y) + (z * z));
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(
		left.x * right.x,
		left.y * right.y,
		left.z * right.z
	);
}

template<typename T>
Vector3<T> operator*(float scalar, const Vector3<T>& vector)
{
	return Vector3<T>(
		vector.x * scalar,
		vector.y * scalar,
		vector.z * scalar
	);
}

template<typename T>
inline Vector3<T> Vector3<T>::Lerp(const Vector3<T>& aStart, const Vector3<T>& aEnd, const float aPercent)
{
	Vector3<T> output;
	output.x = (T(1) - aPercent) * aStart.x + aPercent * aEnd.x;
	output.y = (T(1) - aPercent) * aStart.y + aPercent * aEnd.y;
	output.z = (T(1) - aPercent) * aStart.z + aPercent * aEnd.z;

	return output;
}




template<typename T>
inline Vector3<T>::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

template<typename T>
inline Vector3<T>::Vector3(const Vector4<T>& aVec)
{
	x = aVec.x;
	y = aVec.y;
	z = aVec.z;
}

template<typename T>
inline Vector3<T>::Vector3(float ptr[4])
{
	x = ptr[0];
	y = ptr[1];
	z = ptr[2];
}

template<typename T>
inline Vector3<T>::Vector3(T aX, T aY, T aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

template<typename T>
inline float* Vector3<T>::GetPtr()
{
	return &x;
}

template<typename T>
inline float Vector3<T>::Dot(const Vector3& aVec1, const Vector3& aVec2)
{
	return (aVec1.x * aVec2.x) + (aVec1.y * aVec2.y) + (aVec1.z * aVec2.z);
}

template<typename T>
inline void Vector3<T>::Normalize()
{
	float magnitude = Magnitude();

	if (magnitude > 0) {
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
	else {
		x = 0;
		y = 0;
		z = 0;
	}
}


template<class T>
inline T Vector3<T>::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z);
}

template<class T>
inline T Vector3<T>::Length() const
{
	return static_cast<T>(sqrt(LengthSqr()));
}

template<typename T>
inline Vector3<T> Vector3<T>::GetNormalized()
{
	float length = Length();

	if (length == 0) return Vector3<T>();

	float newX = x / length;
	float newY = y / length;
	float newZ = z / length;

	return Vector3(newX, newY, newZ);
}


template<typename T>
inline Vector3<T> Vector3<T>::GetNormalized() const
{
	float length = Length();

	if (length == 0) return Vector3<T>();

	float newX = x / length;
	float newY = y / length;
	float newZ = z / length;

	return Vector3(newX, newY, newZ);
}



template<typename T>
inline float Vector3<T>::Magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

template<typename T>
inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVec1, const Vector3<T>& aVec2)
{
	Vector3<T> vec;
	vec.x = (aVec1.y * aVec2.z) - (aVec1.z * aVec2.y);
	vec.y = (aVec1.z * aVec2.x) - (aVec1.x * aVec2.z);
	vec.z = (aVec1.x * aVec2.y) - (aVec1.y * aVec2.x);

	return vec;
}

template<typename T>
inline Eigen::Vector3f Vector3<T>::ToEigen()
{
	return { x, y, z };
}

template<typename T>
inline void Vector3<T>::operator+=(const Vector3& aVec)
{
	x += aVec.x;
	y += aVec.y;
	z += aVec.z;
}

template<typename T>
inline void Vector3<T>::operator/=(const Vector3& aVec)
{
	x /= aVec.x;
	y /= aVec.y;
	z /= aVec.z;
}

template<typename T>
inline Vector3<T>  operator/(const Vector3<T>& aVec, const float& aScalar)
{
	Vector3<T> newVec;

	newVec.x = aVec.x / aScalar;
	newVec.y = aVec.y / aScalar;
	newVec.z = aVec.z / aScalar;

	return newVec;
}

template<typename T>
inline Vector3<T>  operator/(const Vector3<T>& aVec, const Vector3<T>& aVec2)
{
	Vector3<T> newVec;

	newVec.x = aVec.x / aVec2.x;
	newVec.y = aVec.y / aVec2.y;
	newVec.z = aVec.z / aVec2.z;

	return newVec;
}

template<typename T>
inline void Vector3<T>::operator*=(const Vector3& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
	z *= aVec.z;
}

template<typename T>
inline T& Vector3<T>::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		break;
	}
}


template <typename T>
inline Vector3<T> operator+(const Vector3<T>& aVec1, const Vector3<T>& aVec2) {
	Vector3<T> vec;
	vec.x = aVec1.x + aVec2.x;
	vec.y = aVec1.y + aVec2.y;
	vec.z = aVec1.z + aVec2.z;
	return vec;
}

template <typename T>
inline Vector3<T> operator*(const Vector3<T>& aVec1, const T& aScalar) {
	Vector3<T> vec;
	vec.x = aVec1.x * aScalar;
	vec.y = aVec1.y * aScalar;
	vec.z = aVec1.z * aScalar;
	return vec;
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& aVec1, const Vector3<T>& aVec2) {
	Vector3<T> vec;
	vec.x = aVec1.x - aVec2.x;
	vec.y = aVec1.y - aVec2.y;
	vec.z = aVec1.z - aVec2.z;
	return vec;
}
