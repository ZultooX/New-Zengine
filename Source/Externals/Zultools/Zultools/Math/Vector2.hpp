#pragma once

#include "math.h"

template <typename T>
class Vector2 final
{
public:
	T x = 0;
	T y = 0;

public:
	Vector2<T>();
	Vector2<T>(T aVecPtr[2]);
	Vector2<T>(T x, T y);

	float* GetPtr();

	static float Dot(const Vector2& aVec1, const Vector2& aVec2);
	void Normalize();
	Vector2<T>& GetNormalized();

	float Magnitude();

public:
	void operator+=(Vector2<T>& aVec);
	void operator+=(const Vector2<T>& aVec);

	void operator/=(float scalar);

	void operator*=(float scalar);

	void operator*=(Vector2<T>& aVec);
	void operator*=(const Vector2<T>& aVec);

	void operator-=(Vector2<T>& aVec);
	void operator-=(const Vector2<T>& aVec);

	void operator=(const Vector2<T>& aVec);

	T& operator[](int index);
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;


template<typename T>
inline Vector2<T>::Vector2(){}


template<typename T>
inline Vector2<T>::Vector2(T aVecPtr[2])
{
	x = aVecPtr[0];
	y = aVecPtr[1];
}

template<typename T>
inline Vector2<T>::Vector2(T aX, T aY)
{
	x = aX;
	y = aY;
}

template<typename T>
inline float* Vector2<T>::GetPtr()
{
	return &x;
}

template<typename T>
inline float Vector2<T>::Dot(const Vector2& aVec1, const Vector2& aVec2)
{
	return (aVec1.x * aVec2.x) + (aVec1.y * aVec2.y);
}

template<typename T>
inline void Vector2<T>::Normalize()
{
	float magnitude = Magnitude();

	if (magnitude > 0) {
		x = x / magnitude;
		y = y / magnitude;
	}
	else {
		x = 0;
		y = 0;
	}
}

template<typename T>
inline Vector2<T>& Vector2<T>::GetNormalized()
{
	Vector2 vec = this;
	vec.Normalize();
	return vec;
}

template<typename T>
inline float Vector2<T>::Magnitude()
{
	return sqrtf((x * x) + (y * y));
}




// =============================================== +=
template<typename T>
inline void Vector2<T>::operator+=(Vector2<T>& aVec)
{
	x += aVec.x;
	y += aVec.y;
}

template<typename T>
inline void Vector2<T>::operator+=(const Vector2<T>& aVec)
{
	x += aVec.x;
	y += aVec.y;
}





// =============================================== /=
template<typename T>
inline void Vector2<T>::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
}

template<typename T>
inline void Vector2<T>::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

template<typename T>
inline Vector2<T> operator*(Vector2<T>& aVec, float scalar)
{
	Vector2<T> vec;
	vec.x = aVec.x * scalar;
	vec.y = aVec.y * scalar;
	return vec;
}




// =============================================== *=
template<typename T>
inline void Vector2<T>::operator*=(Vector2<T>& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
}

template<typename T>
inline void Vector2<T>::operator*=(const Vector2<T>& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
}

template<typename T>
inline void Vector2<T>::operator-=(Vector2<T>& aVec)
{
	x -= aVec.x;
	y -= aVec.y;
}

















template<typename T>
inline Vector2<T> operator-(const Vector2<T>& aVec1, const Vector2<T>& aVec2)
{
	Vector2<T> vec;
	vec.x = aVec1.x - aVec2.x;
	vec.y = aVec1.y - aVec2.y;

	return vec;
}

template<typename T>
inline Vector2<T> operator+(const Vector2<T>& aVec1, const Vector2<T>& aVec2)
{
	Vector2<T> vec;
	vec.x = aVec1.x + aVec2.x;
	vec.y = aVec1.y + aVec2.y;

	return vec;
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& aVec1, const Vector2<T>& aVec2)
{
	Vector2<T> vec;
	vec.x = aVec1.x + aVec2.x;
	vec.y = aVec1.y + aVec2.y;

	return vec;
}


template<typename T>
inline void Vector2<T>::operator=(const Vector2<T>& aVec)
{
	x = aVec.x;
	y = aVec.y;
}



template<typename T>
inline T& Vector2<T>::operator[](int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	default:
		break;
	}
}
