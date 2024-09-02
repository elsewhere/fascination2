//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include <math.h>
#include "face.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Face::Face()
{
	a = NULL;
	b = NULL;
	c = NULL;
	aa = 0;
	bb = 0;
	cc = 0;
	texture = NULL;
	normal = Vector3(0.0f, 0.0f, 0.0f);

	memset(textureName, 0, sizeof(textureName));
}

Face::~Face()
{
	a = NULL;
	b = NULL;
	c = NULL;
	aa = 0;
	bb = 0;
	cc = 0;
	texture = NULL;
	normal = Vector3(0.0f, 0.0f, 0.0f);

	memset(textureName, 0, sizeof(textureName));
}

bool Face::calculateNormal()
{		
	float dx, dy, dz, dx2, dy2, dz2;
	float len;
	Vector3 tmp;

	if(!a || !b || !c) return false;

    dx = b->position.x - a->position.x; dy = b->position.y - a->position.y; dz = b->position.z - a->position.z;
    dx2= c->position.x - a->position.x; dy2= c->position.y - a->position.y; dz2= c->position.z - a->position.z;

	tmp = Vector3((dy * dz2 - dz * dy2), (dz * dx2 - dx * dz2), (dx * dy2 - dy * dx2));
	
	len = 1.0f / tmp.length();
	normal = tmp * len;

	return true;
}

void Face::debug()
{
	printf("Face normal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
}

bool Face::setVertex(Vertex *v1, Vertex *v2, Vertex *v3)
{
	if(v1 == NULL || v2 == NULL || v3 == NULL)
	{
		dmsMsg("Face::setVertex() Error: One or more of the Vertex pointers were NULL\n");
		return false;
	}

	a = v1;
	b = v2;
	c = v3;

	return true;
}

bool Face::setTexture(char *name)
{
	extern TextureManager *tManager;

	texture = tManager->getTextureName(name);
	if(!texture)
	{	
		#ifdef _CRITICAL_DEBUG
			dmsMsg("Face::setTexture() Error: TextureManager doesn't have a texture named as \"%s\"\n", name);
		#endif

		return false;
	}

	sprintf(textureName, "%s", name);

	return true;
}
