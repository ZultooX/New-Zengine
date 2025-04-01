#pragma once

#include "math.h"

template <typename T>
class Vector4 final
{
public:
	T x  = 0;
	T y  = 0;
	T z  = 0;
	T w  = 0;

public:
	Vector4<T>() = default;
	Vector4<T>(float aVecPtr[4]);
	Vector4<T>(T x, T y, T z, T w);

	float* GetPtr();

	static float Dot(const Vector4<T>& aVec1, const Vector4<T>& aVec2);
	static float Distance(const Vector4<T>& aVec1, const Vector4<T>& aVec2);
	static float DistanceSqrd(const Vector4<T>& aVec1, const Vector4<T>& aVec2);
	static Vector4<T> Lerp(const Vector4<T>& aVec0, const Vector4<T>& aVec1, const float t);

	void Normalize();
	Vector4<T> GetNormalized();

	static Vector4<T> Cross(const Vector4<T>& aVec1, const Vector4<T>& aVec2);
	T LengthSqr() const;
	T Length() const;

	float Magnitude();

public:
	void operator+=(Vector4<T>& aVec);
	void operator+=(const Vector4<T>& aVec);
	
	void operator/=(float scalar);
	
	void operator*=(Vector4<T>& aVec);
	void operator*=(const Vector4<T>& aVec);
	
	void operator-=(Vector4<T>& aVec);
	void operator-=(const Vector4<T>& aVec);

	void operator=(const Vector4<T>& aVec);

	T& operator[](int index);
};

using Vector4f = Vector4<float>;
using Vector4Int = Vector4<int>;


template<class T>
inline T Vector4<T>::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

template<class T>
inline T Vector4<T>::Length() const
{
	return (T)sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

template<typename T>
Vector4<T> Vector4<T>::Lerp(const Vector4<T>& aVec0, const Vector4<T>& aVec1, const float t)
{
	Vector4<T> result;
	result.x = (1 - t)* aVec0.x + t * aVec1.x;
	result.y = (1 - t)* aVec0.y + t * aVec1.y;
	result.z = (1 - t)* aVec0.z + t * aVec1.z;
	result.w = (1 - t)* aVec0.w + t * aVec1.w;
	return result;
}

template<typename T>
inline Vector4<T>::Vector4(float aVecPtr[4])
{
	x = aVecPtr[0];
	y = aVecPtr[1];
	z = aVecPtr[2];
	w = aVecPtr[3];
}

template<typename T>
inline Vector4<T>::Vector4(T aX, T aY, T aZ, T aW)
{
	x = aX;
	y = aY;
	z = aZ;
	w = aW;
}



template<typename T>
inline float* Vector4<T>::GetPtr()
{
	return &x;
}

template<typename T>
inline Vector4<T> Vector4<T>::Cross(const Vector4& aVec1, const Vector4& aVec2)
{
	Vector4<T> vec;
	vec.x = (aVec1.y * aVec2.z) - (aVec1.z * aVec2.y);
	vec.y = (aVec1.z * aVec2.x) - (aVec1.x * aVec2.z);
	vec.z = (aVec1.x * aVec2.y) - (aVec1.y * aVec2.x);

	return vec;
}

template<typename T>
inline float Vector4<T>::DistanceSqrd(const Vector4& aVec1, const Vector4& aVec2)
{
	float x = aVec2.x - aVec1.x;
	float y = aVec2.y - aVec1.y;
	float z = aVec2.z - aVec1.z;

	return ((x * x) + (y * y) + (z * z));
}


template<typename T>
inline float Vector4<T>::Distance(const Vector4& aVec1, const Vector4& aVec2)
{
	float x = aVec2.x - aVec1.x;
	float y = aVec2.y - aVec1.y;
	float z = aVec2.z - aVec1.z;

	return sqrtf((x * x) + (y * y) + (z * z));
}

template<typename T>
inline float Vector4<T>::Dot(const Vector4& aVec1, const Vector4& aVec2)
{
	return (aVec1.x * aVec2.x) + (aVec1.y * aVec2.y) + (aVec1.z * aVec2.z) + (aVec1.w * aVec2.w);
}

template<typename T>
inline void Vector4<T>::Normalize()
{
	float magnitude = Magnitude();

	if (magnitude > 0) {
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
		w = w / magnitude;
	}
	else {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
}

template<typename T>
inline Vector4<T> Vector4<T>::GetNormalized()
{
	Vector4 vec = *this;
	vec.Normalize();
	return vec;
}

template<typename T>
inline float Vector4<T>::Magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}


// =============================================== +=
template<typename T>
inline void Vector4<T>::operator+=(Vector4<T>& aVec)
{
	x += aVec.x;
	y += aVec.y;
	z += aVec.z;
	w += aVec.w;
}

template<typename T>
inline void Vector4<T>::operator+=(const Vector4<T>& aVec)
{
	x += aVec.x;
	y += aVec.y;
	z += aVec.z;
	w += aVec.w;
}


template<typename T>
inline Vector4<T> operator+(const Vector4<T>& aVec1 , const Vector4<T>& aVec2)
{
	Vector4f vec;

	vec.x = aVec1.x + aVec2.x;
	vec.y = aVec1.y + aVec2.y;
	vec.z = aVec1.z + aVec2.z;
	vec.w = aVec1.w + aVec2.w;

	return vec;
}


template<typename T>
inline Vector4<T> operator*(float aMultiplier, const Vector4<T>& aVec2)
{
	Vector4f vec;

	vec.x = aMultiplier * aVec2.x;
	vec.y = aMultiplier * aVec2.y;
	vec.z = aMultiplier * aVec2.z;
	vec.w = aMultiplier * aVec2.w;

	return vec;
}



template<typename T>
inline Vector4<T> operator/(const Vector4<T>& aVec2, float aMultiplier)
{
	Vector4f vec;

	vec.x = aVec2.x / aMultiplier;
	vec.y = aVec2.y / aMultiplier;
	vec.z = aVec2.z / aMultiplier;
	vec.w = aVec2.w / aMultiplier;

	return vec;
}



template<typename T>
inline void Vector4<T>::operator-=(Vector4<T>& aVec)
{
	x -= aVec.x;
	y -= aVec.y;
	z -= aVec.z;
	w -= aVec.w;
}

template<typename T>
inline void Vector4<T>::operator-=(const Vector4<T>& aVec)
{
	x -= aVec.x;
	y -= aVec.y;
	z -= aVec.z;
	w -= aVec.w;
}






// =============================================== /=
template<typename T>
inline void Vector4<T>::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
}




// =============================================== *=
template<typename T>
inline void Vector4<T>::operator*=(Vector4<T>& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
	z *= aVec.z;
	w *= aVec.w;
}

template<typename T>
inline void Vector4<T>::operator*=(const Vector4<T>& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
	z *= aVec.z;
	w *= aVec.w;
}

















template<typename T>
inline Vector4<T> operator-(const Vector4<T>& aVec1, const Vector4<T>& aVec2)
{
	Vector4<T> vec;
	vec.x = aVec1.x - aVec2.x;
	vec.y = aVec1.y - aVec2.y;
	vec.z = aVec1.z - aVec2.z;
	vec.w = aVec1.w - aVec2.w;

	return vec;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& aVec1, const Vector4<T>& aVec2)
{
	Vector4<T> vec;
	vec.x = aVec1.x * aVec2.x;
	vec.y = aVec1.y * aVec2.y;
	vec.z = aVec1.z * aVec2.z;
	vec.w = aVec1.w * aVec2.w;

	return vec;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& aVec1, const T& aScalar)
{
	Vector4<T> vec;
	vec.x = aVec1.x * aScalar;
	vec.y = aVec1.y * aScalar;
	vec.z = aVec1.z * aScalar;
	vec.w = aVec1.w * aScalar;

	return vec;
}


template<typename T>
inline void Vector4<T>::operator=(const Vector4<T>& aVec)
{
	x = aVec.x;
	y = aVec.y;
	z = aVec.z;
	w = aVec.w;
}



template<typename T>
inline T& Vector4<T>::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: return w;
	}
}
