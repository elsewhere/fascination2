#include "rayprimitives.hpp"

RayPrimitive::RayPrimitive()
{
}
RayPrimitive::~RayPrimitive()
{
}

bool RayPrimitive::checkIntersection(Vector &position, Vector &direction)
{
	return false;
}

float RayPrimitive::getIntersection(Vector &position, Vector &direction)
{
	return 0.0f;
}
void RayPrimitive::getTextureCoordinates(Vector &intersection, float &u, float &v)
{
	u = 0.0f;
	v = 0.0f;
}

Plane::Plane()
{
	height = 1.0f;
}

Plane::Plane(float pheight)
{
	height = pheight;
}

Plane::~Plane()
{
}
bool Plane::checkIntersection(Vector &position, Vector &direction)
{
	if (direction.y == 0)
		return false;
	else return true;
}

float Plane::getIntersection(Vector &position, Vector &direction)
{
	float t;
	if (direction.y != 0)
	{
		if (direction.y < 0)
			t = (position.y-height) / direction.y;
		else
			t = (position.y+height) / direction.y;
	}
	else
	{
		t = 0.0f;
	}
	return t;
}

void Plane::getTextureCoordinates(Vector &intersection, float &u, float &v)
{
	u = intersection.x;
	v = intersection.z;
}


Tunnel::Tunnel()
{
	radius = 1.0f;
}
Tunnel::Tunnel(float pradius)
{
	radius = pradius;
}

Tunnel::~Tunnel()
{
}

bool Tunnel::checkIntersection(Vector &position, Vector &direction)
{
	float a, b, c;
	a = direction.x * direction.x + direction.y * direction.y;
	b = 2*(direction.x * position.x + direction.y * position.y);
	c = position.x * position.x + position.y * position.y - radius * radius;

	if ((b*b - 4*a*c) > 0)
		return true;
	else return false;
}

float Tunnel::getIntersection(Vector &position, Vector &direction)
{
	float a, b, c, temp, t;
	
	a = direction.x * direction.x + direction.y * direction.y;
	b = 2*(direction.x * position.x + direction.y * position.y);
	c = position.x * position.x + position.y * position.y - radius * radius;

	temp = (float)sqrt(b*b-4*a*c);
	if (a == 0)
		t = 0.0f;
	else
	{
		float t1 = (-b + temp)/(2*a);
		float t2 = (-b - temp)/(2*a);

		if (t1 > 0) t=t1;
		else t=t2;
	}
	return t;
}
void Tunnel::getTextureCoordinates(Vector &intersection, float &u, float &v)
{
	u = intersection.z*0.2f;
	v = (float)fabs(atan2(intersection.y, intersection.x))/(3.1415926535897932f);

}

Sphere::Sphere()
{
	xpos = 0.0f;
	ypos = 0.0f;
	zpos = 0.0f;
	radius = 1.0f;
}

Sphere::Sphere(float px, float py, float pz, float pradius)
{
	xpos = px;
	ypos = py;
	zpos = pz;
	radius = pradius;
}
Sphere::~Sphere()
{
}

bool Sphere::checkIntersection(Vector &position, Vector &direction)
{
	float a, b, c;
	a = direction.x*direction.x + direction.y*direction.y + direction.z*direction.z;
	b = 2*(direction.x*(position.x+xpos) + direction.y*(position.y+ypos) + direction.z*(position.z+zpos));
	c = (position.x+xpos)*(position.x+xpos)+ (position.y+ypos)*(position.y+ypos) + (position.z+zpos)*(position.z+zpos) - radius*radius;

	if ((b*b - 4*a*c) > 0)
		return true;
	else return false;
}
float Sphere::getIntersection(Vector &position, Vector &direction)
{
	float a, b, c, temp, t;

//	a = direction.x*direction.x + direction.y*direction.y + direction.z*direction.z;
//	b = 2*(direction.x*position.x + direction.y*position.y + direction.z*position.z)
//	c = position.x*position.x + position.y*position.y + position.z*position.z - radius*radius;

	a = direction.x*direction.x + direction.y*direction.y + direction.z*direction.z;
	b = 2*(direction.x*(position.x-xpos) + direction.y*(position.y-ypos) + direction.z*(position.z-zpos));
	c = (position.x-xpos)*(position.x-xpos)+ (position.y-ypos)*(position.y-ypos) + (position.z-zpos)*(position.z-zpos) - radius*radius;

	const float D = b*b-4*a*c;

	if (D < 0) return -1;
	temp = (float)sqrt(D);

	float t1 = (-b + temp)/(2*a);
	float t2 = (-b - temp)/(2*a);

/*	if (t1 < t2)
		t = t1;
	else 
		t = t2;
*/
	if (t1 > 0 && t2 < 0)
		t = t1;
	else
		t = t2;
/*
	if (t2 < 0 && t1 > 0)
		t = t1;
	if (t1 < 0 && t2 > 0)
		t = t2;
*/
	return t;
}

void Sphere::getTextureCoordinates(Vector &intersection, float &u, float &v)
{
	float xtemp = intersection.x - xpos;
	float ytemp = intersection.y - ypos;
	float ztemp = intersection.z - zpos;
	u = (float)asin(ytemp / sqrt(xtemp*xtemp + ytemp*ytemp + ztemp*ztemp))*0.5f + 0.5f;
	v = (float)fabs(atan2(ztemp, xtemp))/(3.1415926535897932f);

//	u = (float)asin(xtemp / sqrt(xtemp*xtemp + ztemp*ztemp))*0.5f + 0.5f;
//	v = (float)fabs(atan2(ytemp, xtemp))/3.141592f;
}