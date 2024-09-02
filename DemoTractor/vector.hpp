#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <math.h>
#include "matrix.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	class __declspec(dllexport) Vector3;
	class __declspec(dllexport) Vector;

//--------------------------------------------------------------------------------------------
//  Vector class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Vector
	{
		friend class Matrix;	

		public:
			Vector();
			Vector(float px, float py, float pz);
			Vector(float px, float py, float pz, float pa);
			Vector(Vector &example);
			Vector(Vector3 &example);
			~Vector();

			Vector crossProduct(Vector &vect);
			float dotProduct(Vector &vect);


			Vector operator + (Vector const &vect);
			Vector operator - (Vector const &vect);
			Vector operator += (Vector const &vect);
			Vector operator -= (Vector const &vect);

			Vector operator * (Matrix const &mat);
			Vector operator *= (Matrix const &mat);
			Vector operator * (const float &value);
			Vector operator *= (float const &value);
			Vector operator / (const float &value);

			bool operator == (Vector const &vect);
			void operator = (Vector const &vect);
			
			Vector normalize();
			float length();

			float x, y, z;

			float a; // tämän ei pitäisi olla tässä! läst minute häk
		private:
	};

	class __declspec(dllexport) Vector3
	{
		friend class Matrix;	

		public:
			Vector3();
			Vector3(float px, float py, float pz);
            Vector3(const class Vector3 &v) { this->x = v.x; this->y = v.y; this->z = v.z; }
			Vector3(Vector &example);
			~Vector3();

			Vector3 crossProduct(Vector3 &vect);
			float dotProduct(Vector3 &vect);

			Vector3 operator + (Vector3 const &vect);
			Vector3 operator - (Vector3 const &vect);
			Vector3 operator += (Vector3 const &vect);
			Vector3 operator -= (Vector3 const &vect);

			Vector3 operator * (Matrix const &mat);
			Vector3 operator *= (Matrix const &mat);
			Vector3 operator * (const float &value);
			Vector3 operator *= (float const &value);
			Vector3 operator / (const float &value);

			bool operator == (Vector3 const &vect);
			void operator = (Vector3 const &vect);
			
			Vector3 normalize();
			float length();

			float x, y, z;
			
		private:
	};
}

#endif