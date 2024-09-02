#ifndef _BEZIERCURVE_HPP_
#define _BEZIERCURVE_HPP_

#include "Vector.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	class __declspec(dllexport) QuadraticBezierCurve
	{
	public:
		QuadraticBezierCurve();
		QuadraticBezierCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3);
		~QuadraticBezierCurve();

		void set(Vector3 &point1, Vector3 &point2, Vector3 &point3);

		Vector3 getValue(float t);
		Vector3 getDerivative(float t);

	private:

		Vector3 P1, P2, P3;

		inline float bezierValue(float p1, float p2, float p3, float t);
		inline float derivativeValue(float p1, float p2, float p3, float t);
	};

	class __declspec(dllexport) CubicBezierCurve
	{
	public:
		CubicBezierCurve();
		CubicBezierCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4);
		~CubicBezierCurve();

		void set(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4);

		Vector3 getValue(float t);
		Vector3 getDerivative(float t);

	private:

		Vector3 P1, P2, P3, P4;

		inline float bezierValue(float p1, float p2, float p3, float p4, float t);
		inline float derivativeValue(float p1, float p2, float p3, float p4, float t);
	};

}

#endif