//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "Vector.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Vector class code
//--------------------------------------------------------------------------------------------


Vector::Vector()
{
	x = y = z = 0.0f;
}
Vector::Vector(float px, float py, float pz)
{
	x = px;
	y = py;
	z = pz;
}
Vector::Vector(float px, float py, float pz, float pa)
{
	x = px;
	y = py;
	z = pz;
	a = pa;
}
Vector::Vector(Vector &example)
{
	x = example.x;
	y = example.y;
	z = example.z;
}
Vector::Vector(Vector3 &example)
{
	x = example.x;
	y = example.y;
	z = example.z;
}

Vector::~Vector()
{

}

float Vector::length()
{
	return (float)sqrt(x*x+y*y+z*z);
}

Vector Vector::normalize()
{
	float l = length();
	if (l==0)
		return Vector(0,0,0);
	x /= l;
	y /= l;
	z /= l;

	return Vector(x, y, z);
}

float Vector::dotProduct(Vector &vect)
{
	return x*vect.x + y*vect.y + z*vect.z;
}

Vector Vector::crossProduct(Vector &vect)
{
	float tx = y*vect.z-z*vect.y;
	float ty = x*vect.z-z*vect.x;
	float tz = x*vect.y-y*vect.x;
	return Vector(tx, -ty, tz);
}
Vector Vector::operator + (Vector const &vect)
{
	float tx, ty, tz;
	tx = x + vect.x;
	ty = y + vect.y;
	tz = z + vect.z;

	return Vector(tx, ty, tz);
}
Vector Vector::operator - (Vector const &vect)
{
	float tx, ty, tz;
	tx = x - vect.x;
	ty = y - vect.y;
	tz = z - vect.z;
	return Vector(tx, ty, tz);
}
Vector Vector::operator += (Vector const &vect)
{
	x += vect.x;
	y += vect.y;
	z += vect.z;

	return Vector(x, y, z);
}
Vector Vector::operator -= (Vector const &vect)
{
	x -= vect.x;
	y -= vect.y;
	z -= vect.z;

	return Vector(x, y, z);
}
Vector Vector::operator * (Matrix const &mat)
{
	float tx, ty, tz;
	tx = mat.data[0][0]*x + mat.data[0][1]*y + mat.data[0][2]*z;
	ty = mat.data[1][0]*x + mat.data[1][1]*y + mat.data[1][2]*z;
	tz = mat.data[2][0]*x + mat.data[2][1]*y + mat.data[2][2]*z;
	return Vector(tx, ty, tz);
}

Vector	Vector::operator *= (Matrix const &mat)
{
	float tx, ty, tz;
	tx = mat.data[0][0]*x + mat.data[0][1]*y + mat.data[0][2]*z;
	ty = mat.data[1][0]*x + mat.data[1][1]*y + mat.data[1][2]*z;
	tz = mat.data[2][0]*x + mat.data[2][1]*y + mat.data[2][2]*z;

	x = tx;
	y = ty;
	z = tz;
	return Vector(x, y, z);
}
Vector Vector::operator * (float const &value)
{
	float tx, ty, tz;
	tx = x * value;
	ty = y * value;
	tz = z * value;

	return Vector(tx, ty, tz);
}
Vector Vector::operator *= (float const &value)
{
	x *= value;
	y *= value;
	z *= value;

	return Vector(x, y, z);
}
Vector Vector::operator / (float const &value)
{
	if(value <= 0) return Vector(0.0f, 0.0f, 0.0f);

	float tx, ty, tz;
	tx = x / value;
	ty = y / value;
	tz = z / value;

	return Vector(tx, ty, tz);
}
bool Vector::operator == (Vector const &vect)
{
	if (x == vect.x && y == vect.y && z == vect.z)
		return true;
	else return false;

}

void Vector::operator = (Vector const &vect)
{
	x = vect.x;
	y = vect.y;
	z = vect.z;
}



//--------------------------------------------------------------------------------------------
//  Vector3 class code
//--------------------------------------------------------------------------------------------

Vector3::Vector3()
{
	x = y = z = 0.0f;
}
Vector3::Vector3(float px, float py, float pz)
{
	x = px;
	y = py;
	z = pz;
}
/*
Vector3::Vector3(Vector3 &example)
{
	x = example.x;
	y = example.y;
	z = example.z;
}
*/
Vector3::Vector3(Vector &example)
{
	x = example.x;
	y = example.y;
	z = example.z;
}

Vector3::~Vector3()
{

}

float Vector3::length()
{
	return (float)sqrt(x*x+y*y+z*z);
}

Vector3 Vector3::normalize()
{
	float l = length();
	if (l==0)
		return Vector3(0,0,0);
	x /= l;
	y /= l;
	z /= l;

	return Vector3(x, y, z);
}

float Vector3::dotProduct(Vector3 &vect)
{
	return x*vect.x + y*vect.y + z*vect.z;
}

Vector3 Vector3::crossProduct(Vector3 &vect)
{
	float tx = y*vect.z-z*vect.y;
	float ty = x*vect.z-z*vect.x;
	float tz = x*vect.y-y*vect.x;
	return Vector3(tx, -ty, tz);
}
Vector3 Vector3::operator + (Vector3 const &vect)
{
	float tx, ty, tz;
	tx = x + vect.x;
	ty = y + vect.y;
	tz = z + vect.z;

	return Vector3(tx, ty, tz);
}
Vector3 Vector3::operator - (Vector3 const &vect)
{
	float tx, ty, tz;
	tx = x - vect.x;
	ty = y - vect.y;
	tz = z - vect.z;
	return Vector3(tx, ty, tz);
}
Vector3 Vector3::operator += (Vector3 const &vect)
{
	x += vect.x;
	y += vect.y;
	z += vect.z;

	return Vector3(x, y, z);
}
Vector3 Vector3::operator -= (Vector3 const &vect)
{
	x -= vect.x;
	y -= vect.y;
	z -= vect.z;

	return Vector3(x, y, z);
}
Vector3	Vector3::operator * (Matrix const &mat)
{
	float tx, ty, tz;
	tx = mat.data[0][0]*x + mat.data[0][1]*y + mat.data[0][2]*z;
	ty = mat.data[1][0]*x + mat.data[1][1]*y + mat.data[1][2]*z;
	tz = mat.data[2][0]*x + mat.data[2][1]*y + mat.data[2][2]*z;
	return Vector3(tx, ty, tz);
}

Vector3	Vector3::operator *= (Matrix const &mat)
{
	float tx, ty, tz;
	tx = mat.data[0][0]*x + mat.data[0][1]*y + mat.data[0][2]*z;
	ty = mat.data[1][0]*x + mat.data[1][1]*y + mat.data[1][2]*z;
	tz = mat.data[2][0]*x + mat.data[2][1]*y + mat.data[2][2]*z;

	x = tx;
	y = ty;
	z = tz;
	return Vector3(x, y, z);
}
Vector3 Vector3::operator * (float const &value)
{
	float tx, ty, tz;
	tx = x * value;
	ty = y * value;
	tz = z * value;

	return Vector3(tx, ty, tz);
}
Vector3 Vector3::operator *= (float const &value)
{
	x *= value;
	y *= value;
	z *= value;

	return Vector3(x, y, z);
}
Vector3 Vector3::operator / (float const &value)
{
	if(value <= 0) return Vector3(0.0f, 0.0f, 0.0f);

	float tx, ty, tz;
	tx = x / value;
	ty = y / value;
	tz = z / value;

	return Vector3(tx, ty, tz);
}
bool Vector3::operator == (Vector3 const &vect)
{
	if (x == vect.x && y == vect.y && z == vect.z)
		return true;
	else return false;

}

void Vector3::operator = (Vector3 const &vect)
{
	x = vect.x;
	y = vect.y;
	z = vect.z;
}
