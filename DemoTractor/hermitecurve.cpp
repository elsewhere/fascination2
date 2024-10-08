#include "hermitecurve.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

HermiteCurve::HermiteCurve()
{
	P1 = Vector3(0,0,0);
	P2 = Vector3(0,0,0);
	P3 = Vector3(0,0,0);
	P4 = Vector3(0,0,0);
}

HermiteCurve::HermiteCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
	P4 = point4;
}
HermiteCurve::~HermiteCurve()
{
}

void HermiteCurve::set(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
	P4 = point4;
}

Vector3 HermiteCurve::getValue(float t)
{
	Vector3 temp;
	temp.x = value(P1.x, P2.x, P3.x, P4.x, t);
	temp.y = value(P1.y, P2.y, P3.y, P4.y, t);
	temp.z = value(P1.z, P2.z, P3.z, P4.z, t);
	return temp;
}

Vector3 HermiteCurve::getDerivative(float t)
{
	Vector3 temp;
	temp.x = derivativeValue(P1.x, P2.x, P3.x, P4.x, t);
	temp.y = derivativeValue(P1.y, P2.y, P3.y, P4.y, t);
	temp.z = derivativeValue(P1.z, P2.z, P3.z, P4.z, t);
	return temp;
}

inline float HermiteCurve::value(float p1, float p2, float p3, float p4, float t)
{
	const float t2 = t*t;
	const float t3 = t*t*t;
	return (2*t3-3*t2+1)*p1 + (-2*t3+3*t2)*p4 + (t3-2*t2+t)*p2 + (t3-t2)*p3;
}
inline float HermiteCurve::derivativeValue(float p1, float p2, float p3, float p4, float t)
{
	return ((-3*t*t+6*t-3)*p1 + (3*t*t-4*t+1)*p2 + (-3*t*t+2*t)*p3 + (3*t*t)*p4);
}
