// 4x4 Matrixluokka 
#ifndef _MATRIX4_HPP_
#define _MATRIX4_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <math.h>

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Matrix class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Matrix4
	{
		public:
			Matrix4();
			Matrix4(float val);
			Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8,float m9, float m10, float m11, float m12, float m13, float m14, float m15);

			~Matrix4();

			Matrix4 makeIdentity();
			Matrix4 makeTranspose();

			Matrix4 makeProjection (float fovy, float ar,			// create projection matrix
									float zNear, float zFar);

			
			void getGL(float *array);		// easy to dump into opengl functions

			Matrix4 operator + (Matrix4 const &mat);
			Matrix4 operator += (Matrix4 const &mat);
			Matrix4 operator - (Matrix4 const &mat);
			Matrix4 operator -= (Matrix4 const &mat);
			Matrix4 operator * (Matrix4 const &mat);
			Matrix4 operator *= (Matrix4 const &mat);
			Matrix4 operator * (float const &value);
			Matrix4 operator *= (float const &value);


			void operator = (Matrix4 const &mat);
			void operator = (float const &value);

			bool operator == (Matrix4 const &mat);

			float data[4][4];
	};
}

#endif