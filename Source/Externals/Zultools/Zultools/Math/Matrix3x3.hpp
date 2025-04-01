#pragma once

#include <array>

#include "Vector3.hpp"
#include "Matrix4x4.hpp"

#include <Eigen/Dense>

template <class T>

class Matrix3x3
{
public:
	~Matrix3x3() = default;

	// Creates the identity matrix.
	Matrix3x3<T>()
	{
		myMatrix = std::array<std::array<T, 3>, 3>();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (x == y)
				{
					myMatrix[y][x] = 1;
				}
				else
				{
					myMatrix[y][x] = 0;
				}
			}
		}
	}

	// Creates the identity matrix.
	Matrix3x3<T>(std::array<std::array<T, 3>, 3>& anArray)
	{
		myMatrix = anArray;
	}

	// Copy Constructor.
	Matrix3x3<T>(const Matrix3x3<T>& aMatrix)
	{
		myMatrix = std::array<std::array<T, 3>, 3>(*aMatrix.GetMatrix());
	}

	// Copies the top left 3x3 part of the Matrix4x4.
	Matrix3x3<T>(const Matrix4x4<T>& aMatrix)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[y][x] = aMatrix(y + 1, x + 1);
			}
		}
	}

	Eigen::Matrix3f ToEigen();

public:
	void SetRotation(const Matrix3x3<T>& aMatrix);






	// () operator for accessing element (row, column) for read/write or read, respectively.
	T& operator()(const int aRow, const int aColumn)
	{
		assert(aRow <= 3 && aColumn <= 3 && "Index out of range.");
		assert(aRow > 0 && aColumn > 0 && "Index out of range.");

		return myMatrix[aRow - 1][aColumn - 1];
	}

	const T& operator()(const int aRow, const int aColumn) const
	{
		assert(aRow <= 3 && aColumn <= 3 && "Index out of range.");
		assert(aRow > 0 && aColumn > 0 && "aColumn - 1Index out of range.");

		return myMatrix[aRow - 1][aColumn - 1];
	}

	// Creates a transposed copy of the matrix.
	Matrix3x3<T> GetTranspose() const
	{
		Matrix3x3<T> newMatrix = Matrix3x3<T>(*this);

		std::swap(newMatrix(2, 1), newMatrix(1, 2));
		std::swap(newMatrix(3, 1), newMatrix(1, 3));
		std::swap(newMatrix(3, 2), newMatrix(2, 3));

		return newMatrix;
	}

	// Static functions for creating rotation matrices.
	static Matrix3x3<T> CreateRotationAroundX(const T aAngleInRadians)
	{
		Matrix3x3<T> newMatrix = Matrix3x3<T>();

		newMatrix(1, 1) = 1;
		newMatrix(2, 2) = std::cos(aAngleInRadians);
		newMatrix(2, 3) = std::sin(aAngleInRadians);
		newMatrix(3, 2) = -std::sin(aAngleInRadians);
		newMatrix(3, 3) = std::cos(aAngleInRadians);

		return newMatrix;
	}

	static Matrix3x3<T> CreateRotationAroundY(const T aAngleInRadians)
	{
		Matrix3x3<T> newMatrix = Matrix3x3<T>();

		newMatrix(1, 1) = std::cos(aAngleInRadians);
		newMatrix(1, 3) = -std::sin(aAngleInRadians);
		newMatrix(2, 2) = 1;
		newMatrix(3, 1) = std::sin(aAngleInRadians);
		newMatrix(3, 3) = std::cos(aAngleInRadians);

		return newMatrix;
	}

	static Matrix3x3<T> CreateRotationAroundZ(const T aAngleInRadians)
	{
		Matrix3x3<T> newMatrix = Matrix3x3<T>();

		newMatrix(1, 1) = std::cos(aAngleInRadians);
		newMatrix(1, 2) = std::sin(aAngleInRadians);
		newMatrix(2, 1) = -std::sin(aAngleInRadians);
		newMatrix(2, 2) = std::cos(aAngleInRadians);
		newMatrix(3, 3) = 1;

		return newMatrix;
	}

	const std::array<std::array<T, 3>, 3>* GetMatrix() const
	{
		return &myMatrix;
	}

	void operator =(Matrix3x3<T> aMatrix)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[y][x] = aMatrix(y + 1, x + 1);
			}
		}
	}

	void operator +=(Matrix3x3<T> aMatrix)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[y][x] += aMatrix(y + 1, x + 1);
			}
		}
	}

	void operator *=(Matrix3x3<T> aMatrix)
	{
		Matrix3x3<T> newMatrix;

		for (int row = 1; row <= 3; row++)
		{
			for (int column = 1; column <= 3; column++)
			{
				T value = 0;

				for (int i = 1; i <= 3; i++)
				{
					value += (*this)(row, i) * aMatrix(i, column);
				}

				newMatrix(row, column) = value;
			}
		}

		myMatrix = *newMatrix.GetMatrix();
	}

	void operator -=(Matrix3x3<T> aMatrix)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				myMatrix[y][x] -= aMatrix(y + 1, x + 1);
			}
		}
	}

private:
	std::array<std::array<T, 3>, 3> myMatrix;
};

template<class T>
const Matrix3x3<T> operator +(Matrix3x3<T> aMatrix0, Matrix3x3<T> aMatrix1)
{
	Matrix3x3<T> addedMatrixes;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			addedMatrixes(y + 1, x + 1) = aMatrix0(y + 1, x + 1) + aMatrix1(y + 1, x + 1);
		}
	}

	return addedMatrixes;
}

template<class T>
const Matrix3x3<T> operator -(Matrix3x3<T> aMatrix0, Matrix3x3<T> aMatrix1)
{
	Matrix3x3<T> subtractedMatrixes;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			subtractedMatrixes(y + 1, x + 1) = aMatrix0(y + 1, x + 1) - aMatrix1(y + 1, x + 1);
		}
	}

	return subtractedMatrixes;
}

template<class T>
const Matrix3x3<T> operator *(Matrix3x3<T> aMatrix0, Matrix3x3<T> aMatrix1)
{
	Matrix3x3<T> newMatrix;

	for (int row = 1; row <= 3; row++)
	{
		for (int column = 1; column <= 3; column++)
		{
			T value = 0;

			for (int i = 1; i <= 3; i++)
			{
				value += aMatrix0(row, i) * aMatrix1(i, column);
			}

			newMatrix(row, column) = value;
		}
	}

	return newMatrix;
}

template<class T>
const Vector3<T> operator *(Vector3<T> aVector3, Matrix3x3<T> aMatrix0)
{
	Vector3<T> newVector;

	for (T column = 0; column < 3; column++)
	{
		T value = 0;

		for (T row = 0; row < 3; row++)
		{
			// Add one since matrices index starts at 1.
			value += aMatrix0(row + 1, column + 1) * aVector3[row];
		}

		newVector[column] = value;
	}

	return newVector;
}

template<class T>
const bool operator ==(Matrix3x3<T> aMatrix0, Matrix3x3<T> aMatrix1)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (aMatrix0(y + 1, x + 1) != aMatrix1(y + 1, x + 1))
			{
				return false;
			}
		}
	}

	return true;
}

template<class T>
inline Eigen::Matrix3f Matrix3x3<T>::ToEigen()
{
	Eigen::Matrix3f eigenMatrix;

	for (int i = 0; i < 3; ++i) 
	{
		for (int j = 0; j < 3; ++j) 
		{
			eigenMatrix(i, j) = (*this)(i + 1, j + 1);
		}
	}

	return eigenMatrix;
}

template<class T>
inline void Matrix3x3<T>::SetRotation(const Matrix3x3<T>& aMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			myMatrix[y][x] = aMatrix(y + 1, x + 1);
		}
	}
}
