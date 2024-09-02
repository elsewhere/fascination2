// 4x4 Matrixluokka kaikilla leluilla

#ifndef _MATRIX4_HPP_
#define _MATRIX4_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <string.h>


//--------------------------------------------------------------------------------------------
//  Matrix class
//--------------------------------------------------------------------------------------------

class Matrix4
{
	public:
		Matrix4();
		Matrix4(float value);
		Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, 
				float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);
		~Matrix4();

		Matrix4 makeIdentity();
		Matrix4 makeTranspose();
		Matrix4 makeInverseTranspose();

		Matrix4 operator+(const Matrix4 & rhs);
		Matrix4 operator-(const Matrix4 & rhs);
		Matrix4 operator*(const Matrix4 & rhs);
		Matrix4 operator*(const float rhs);
		Matrix4 operator/(const float rhs);

		void operator = (Matrix4 const &mat);
		void operator = (float const &value);

		bool operator == (Matrix4 const &mat);
		bool operator != (Matrix4 const &mat);

		float data[16];

		operator float* () const {return (float*) this;}
		operator const float* () const {return (const float*) this;}
};

#endif