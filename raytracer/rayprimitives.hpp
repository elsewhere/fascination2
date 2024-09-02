#ifndef _RAYPRIMITIVES_HPP_
#define _RAYPRIMITIVES_HPP_

#include "../externs.hpp"

class RayPrimitive
{
public:
	RayPrimitive();
	~RayPrimitive();

	virtual bool checkIntersection(Vector &position, Vector &direction);
	virtual float getIntersection(Vector &position, Vector &direction);
	virtual void getTextureCoordinates(Vector &intersection, float &u, float &v);

	int objectID;
private:
};

class Plane : public RayPrimitive
{
public:
	Plane();
	Plane(float pheight);
	~Plane();

	bool checkIntersection(Vector &position, Vector &direction);
	float getIntersection(Vector &position, Vector &direction);
	void getTextureCoordinates(Vector &intersection, float &u, float &v);

	float height;
};

class Tunnel : public RayPrimitive
{
public:
	Tunnel();
	Tunnel(float pradius);
	~Tunnel();

	bool checkIntersection(Vector &position, Vector &direction);
	float getIntersection(Vector &position, Vector &direction);
	void getTextureCoordinates(Vector &intersection, float &u, float &v);

	float radius;
};

class Sphere : public RayPrimitive
{
public:
	Sphere();
	Sphere(float px, float py, float pz, float pradius);
	~Sphere();

	bool checkIntersection(Vector &position, Vector &direction);
	float getIntersection(Vector &position, Vector &direction);
	void getTextureCoordinates(Vector &intersection, float &u, float &v);

	float radius;
	float xpos, ypos, zpos;
};

#endif