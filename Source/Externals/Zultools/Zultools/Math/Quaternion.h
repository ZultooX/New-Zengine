#pragma once

#pragma warning( push )
#pragma warning( disable : 4201 ) // Nonstandard nameless struct/union.
#include "Vector3.hpp"
#include "MathFuntions.h"
#include "Matrix4x4.hpp"

#ifndef _RETAIL
#include <iostream>
#endif // !_RETAIL

#ifdef max
#undef max
#endif

template <class T>
class Matrix4x4;


template <class T>
class Quaternion
{
public:
	union
	{
		T myValues[4];
		struct { T W; T X; T Y; T Z; };
		struct { T w; T x; T y; T z; };
	};

	Quaternion<T>();
	Quaternion<T>(const T& aW, const T& aX, const T& aY, const T& aZ);
	Quaternion<T>(const T& aYaw, const T& aPitch, const T& aRoll);
	Quaternion<T>(const Vector3<T>& aYawPitchRoll);
	Quaternion<T>(const Vector3<T>& aVector, const T aAngle);
	Quaternion<T>(const Matrix4x4<T>& aMatrix);

	//Set from Unity values - Flip X and Z values, W and Y remains the same
	void SetFromUnityValues(const T aW, const T aX, const T aY, const T aZ);

	void RotateWithEuler(const Vector3<T>& anEuler);

	inline void Normalize();
	inline Quaternion<T> GetNormalized() const;
	inline Quaternion<T> GetConjugate() const;

	Quaternion<T>& operator=(const Quaternion<T>& aQuat) = default;

	T Length() const;
	T Length2() const;
	inline Vector3<T> GetEulerAnglesRadians() const;
	inline Vector3<T> GetEulerAnglesDegrees() const;
	inline Matrix4x4<T> GetRotationMatrix4x4f() const;
	inline T Dot(const Quaternion<T>& aQuat) const;

	inline Vector3<T> GetRight() const;
	inline Vector3<T> GetUp() const;
	inline Vector3<T> GetForward() const;
	// Rotates a vector by the rotation stored in the Quaternion.
	inline static Vector3<T> RotateVectorByQuaternion(const Quaternion<T>& aQuaternion, const Vector3f& aVectorToRotate);
	inline static Quaternion<T> Lerp(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB, const T& aDelta);
	inline static Quaternion<T> Slerp(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB, const T& aDelta);

	inline static Quaternion<T> CreateFromOrthonormalBasisVectors(Vector3<T> x, Vector3<T> y, Vector3<T> z);
};

template<class T>
inline Quaternion<T>::Quaternion()
{
	W = static_cast<T>(1);
	X = static_cast<T>(0);
	Y = static_cast<T>(0);
	Z = static_cast<T>(0);
}

template<class T>
inline Quaternion<T>::Quaternion(const T& aW, const T& aX, const T& aY, const T& aZ)
{
	W = aW;
	X = aX;
	Y = aY;
	Z = aZ;
}

template<class T>
inline Quaternion<T>::Quaternion(const T& aYaw, const T& aPitch, const T& aRoll)
{
	T cy = cos(aYaw * T(0.5));
	T sy = sin(aYaw * T(0.5));
	T cr = cos(aRoll * T(0.5));
	T sr = sin(aRoll * T(0.5));
	T cp = cos(aPitch * T(0.5));
	T sp = sin(aPitch * T(0.5));

	W = cy * cr * cp + sy * sr * sp;
	X = cy * sr * cp - sy * cr * sp;
	Y = cy * cr * sp + sy * sr * cp;
	Z = sy * cr * cp - cy * sr * sp;
}

template<class T>
inline Quaternion<T>::Quaternion(const Vector3<T>& aYawPitchRoll)
{
	T cx = cos(aYawPitchRoll.x * T(0.5));
	T cy = cos(aYawPitchRoll.y * T(0.5));
	T cz = cos(aYawPitchRoll.z * T(0.5));
	T sx = sin(aYawPitchRoll.x * T(0.5));
	T sy = sin(aYawPitchRoll.y * T(0.5));
	T sz = sin(aYawPitchRoll.z * T(0.5));

	W = cx * cy * cz + sx * sy * sz;
	X = sx * cy * cz - cx * sy * sz;
	Y = cx * sy * cz + sx * cy * sz;
	Z = cx * cy * sz - sx * sy * cz;

}

template<class T>
inline Quaternion<T>::Quaternion(const Vector3<T>& aVector, const T aAngle)
{
	T halfAngle = aAngle / T(2);
	W = cos(halfAngle);
	T halfAngleSin = sin(halfAngle);
	X = aVector.x * halfAngleSin;
	Y = aVector.y * halfAngleSin;
	Z = aVector.z * halfAngleSin;

	//W = cos(aAngle / T(2));
	//X = cos(axis.X) * sin(aAngle / T(2));
	//Y = cos(axis.Y) * sin(aAngle / T(2));
	//Z = cos(axis.Z) * sin(aAngle / T(2));
}

template<class T>
inline Quaternion<T>::Quaternion(const Matrix4x4<T>& aMatrix)
{
	*this = CreateFromOrthonormalBasisVectors(normalize(aMatrix.GetRight()), normalize(aMatrix.GetUp()), normalize(aMatrix.GetForward()));
}

#ifndef _RETAIL
// Prints the Quaternion, example use case: std::cout << q << std::endl;
template <class T> inline std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& aQuat)
{
	std::cout << "W: " << aQuat.W << "  X: " << aQuat.X << "  Y: " << aQuat.Y << "  Z: " << aQuat.Z;
	return stream;
}
#endif //!_RETAIL

template <class T> inline Quaternion<T> operator*(const Quaternion<T>& aQuat, const T& aScalar)
{
	return Quaternion<T>(aQuat.W * aScalar, aQuat.X * aScalar, aQuat.Y * aScalar, aQuat.Z * aScalar);
}

template <class T> inline Quaternion<T> operator*(const T& aScalar, const Quaternion<T>& aQuat)
{
	return Quaternion<T>(aQuat.W * aScalar, aQuat.X * aScalar, aQuat.Y * aScalar, aQuat.Z * aScalar);
}

template <class T> inline Quaternion<T> operator*(const Quaternion<T>& aQuat0, const Quaternion<T>& aQuat1)
{
	return Quaternion<T>(
		(aQuat1.W * aQuat0.W) - (aQuat1.X * aQuat0.X) - (aQuat1.Y * aQuat0.Y) - (aQuat1.Z * aQuat0.Z),
		(aQuat1.W * aQuat0.X) + (aQuat1.X * aQuat0.W) + (aQuat1.Y * aQuat0.Z) - (aQuat1.Z * aQuat0.Y),
		(aQuat1.W * aQuat0.Y) + (aQuat1.Y * aQuat0.W) + (aQuat1.Z * aQuat0.X) - (aQuat1.X * aQuat0.Z),
		(aQuat1.W * aQuat0.Z) + (aQuat1.Z * aQuat0.W) + (aQuat1.X * aQuat0.Y) - (aQuat1.Y * aQuat0.X)
	);
}

template <class T> inline void operator*=(Quaternion<T>& aQuat, const T& aScalar)
{
	aQuat.W *= aScalar;
	aQuat.X *= aScalar;
	aQuat.Y *= aScalar;
	aQuat.Z *= aScalar;
}

template <class T> inline void operator*=(Quaternion<T>& aQuat0, const Quaternion<T>& aQuat1)
{
	T w = aQuat0.W;
	T x = aQuat0.X;
	T y = aQuat0.Y;
	T z = aQuat0.Z;

	//aQuat0.W = W * aQuat1.W - X * aQuat1.X - Y * aQuat1.Y - Z * aQuat1.Z;
	//aQuat0.X = W * aQuat1.X + X * aQuat1.W + Y * aQuat1.Z - Z * aQuat1.Y;
	//aQuat0.Y = W * aQuat1.Y - X * aQuat1.Z + Y * aQuat1.W + Z * aQuat1.X;
	//aQuat0.Z = W * aQuat1.Z + X * aQuat1.Y - Y * aQuat1.X + Z * aQuat1.W;


	aQuat0.W = (aQuat1.W * w) - (aQuat1.X * x) - (aQuat1.Y * y) - (aQuat1.Z * z);
	aQuat0.X = (aQuat1.W * x) + (aQuat1.X * w) + (aQuat1.Y * z) - (aQuat1.Z * y);
	aQuat0.Y = (aQuat1.W * y) + (aQuat1.Y * w) + (aQuat1.Z * x) - (aQuat1.X * z);
	aQuat0.Z = (aQuat1.W * z) + (aQuat1.Z * w) + (aQuat1.X * y) - (aQuat1.Y * x);

}

template <class T> inline Quaternion<T> operator/(const Quaternion<T>& aQuat, const T& aScalar)
{
	return Quaternion<T>(aQuat.W / aScalar, aQuat.X / aScalar, aQuat.Y / aScalar, aQuat.Z / aScalar);
}

template <class T> inline Quaternion<T> operator-(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB)
{
	return Quaternion<T>(aQuatA.W - aQuatB.W, aQuatA.X - aQuatB.X, aQuatA.Y - aQuatB.Y, aQuatA.Z - aQuatB.Z);
}

template <class T> inline Quaternion<T> operator-(const Quaternion<T>& aQuat)
{
	return Quaternion<T>(-aQuat.W, -aQuat.X, -aQuat.Y, -aQuat.Z);
}

template <class T> inline Quaternion<T> operator+(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB)
{
	return Quaternion<T>(aQuatA.W + aQuatB.W, aQuatA.X + aQuatB.X, aQuatA.Y + aQuatB.Y, aQuatA.Z + aQuatB.Z);
}

template <class T> inline void operator+=(Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB)
{
	aQuatA.W += aQuatB.W;
	aQuatA.X += aQuatB.X;
	aQuatA.Y += aQuatB.Y;
	aQuatA.Z += aQuatB.Z;
}

template<class T>
inline void Quaternion<T>::SetFromUnityValues(const T aW, const T aX, const T aY, const T aZ)
{
	W = aW;
	X = -aX;
	Y = aY;
	Z = -aZ;
}

template<class T>
inline void Quaternion<T>::RotateWithEuler(const Vector3<T>& anEuler)
{
	*this *= Quaternion(anEuler);
}

template<class T>
inline void Quaternion<T>::Normalize()
{
	T length = T(1) / Length();
	W *= length;
	X *= length;
	Y *= length;
	Z *= length;
}

template<class T>
inline Quaternion<T> Quaternion<T>::GetNormalized() const
{
	T length = T(1) / Length();
	return Quaternion<T>(W * length, X * length, Y * length, Z * length);
}

template<class T>
inline Quaternion<T> Quaternion<T>::GetConjugate() const
{
	return Quaternion<T>(W, -X, -Y, -Z);
}

template<class T>
inline T Quaternion<T>::Length2() const
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

template<class T>
inline T Quaternion<T>::Length() const
{
	return sqrt(Length2());
}

template<class T>
inline Matrix4x4<T> Quaternion<T>::GetRotationMatrix4x4f() const
{
	Matrix4x4<T> result;
	T qxx(X * X);
	T qyy(Y * Y);
	T qzz(Z * Z);

	T qxz(X * Z);
	T qxy(X * Y);
	T qyz(Y * Z);

	T qwx(W * X);
	T qwy(W * Y);
	T qwz(W * Z);


	result(1,1)= T(1) - T(2) * (qyy + qzz);
	result(2,1) = T(2) * (qxy + qwz);
	result(3,1) = T(2) * (qxz - qwy);

	result(1, 2) = T(2) * (qxy - qwz);
	result(2, 2) = T(1) - T(2) * (qxx + qzz);
	result(3, 2) = T(2) * (qyz + qwx);

	result(1, 3) = T(2) * (qxz + qwy);
	result(2, 3) = T(2) * (qyz - qwx);
	result(3, 3) = T(1) - T(2) * (qxx + qyy);
	return result;
}

template<class T>
inline T Quaternion<T>::Dot(const Quaternion<T>& aQuat) const
{
	return X * aQuat.X + Y * aQuat.Y + Z * aQuat.Z + W * aQuat.W;
}

template<class T>
inline Vector3<T> Quaternion<T>::GetRight() const
{
	Vector3<T> right = { 1.f, 0.f, 0.f };
	return Quaternion<T>::RotateVectorByQuaternion(*this, right);;
}

template<class T>
inline Vector3<T> Quaternion<T>::GetUp() const
{
	Vector3<T> up = { 0.f, 1.f, 0.f };
	return Quaternion<T>::RotateVectorByQuaternion(*this, up);
}

template<class T>
inline Vector3<T> Quaternion<T>::GetForward() const
{
	Vector3<T> forward = { 0.f, 0.f, 1.f };
	return Quaternion<T>::RotateVectorByQuaternion(*this, forward);
}

template<class T>
inline Vector3<T> Quaternion<T>::GetEulerAnglesDegrees() const
{
	return GetEulerAnglesRadians() * Math::_RadToDeg;
}


template<class T>
inline Vector3<T> Quaternion<T>::GetEulerAnglesRadians() const
{
	// based on https://gamemath.com/book/orient.html
	// but x and y are switched

	// Output Euler angles (radians)
	float yaw, pitch, roll;

	// Extract sin(pitch)
	float sp = -2.0f * (x * z - w * y);

	// Check for Gimbal lock, giving slight tolerance
	// for numerical imprecision
	if (fabs(sp) > 0.9999f) {

		// Looking straight up or down
		pitch = 1.570796f * sp; // pi/2

		// Compute heading, slam bank to zero
		yaw = atan2(-y * z + w * x, 0.5f - x * x - z * z);
		roll = 0.0f;

	}
	else {

		// Compute angles
		pitch = asin(sp);
		yaw = atan2(y * z + w * x, 0.5f - y * y - x * x);
		roll = atan2(y * x + w * z, 0.5f - y * y - z * z);
	}

	return { yaw, pitch, roll };
}

template<class T>
inline Vector3<T> Quaternion<T>::RotateVectorByQuaternion(const Quaternion<T>& aQuaternion, const Vector3f& aVectorToRotate)
{
	Vector3<T> v(aQuaternion.X, aQuaternion.Y, aQuaternion.Z);
	Vector3<T> result =
		2.0f * v.Dot(aVectorToRotate) * v
		+ (aQuaternion.W * aQuaternion.W - v.Dot(v)) * aVectorToRotate
		+ 2.0f * aQuaternion.W * v.Cross(aVectorToRotate);
	return result;
}

template<class T>
inline Quaternion<T> Quaternion<T>::Lerp(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB, const T& aDelta)
{
	Quaternion<T> Result;
	float deltaInv = 1 - aDelta;
	Result.W = deltaInv * aQuatA.W + aDelta * aQuatB.W;
	Result.X = deltaInv * aQuatA.X + aDelta * aQuatB.X;
	Result.Y = deltaInv * aQuatA.Y + aDelta * aQuatB.Y;
	Result.Z = deltaInv * aQuatA.Z + aDelta * aQuatB.Z;
	Result.Normalize();
	return Result;
}

template<class T>
inline Quaternion<T> Quaternion<T>::Slerp(const Quaternion<T>& aQuatA, const Quaternion<T>& aQuatB, const T& aDelta)
{
	Quaternion<T> qz = aQuatB;

	T cosTheta = aQuatA.Dot(aQuatB);

	// If cosTheta < 0, the interpolation will take the long way around the sphere. 
	// To fix this, one quat must be negated.
	if (cosTheta < T(0))
	{
		qz = -qz;
		cosTheta = -cosTheta;
	}

	const T dotThreshold = static_cast<T>(0.9995);
	// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
	if (cosTheta > T(1) - dotThreshold)
	{
		// Linear interpolation
		return Lerp(aQuatA, qz, aDelta);
	}
	else
	{
		// Essential Mathematics, page 467
		T angle = acos(cosTheta);
		return (sin((T(1) - aDelta) * angle) * aQuatA + sin(aDelta * angle) * qz) / sin(angle);
	}

}

template<class T>
inline Quaternion<T> Quaternion<T>::CreateFromOrthonormalBasisVectors(Vector3<T> x, Vector3<T> y, Vector3<T> z)
{
	// Based on https://gamemath.com/book/orient.html
	Quaternion<T> q;

	// Input matrix:
	float m11 = x.x, m12 = x.y, m13 = x.z;
	float m21 = y.x, m22 = y.y, m23 = y.z;
	float m31 = z.x, m32 = z.y, m33 = z.z;

	// Determine which of w, x, y, or z has the largest absolute value
	float fourWSquaredMinus1 = m11 + m22 + m33;
	float fourXSquaredMinus1 = m11 - m22 - m33;
	float fourYSquaredMinus1 = m22 - m11 - m33;
	float fourZSquaredMinus1 = m33 - m11 - m22;

	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	// Perform square root and division
	float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	float mult = 0.25f / biggestVal;

	// Apply table to compute quaternion values
	switch (biggestIndex)
	{
	case 0:
		q.W = biggestVal;
		q.X = (m23 - m32) * mult;
		q.Y = (m31 - m13) * mult;
		q.Z = (m12 - m21) * mult;
		break;

	case 1:
		q.X = biggestVal;
		q.W = (m23 - m32) * mult;
		q.Y = (m12 + m21) * mult;
		q.Z = (m31 + m13) * mult;
		break;

	case 2:
		q.Y = biggestVal;
		q.W = (m31 - m13) * mult;
		q.X = (m12 + m21) * mult;
		q.Z = (m23 + m32) * mult;
		break;

	case 3:
		q.Z = biggestVal;
		q.W = (m12 - m21) * mult;
		q.X = (m31 + m13) * mult;
		q.Y = (m23 + m32) * mult;
		break;
	}

	return q;
}

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;
typedef Quaternion<int> Quaternioni;
typedef Quaternion<unsigned int> Quaternionui;
typedef Quaternion<short>Quaternions;
typedef Quaternion<unsigned short> Quaternionus;
typedef Quaternion<char> Quaternionc;
typedef Quaternion<unsigned char> Quaternionuc;

typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;
typedef Quaternion<int> Quati;
typedef Quaternion<unsigned int> Quatui;
typedef Quaternion<short>Quats;
typedef Quaternion<unsigned short> Quatus;
typedef Quaternion<char> Quatc;
typedef Quaternion<unsigned char> Quatuc;

#pragma warning( pop )