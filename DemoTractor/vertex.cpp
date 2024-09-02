//-------------------------------------------------------
//	Headers
//-------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "vertex.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//-------------------------------------------------------
//	Class code
//-------------------------------------------------------

Vertex::Vertex()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	normal = Vector3(0.0f, 0.0f, 0.0f);
	u = 0.0f;
	v = 0.0f;
}

Vertex::Vertex(Vector3 vec)
{
	position = vec;
	normal = Vector3(0.0f, 0.0f, 0.0f);	
	u = 0.0f;
	v = 0.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	position = Vector3(x, y, z);
	normal = Vector3(0.0f, 0.0f, 0.0f);
	u = 0.0f;
	v = 0.0f;
}

Vertex::~Vertex()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	normal = Vector3(0.0f, 0.0f, 0.0f);
	u = 0.0f;
	v = 0.0f;
}

//-------------------------------------------------------
//	Getters
//-------------------------------------------------------

Vector3 Vertex::getPosition()
{
	return position;
}

Vector3 Vertex::getOldPosition()
{
	return old;
}

Vector3 Vertex::getNormal()
{
	return normal;
}

//-------------------------------------------------------
//	Setters
//-------------------------------------------------------

void Vertex::setPosition(Vector3 vec)
{
	position = vec;
}

void Vertex::setNormal(Vector3 vec)
{
	normal = vec;
}

void Vertex::setUV(float uu, float vv)
{
	u = uu;
	v = vv;
}