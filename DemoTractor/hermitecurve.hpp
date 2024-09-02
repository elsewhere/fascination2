#ifndef _HERMITECURVE_HPP_
#define _HERMITECURVE_HPP_

#include "vector.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	class __declspec(dllexport) HermiteCurve
	{
	public:
		HermiteCurve();
		HermiteCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4);
		~HermiteCurve();

		void set(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4);

		Vector3 getValue(float t);
		Vector3 getDerivative(float t);

	private:

		Vector3 P1, P2, P3, P4;

		inline float value(float p1, float p2, float p3, float p4, float t);
		inline float derivativeValue(float p1, float p2, float p3, float p4, float t);
	};

}

#endif