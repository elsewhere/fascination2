#include "beziercurve.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

QuadraticBezierCurve::QuadraticBezierCurve()
{
	P1 = Vector3(0,0,0);
	P2 = Vector3(0,0,0);
	P3 = Vector3(0,0,0);
}

QuadraticBezierCurve::QuadraticBezierCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
}

QuadraticBezierCurve::~QuadraticBezierCurve()
{
}

void QuadraticBezierCurve::set(Vector3 &point1, Vector3 &point2, Vector3 &point3)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
}

Vector3 QuadraticBezierCurve::getValue(float t)
{
	Vector3 temp;
	temp.x = bezierValue(P1.x, P2.x, P3.x, t);
	temp.y = bezierValue(P1.y, P2.y, P3.y, t);
	temp.z = bezierValue(P1.z, P2.z, P3.z, t);
	return temp;
}
Vector3 QuadraticBezierCurve::getDerivative(float t)
{
	Vector3 temp;
	temp.x = derivativeValue(P1.x, P2.x, P3.x, t);
	temp.y = derivativeValue(P1.y, P2.y, P3.y, t);
	temp.z = derivativeValue(P1.z, P2.z, P3.z, t);
	return temp;
}

inline float QuadraticBezierCurve::bezierValue(float p1, float p2, float p3, float t)
{
	const float tr = 1-t;
	return tr*tr*p1 + 2*tr*t*p2 + t*t*p3;
}
inline float QuadraticBezierCurve::derivativeValue(float p1, float p2, float p3, float t)
{
	return ((-2+2*t)*p1 + (-2*t+1)*p2 + (2*t)*p3);
}

CubicBezierCurve::CubicBezierCurve()
{
	P1 = Vector3(0,0,0);
	P2 = Vector3(0,0,0);
	P3 = Vector3(0,0,0);
	P4 = Vector3(0,0,0);
}

CubicBezierCurve::CubicBezierCurve(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
	P4 = point4;
}
CubicBezierCurve::~CubicBezierCurve()
{
}

void CubicBezierCurve::set(Vector3 &point1, Vector3 &point2, Vector3 &point3, Vector3 &point4)
{
	P1 = point1;
	P2 = point2;
	P3 = point3;
	P4 = point4;
}

Vector3 CubicBezierCurve::getValue(float t)
{
	Vector3 temp;
	temp.x = bezierValue(P1.x, P2.x, P3.x, P4.x, t);
	temp.y = bezierValue(P1.y, P2.y, P3.y, P4.y, t);
	temp.z = bezierValue(P1.z, P2.z, P3.z, P4.z, t);
	return temp;
}

Vector3 CubicBezierCurve::getDerivative(float t)
{
	Vector3 temp;
	temp.x = derivativeValue(P1.x, P2.x, P3.x, P4.x, t);
	temp.y = derivativeValue(P1.y, P2.y, P3.y, P4.y, t);
	temp.z = derivativeValue(P1.z, P2.z, P3.z, P4.z, t);
	return temp;
}

inline float CubicBezierCurve::bezierValue(float p1, float p2, float p3, float p4, float t)
{
	const float tr = 1-t;
	return tr*tr*tr*p1 + 3*t*tr*tr*p2 + 3*t*t*tr*p3 + t*t*t*p4;
}
inline float CubicBezierCurve::derivativeValue(float p1, float p2, float p3, float p4, float t)
{
	return ((-3*t*t+6*t-3)*p1 + (3*t*t-4*t+1)*p2 + (-3*t*t+2*t)*p3 + (3*t*t)*p4);
}
