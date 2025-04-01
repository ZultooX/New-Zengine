#pragma once

#include "Vector4.hpp"
#include <array>

#include <vector>

#include <assert.h>
#include <cmath>
#include "Quaternion.h"
#include "Matrix3x3.hpp"



template <class T>
class Quaternion;

template <class T>
class Matrix4x4
{
public:
	// Creates the identity matrix.
	Matrix4x4<T>();

	// Copy Constructor.
	Matrix4x4<T>(const Matrix4x4<T>& aMatrix);

	// Constructor using array.
	Matrix4x4<T>(const std::array<std::array<T, 4>, 4>& aArray);

	void SetRight(float x, float y, float z);
	void SetUp(float x, float y, float z);
	void SetForward(float x, float y, float z);


	Matrix4x4<T> GetInverse();
	Matrix4x4<T> GetInverse() const;

	void Decompose(Vector3f& aPosition, Vector3f& aRotation, Vector3f& aScale);

	void SetRotation(const Matrix3x3<T>& aRotationMatrix);
	Matrix3x3<T> GetRotation();

	static Matrix4x4<T> CreateScaleMatrix(const Vector4<T>& aScale);
	static Matrix4x4<T> CreateScaleMatrix(const Vector3<T>& aScale);

	static Matrix4x4<T> CreateTranslation(const Vector4<T>& aPosition);
	static Matrix4x4<T> CreateTranslation(const Vector3<T>& aPosition);

	static Matrix4x4<T> CreateRotationAroundX(const T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundY(const T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundZ(const T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAround(T angle, Vector4<float> aCoords);


	Vector4<T> GetColumn(int index);
	void SetColumn(int index, const Vector4<T> aVec);
	Vector4<T> GetRow(int index);


	T& operator()(const int aRow, const int aColumn);

	T operator()(const int aRow, const int aColumn) const;

	T& operator[](const int& aIndex);

	const T& operator[](const int& aIndex) const;

	Matrix4x4<T> GetTranspose() const;

	Matrix4x4<T> GetFastInverse();

	const Vector4<T> GetPosition() const;

	void SetPosition(Vector4<T> pos);

	const Vector4<T> GetRight();

	const Vector4<T> GetUp();

	const Vector4<T> GetForward();

	const std::array<std::array<T, 4>, 4>* GetMatrix() const;

	inline void operator =(Matrix4x4<T> aMatrix)
	{
		myMatrix = std::array<std::array<T, 4>, 4>(*aMatrix.GetMatrix());
	}

	inline void operator =(Vector4<T> aVector)
	{
		for (int x = 0; x < 4; x++)
		{
			myMatrix[4][x] = aVector[x];
		}
	}

	inline void operator +=(Matrix4x4<T> aMatrix)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				myMatrix[y][x] += aMatrix(y + 1, x + 1);
			}
		}
	}

	inline void operator -=(Matrix4x4<T> aMatrix)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				myMatrix[y][x] -= aMatrix(y + 1, x + 1);
			}
		}
	}

	inline void operator *=(Matrix4x4<T> aMatrix)
	{
		Matrix4x4<T> newMatrix;
		T value = 0;

		for (int row = 1; row <= 4; row++)
		{
			for (int column = 1; column <= 4; column++)
			{
				value = 0;

				for (int i = 1; i <= 4; i++)
				{
					value += (*this)(row, i) * aMatrix(i, column);
				}

				newMatrix(row, column) = value;
			}
		}

		myMatrix = *newMatrix.GetMatrix();
	}

	inline void operator *=(T aScalar)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (x == y)
				{
					myMatrix[y][x] *= aScalar;
				}
			}
		}
	}

	inline void operator *=(Vector4<T> aVector4)
	{
		Vector4<T> newVector;
		T value = 0;

		for (int column = 1; column < 5; column++)
		{
			value = 0;

			for (int row = 1; row < 5; row++)
			{
				value += myMatrix(row, column) * aVector4[row];
			}

			newVector[column] = value;
		}

		return newVector;
	}

private:
	std::array<std::array<T, 4>, 4> myMatrix;
};


using Matrix4x4f = Matrix4x4<float>;
using Matrix4x4Int = Matrix4x4<int>;

template <class T>
inline const Matrix4x4<T> operator +(Matrix4x4<T> aMatrix0, Matrix4x4<T> aMatrix1)
{
	Matrix4x4<T> addedMatrixes;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			addedMatrixes(y + 1, x + 1) = aMatrix0(y + 1, x + 1) + aMatrix1(y + 1, x + 1);
		}
	}

	return addedMatrixes;
}

template <class T>
const Matrix4x4<T> operator -(Matrix4x4<T> aMatrix0, Matrix4x4<T> aMatrix1)
{
	Matrix4x4<T> subtractedMatrixes;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			subtractedMatrixes(y + 1, x + 1) = aMatrix0(y + 1, x + 1) - aMatrix1(y + 1, x + 1);
		}
	}

	return subtractedMatrixes;
}

template <typename T>
inline Matrix4x4<T> operator*(const Matrix4x4<T> aMatrix0, const Matrix4x4<T> aMatrix1)
{
	Matrix4x4<T> newMatrix;

	T value = 0;

	for (int row = 1; row <= 4; row++)
	{
		for (int column = 1; column <= 4; column++)
		{
			value = 0;

			for (int i = 1; i <= 4; i++)
			{
				value += aMatrix0(row, i) * aMatrix1(i, column);
			}

			newMatrix(row, column) = value;
		}
	}

	return newMatrix;
}


template <class T>
const inline Vector4<T> operator *(Matrix4x4<T> aMatrix0, Vector4<T> aVector4)
{
	Vector4<T> newVector = {};

	// Iterate over each column of the matrix (to form each component of the resulting vector).
	for (int column = 1; column < 5; column++)
	{
		// Calculate the dot product of the vector with each row of the matrix.
		newVector[column - 1] = aMatrix0(1, column) * aVector4[0] +
			aMatrix0(2, column) * aVector4[1] +
			aMatrix0(3, column) * aVector4[2] +
			aMatrix0(4, column) * aVector4[3];
	}

	return newVector;






	//Vector4<T> newVector = {};


	//for (int column = 1; column < 5; column++)
	//{
	//	for (int row = 1; row < 5; row++)
	//	{
	//		// Add one since matrices index starts at 1.
	//		newVector[row - 1] += aMatrix0(row, column) * aVector4[row - 1];
	//	}
	//}

	//return newVector;
}

template <class T>
const inline bool operator ==(Matrix4x4<T> aMatrix0, Matrix4x4<T> aMatrix1)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (aMatrix0(y + 1, x + 1) != aMatrix1(y + 1, x + 1))
			{
				return false;
			}
		}
	}

	return true;
}


#pragma region ---- CONSTRUCTOR

template<class T>
inline Matrix4x4<T>::Matrix4x4()
{
	myMatrix = std::array<std::array<T, 4>, 4>();

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			myMatrix[y][x] = (x == y) ? static_cast<float>(1) : static_cast<float>(0);
		}
	}
}

template<class T>
inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
{
	myMatrix = std::array<std::array<T, 4>, 4>(*aMatrix.GetMatrix());
}

template<class T>
inline Matrix4x4<T>::Matrix4x4(const std::array<std::array<T, 4>, 4>& aArray)
{
	myMatrix = std::array<std::array<T, 4>, 4>(aArray);
}

#pragma endregion

#pragma region ---- SETTERS

template<class T>
inline void Matrix4x4<T>::SetRight(float x, float y, float z)
{
	myMatrix[0][0] = x;
	myMatrix[0][1] = y;
	myMatrix[0][2] = z;
	myMatrix[0][3] = 0;
}

template<class T>
inline void Matrix4x4<T>::SetUp(float x, float y, float z)
{
	myMatrix[1][0] = x;
	myMatrix[1][1] = y;
	myMatrix[1][2] = z;
	myMatrix[1][3] = 0;
}

template<class T>
inline void Matrix4x4<T>::SetForward(float x, float y, float z)
{
	myMatrix[2][0] = x;
	myMatrix[2][1] = y;
	myMatrix[2][2] = z;
	myMatrix[2][3] = 0;
}

#pragma endregion

#pragma region ---- CALCULATIONS

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::GetInverse()
{
	Matrix4x4<T>& aMatrixToInverse = *this;

	T inv[16];

	inv[0] =
		aMatrixToInverse[5] * aMatrixToInverse[10] * aMatrixToInverse[15] -
		aMatrixToInverse[5] * aMatrixToInverse[11] * aMatrixToInverse[14] -
		aMatrixToInverse[9] * aMatrixToInverse[6] * aMatrixToInverse[15] +
		aMatrixToInverse[9] * aMatrixToInverse[7] * aMatrixToInverse[14] +
		aMatrixToInverse[13] * aMatrixToInverse[6] * aMatrixToInverse[11] -
		aMatrixToInverse[13] * aMatrixToInverse[7] * aMatrixToInverse[10];

	inv[4] = -aMatrixToInverse[4] * aMatrixToInverse[10] * aMatrixToInverse[15] +
		aMatrixToInverse[4] * aMatrixToInverse[11] * aMatrixToInverse[14] +
		aMatrixToInverse[8] * aMatrixToInverse[6] * aMatrixToInverse[15] -
		aMatrixToInverse[8] * aMatrixToInverse[7] * aMatrixToInverse[14] -
		aMatrixToInverse[12] * aMatrixToInverse[6] * aMatrixToInverse[11] +
		aMatrixToInverse[12] * aMatrixToInverse[7] * aMatrixToInverse[10];

	inv[8] = aMatrixToInverse[4] * aMatrixToInverse[9] * aMatrixToInverse[15] -
		aMatrixToInverse[4] * aMatrixToInverse[11] * aMatrixToInverse[13] -
		aMatrixToInverse[8] * aMatrixToInverse[5] * aMatrixToInverse[15] +
		aMatrixToInverse[8] * aMatrixToInverse[7] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[5] * aMatrixToInverse[11] -
		aMatrixToInverse[12] * aMatrixToInverse[7] * aMatrixToInverse[9];

	inv[12] = -aMatrixToInverse[4] * aMatrixToInverse[9] * aMatrixToInverse[14] +
		aMatrixToInverse[4] * aMatrixToInverse[10] * aMatrixToInverse[13] +
		aMatrixToInverse[8] * aMatrixToInverse[5] * aMatrixToInverse[14] -
		aMatrixToInverse[8] * aMatrixToInverse[6] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[5] * aMatrixToInverse[10] +
		aMatrixToInverse[12] * aMatrixToInverse[6] * aMatrixToInverse[9];

	inv[1] = -aMatrixToInverse[1] * aMatrixToInverse[10] * aMatrixToInverse[15] +
		aMatrixToInverse[1] * aMatrixToInverse[11] * aMatrixToInverse[14] +
		aMatrixToInverse[9] * aMatrixToInverse[2] * aMatrixToInverse[15] -
		aMatrixToInverse[9] * aMatrixToInverse[3] * aMatrixToInverse[14] -
		aMatrixToInverse[13] * aMatrixToInverse[2] * aMatrixToInverse[11] +
		aMatrixToInverse[13] * aMatrixToInverse[3] * aMatrixToInverse[10];

	inv[5] = aMatrixToInverse[0] * aMatrixToInverse[10] * aMatrixToInverse[15] -
		aMatrixToInverse[0] * aMatrixToInverse[11] * aMatrixToInverse[14] -
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[15] +
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[14] +
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[11] -
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[10];

	inv[9] = -aMatrixToInverse[0] * aMatrixToInverse[9] * aMatrixToInverse[15] +
		aMatrixToInverse[0] * aMatrixToInverse[11] * aMatrixToInverse[13] +
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[15] -
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[11] +
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[9];

	inv[13] = aMatrixToInverse[0] * aMatrixToInverse[9] * aMatrixToInverse[14] -
		aMatrixToInverse[0] * aMatrixToInverse[10] * aMatrixToInverse[13] -
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[14] +
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[10] -
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[9];

	inv[2] = aMatrixToInverse[1] * aMatrixToInverse[6] * aMatrixToInverse[15] -
		aMatrixToInverse[1] * aMatrixToInverse[7] * aMatrixToInverse[14] -
		aMatrixToInverse[5] * aMatrixToInverse[2] * aMatrixToInverse[15] +
		aMatrixToInverse[5] * aMatrixToInverse[3] * aMatrixToInverse[14] +
		aMatrixToInverse[13] * aMatrixToInverse[2] * aMatrixToInverse[7] -
		aMatrixToInverse[13] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[6] = -aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[15] +
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[14] +
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[15] -
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[14] -
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[7] +
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[10] = aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[15] -
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[13] -
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[15] +
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[7] -
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[5];

	inv[14] = -aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[14] +
		aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[13] +
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[14] -
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[6] +
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[5];

	inv[3] = -aMatrixToInverse[1] * aMatrixToInverse[6] * aMatrixToInverse[11] +
		aMatrixToInverse[1] * aMatrixToInverse[7] * aMatrixToInverse[10] +
		aMatrixToInverse[5] * aMatrixToInverse[2] * aMatrixToInverse[11] -
		aMatrixToInverse[5] * aMatrixToInverse[3] * aMatrixToInverse[10] -
		aMatrixToInverse[9] * aMatrixToInverse[2] * aMatrixToInverse[7] +
		aMatrixToInverse[9] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[7] = aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[11] -
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[10] -
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[11] +
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[10] +
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[7] -
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[11] = -aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[11] +
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[9] +
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[11] -
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[9] -
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[7] +
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[5];

	inv[15] = aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[10] -
		aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[9] -
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[10] +
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[9] +
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[6] -
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[5];

	T det = aMatrixToInverse[0] * inv[0] + aMatrixToInverse[1] * inv[4] + aMatrixToInverse[2] * inv[8] + aMatrixToInverse[3] * inv[12];

	//if (det == 0)
	//	return false;

	det = T(1.0) / det;

	Matrix4x4<T> returnMatrix;
	for (int i = 0; i < 16; i++)
	{
		returnMatrix[i] = inv[i] * det;
	}

	return returnMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::GetInverse() const
{
	Matrix4x4<T> aMatrixToInverse = *this;

	T inv[16];

	inv[0] =
		aMatrixToInverse[5] * aMatrixToInverse[10] * aMatrixToInverse[15] -
		aMatrixToInverse[5] * aMatrixToInverse[11] * aMatrixToInverse[14] -
		aMatrixToInverse[9] * aMatrixToInverse[6] * aMatrixToInverse[15] +
		aMatrixToInverse[9] * aMatrixToInverse[7] * aMatrixToInverse[14] +
		aMatrixToInverse[13] * aMatrixToInverse[6] * aMatrixToInverse[11] -
		aMatrixToInverse[13] * aMatrixToInverse[7] * aMatrixToInverse[10];

	inv[4] = -aMatrixToInverse[4] * aMatrixToInverse[10] * aMatrixToInverse[15] +
		aMatrixToInverse[4] * aMatrixToInverse[11] * aMatrixToInverse[14] +
		aMatrixToInverse[8] * aMatrixToInverse[6] * aMatrixToInverse[15] -
		aMatrixToInverse[8] * aMatrixToInverse[7] * aMatrixToInverse[14] -
		aMatrixToInverse[12] * aMatrixToInverse[6] * aMatrixToInverse[11] +
		aMatrixToInverse[12] * aMatrixToInverse[7] * aMatrixToInverse[10];

	inv[8] = aMatrixToInverse[4] * aMatrixToInverse[9] * aMatrixToInverse[15] -
		aMatrixToInverse[4] * aMatrixToInverse[11] * aMatrixToInverse[13] -
		aMatrixToInverse[8] * aMatrixToInverse[5] * aMatrixToInverse[15] +
		aMatrixToInverse[8] * aMatrixToInverse[7] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[5] * aMatrixToInverse[11] -
		aMatrixToInverse[12] * aMatrixToInverse[7] * aMatrixToInverse[9];

	inv[12] = -aMatrixToInverse[4] * aMatrixToInverse[9] * aMatrixToInverse[14] +
		aMatrixToInverse[4] * aMatrixToInverse[10] * aMatrixToInverse[13] +
		aMatrixToInverse[8] * aMatrixToInverse[5] * aMatrixToInverse[14] -
		aMatrixToInverse[8] * aMatrixToInverse[6] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[5] * aMatrixToInverse[10] +
		aMatrixToInverse[12] * aMatrixToInverse[6] * aMatrixToInverse[9];

	inv[1] = -aMatrixToInverse[1] * aMatrixToInverse[10] * aMatrixToInverse[15] +
		aMatrixToInverse[1] * aMatrixToInverse[11] * aMatrixToInverse[14] +
		aMatrixToInverse[9] * aMatrixToInverse[2] * aMatrixToInverse[15] -
		aMatrixToInverse[9] * aMatrixToInverse[3] * aMatrixToInverse[14] -
		aMatrixToInverse[13] * aMatrixToInverse[2] * aMatrixToInverse[11] +
		aMatrixToInverse[13] * aMatrixToInverse[3] * aMatrixToInverse[10];

	inv[5] = aMatrixToInverse[0] * aMatrixToInverse[10] * aMatrixToInverse[15] -
		aMatrixToInverse[0] * aMatrixToInverse[11] * aMatrixToInverse[14] -
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[15] +
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[14] +
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[11] -
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[10];

	inv[9] = -aMatrixToInverse[0] * aMatrixToInverse[9] * aMatrixToInverse[15] +
		aMatrixToInverse[0] * aMatrixToInverse[11] * aMatrixToInverse[13] +
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[15] -
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[11] +
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[9];

	inv[13] = aMatrixToInverse[0] * aMatrixToInverse[9] * aMatrixToInverse[14] -
		aMatrixToInverse[0] * aMatrixToInverse[10] * aMatrixToInverse[13] -
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[14] +
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[10] -
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[9];

	inv[2] = aMatrixToInverse[1] * aMatrixToInverse[6] * aMatrixToInverse[15] -
		aMatrixToInverse[1] * aMatrixToInverse[7] * aMatrixToInverse[14] -
		aMatrixToInverse[5] * aMatrixToInverse[2] * aMatrixToInverse[15] +
		aMatrixToInverse[5] * aMatrixToInverse[3] * aMatrixToInverse[14] +
		aMatrixToInverse[13] * aMatrixToInverse[2] * aMatrixToInverse[7] -
		aMatrixToInverse[13] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[6] = -aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[15] +
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[14] +
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[15] -
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[14] -
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[7] +
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[10] = aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[15] -
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[13] -
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[15] +
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[13] +
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[7] -
		aMatrixToInverse[12] * aMatrixToInverse[3] * aMatrixToInverse[5];

	inv[14] = -aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[14] +
		aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[13] +
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[14] -
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[13] -
		aMatrixToInverse[12] * aMatrixToInverse[1] * aMatrixToInverse[6] +
		aMatrixToInverse[12] * aMatrixToInverse[2] * aMatrixToInverse[5];

	inv[3] = -aMatrixToInverse[1] * aMatrixToInverse[6] * aMatrixToInverse[11] +
		aMatrixToInverse[1] * aMatrixToInverse[7] * aMatrixToInverse[10] +
		aMatrixToInverse[5] * aMatrixToInverse[2] * aMatrixToInverse[11] -
		aMatrixToInverse[5] * aMatrixToInverse[3] * aMatrixToInverse[10] -
		aMatrixToInverse[9] * aMatrixToInverse[2] * aMatrixToInverse[7] +
		aMatrixToInverse[9] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[7] = aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[11] -
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[10] -
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[11] +
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[10] +
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[7] -
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[6];

	inv[11] = -aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[11] +
		aMatrixToInverse[0] * aMatrixToInverse[7] * aMatrixToInverse[9] +
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[11] -
		aMatrixToInverse[4] * aMatrixToInverse[3] * aMatrixToInverse[9] -
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[7] +
		aMatrixToInverse[8] * aMatrixToInverse[3] * aMatrixToInverse[5];

	inv[15] = aMatrixToInverse[0] * aMatrixToInverse[5] * aMatrixToInverse[10] -
		aMatrixToInverse[0] * aMatrixToInverse[6] * aMatrixToInverse[9] -
		aMatrixToInverse[4] * aMatrixToInverse[1] * aMatrixToInverse[10] +
		aMatrixToInverse[4] * aMatrixToInverse[2] * aMatrixToInverse[9] +
		aMatrixToInverse[8] * aMatrixToInverse[1] * aMatrixToInverse[6] -
		aMatrixToInverse[8] * aMatrixToInverse[2] * aMatrixToInverse[5];

	T det = aMatrixToInverse[0] * inv[0] + aMatrixToInverse[1] * inv[4] + aMatrixToInverse[2] * inv[8] + aMatrixToInverse[3] * inv[12];

	//if (det == 0)
	//	return false;

	det = T(1.0) / det;

	Matrix4x4<T> returnMatrix;
	for (int i = 0; i < 16; i++)
	{
		returnMatrix[i] = inv[i] * det;
	}

	return returnMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::GetTranspose() const
{
	Matrix4x4<T> newMatrix;

	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			newMatrix(i, j) = myMatrix[j - 1][i - 1];
		}
	}

	return newMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(const T aAngleInRadians)
{
	Matrix4x4<T> newMatrix;

	newMatrix(1, 1) = 1;
	newMatrix(2, 2) = std::cos(aAngleInRadians);
	newMatrix(2, 3) = std::sin(aAngleInRadians);
	newMatrix(3, 2) = -std::sin(aAngleInRadians);
	newMatrix(3, 3) = std::cos(aAngleInRadians);
	newMatrix(4, 4) = 1;

	return newMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(const T aAngleInRadians)
{
	Matrix4x4<T> newMatrix;

	newMatrix(1, 1) = std::cos(aAngleInRadians);
	newMatrix(1, 3) = -std::sin(aAngleInRadians);
	newMatrix(2, 2) = 1;
	newMatrix(3, 1) = std::sin(aAngleInRadians);
	newMatrix(3, 3) = std::cos(aAngleInRadians);
	newMatrix(4, 4) = 1;

	return newMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(const T aAngleInRadians)
{
	Matrix4x4<T> newMatrix;

	newMatrix(1, 1) = std::cos(aAngleInRadians);
	newMatrix(1, 2) = std::sin(aAngleInRadians);
	newMatrix(2, 1) = -std::sin(aAngleInRadians);
	newMatrix(2, 2) = std::cos(aAngleInRadians);
	newMatrix(3, 3) = 1;
	newMatrix(4, 4) = 1;

	return newMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAround(T angle, Vector4<float> aCoords)
{
	aCoords.Normalize();

	float x = aCoords.x;
	float y = aCoords.y;
	float z = aCoords.z;

	T length = std::sqrt(x * x + y * y + z * z);

	x /= length;
	y /= length;
	z /= length;

	// Compute trigonometric values
	T c = std::cos(angle);
	T s = std::sin(angle);
	T t = 1 - c;

	Matrix4x4<T> rotationMatrix;

	rotationMatrix(1, 1) = t * x * x + c;
	rotationMatrix(1, 2) = t * x * y - s * z;
	rotationMatrix(1, 3) = t * x * z + s * y;

	rotationMatrix(2, 1) = t * x * y + s * z;
	rotationMatrix(2, 2) = t * y * y + c;
	rotationMatrix(2, 3) = t * y * z - s * x;

	rotationMatrix(3, 1) = t * x * z - s * y;
	rotationMatrix(3, 2) = t * y * z + s * x;
	rotationMatrix(3, 3) = t * z * z + c;

	return rotationMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse()
{
	Matrix4x4 inversed = GetTranspose();
	Matrix4x4 translation;

	translation(4, 1) = -inversed(1, 4);
	translation(4, 2) = -inversed(2, 4);
	translation(4, 3) = -inversed(3, 4);

	inversed(1, 4) = 0;
	inversed(2, 4) = 0;
	inversed(3, 4) = 0;

	return inversed * translation;
}

#pragma endregion

template<class T>
inline const Vector4<T> Matrix4x4<T>::GetPosition() const
{
	Vector4<T> pos;

	pos.x = (*this)(4, 1);
	pos.y = (*this)(4, 2);
	pos.z = (*this)(4, 3);
	pos.w = (*this)(4, 4);

	return pos;
}

template<class T>
inline void Matrix4x4<T>::SetPosition(Vector4<T> pos)
{
	(*this)(4, 1) = pos.x;
	(*this)(4, 2) = pos.y;
	(*this)(4, 3) = pos.z;
}

template<class T>
inline const Vector4<T> Matrix4x4<T>::GetRight()
{
	Vector4<T> direction;

	direction.x = (*this)(1, 1);
	direction.y = (*this)(2, 1);
	direction.z = (*this)(3, 1);
	direction.w = 0;

	return direction;
}

template<class T>
inline const Vector4<T> Matrix4x4<T>::GetUp()
{
	Vector4<T> direction;

	direction.x = (*this)(1, 2);
	direction.y = (*this)(2, 2);
	direction.z = (*this)(3, 2);
	direction.w = 0;

	return direction;
}

template<class T>
inline const Vector4<T> Matrix4x4<T>::GetForward()
{
	Vector4<T> direction;

	direction.x = (*this)(1, 3);
	direction.y = (*this)(2, 3);
	direction.z = (*this)(3, 3);
	direction.w = 0;

	return direction;
}

template<class T>
inline const std::array<std::array<T, 4>, 4>* Matrix4x4<T>::GetMatrix() const
{
	return &myMatrix;
}



template<class T>
inline void Matrix4x4<T>::Decompose(Vector3f& aPosition, Vector3f& aRotation, Vector3f& aScale)
{
	static const float ZPI = 3.1415f;
	static const float RAD2DEG = (180.f / ZPI);
	const Matrix4x4<T>& mat = *this;
	Vector4f scaleX = { mat(1,1),mat(1,2) ,mat(1,3) ,mat(1,4) };
	Vector4f scaleY = { mat(2,1),mat(2,2) ,mat(2,3) ,mat(2,4) };
	Vector4f scaleZ = { mat(3,1),mat(3,2) ,mat(3,3) ,mat(3,4) };

	aScale.x = scaleX.Length();
	aScale.y = scaleY.Length();
	aScale.z = scaleZ.Length();

	scaleX.Normalize();
	scaleY.Normalize();
	scaleZ.Normalize();

	Quatf q = Quatf::CreateFromOrthonormalBasisVectors(scaleX, scaleY, scaleZ);
	aRotation = q.GetEulerAnglesDegrees();

	aPosition.x = mat.GetPosition().x;
	aPosition.y = mat.GetPosition().y;
	aPosition.z = mat.GetPosition().z;
}

template<class T>
inline void Matrix4x4<T>::SetRotation(const Matrix3x3<T>& aRotationMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			myMatrix[y][x] = aRotationMatrix(y + 1, x + 1);
		}
	}
}

template<class T>
inline Matrix3x3<T> Matrix4x4<T>::GetRotation()
{
	Matrix3x3<T> rotMat;

	for (int i = 0; i < 3; i++)
	{
		Vector3<T> dir;

		for (int j = 0; j < 3; j++)
		{
			dir[j] = (*this)(i + 1, j + 1);
		}
		
		dir.Normalize();
		rotMat(i + 1, 1) = dir.x;
		rotMat(i + 1, 2) = dir.y;
		rotMat(i + 1, 3) = dir.z;
	}

	return rotMat;
}


template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateScaleMatrix(const Vector4<T>& aScale)
{
	Matrix4x4<T> translationMatrix;
	translationMatrix(1, 1) = aScale.x;
	translationMatrix(2, 2) = aScale.y;
	translationMatrix(3, 3) = aScale.z;
	return translationMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateScaleMatrix(const Vector3<T>& aScale)
{
	Matrix4x4<T> translationMatrix;
	translationMatrix(1, 1) = aScale.x;
	translationMatrix(2, 2) = aScale.y;
	translationMatrix(3, 3) = aScale.z;
	return translationMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateTranslation(const Vector4<T>& aPosition)
{
	Matrix4x4<T> translationMatrix;
	translationMatrix(4, 1) = aPosition.x;
	translationMatrix(4, 2) = aPosition.y;
	translationMatrix(4, 3) = aPosition.z;
	return translationMatrix;
}

template<class T>
inline Matrix4x4<T> Matrix4x4<T>::CreateTranslation(const Vector3<T>& aPosition)
{
	Matrix4x4<T> translationMatrix;
	translationMatrix(4, 1) = aPosition.x;
	translationMatrix(4, 2) = aPosition.y;
	translationMatrix(4, 3) = aPosition.z;
	return translationMatrix;
}

template<class T>
inline Vector4<T> Matrix4x4<T>::GetColumn(int index)
{
	return { myMatrix[index][0], myMatrix[index][1], myMatrix[index][2], myMatrix[index][3] };
}

template<class T>
inline void Matrix4x4<T>::SetColumn(int index, const Vector4<T> aVec)
{
	myMatrix[index][0] = aVec.x;
	myMatrix[index][1] = aVec.y;
	myMatrix[index][2] = aVec.z;
	myMatrix[index][3] = aVec.w;
}

template<class T>
inline Vector4<T> Matrix4x4<T>::GetRow(int index)
{
	return { myMatrix[0][index], myMatrix[1][index], myMatrix[2][index], myMatrix[3][index] };
}


#pragma region ---- OPERATORS

template<class T>
inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
{
	assert(aRow <= 4 && aColumn <= 4 && "Index out of range.");
	assert(aRow > 0 && aColumn > 0 && "Index out of range.");

	return myMatrix[aRow - 1][aColumn - 1];
}

template<class T>
inline T Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
{
	assert(aRow <= 4 && aColumn <= 4 && "Index out of range.");
	assert(aRow > 0 && aColumn > 0 && "Index out of range.");

	return myMatrix[aRow - 1][aColumn - 1];
}

template<class T>
inline T& Matrix4x4<T>::operator[](const int& aIndex)
{
	int x = (int)(aIndex / 4);
	int y = (int)(aIndex % 4);

	return (*this)(x + 1, y + 1);
}

template<class T>
inline const T& Matrix4x4<T>::operator[](const int& aIndex) const
{
	int x = (int)(aIndex / 4);
	int y = (int)(aIndex % 4);

	return (*this)(x + 1, y + 1);
}

#pragma endregion