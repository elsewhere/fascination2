//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "object.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Object::Object()
{
	nFaces = 0;
	nVertices = 0;
	position = Vector3(0.0f, 0.0f, 0.0f);

	vertex = NULL;
	face = NULL;
}

Object::~Object()
{
	release();
}

bool Object::initVertices(unsigned int i)
{
	nVertices = i;

	vertex = new Vertex[nVertices];
	if(!vertex)
	{
		dmsMsg("Object::initVertices() Error: Could not allocate memory for vertices\n");		
		return false;
	}

	return true;
}

bool Object::initFaces(unsigned int i)
{
	nFaces = i;

	face = new Face[nFaces];
	if(!face)
	{
		dmsMsg("Object::initFaces() Error: Could not allocate memory for faces\n");
		return false;
	}

	return true;
}

void Object::render()
{
	unsigned int i;
	Vertex *v1 = NULL;
	Vertex *v2 = NULL;
	Vertex *v3 = NULL;
	Face *f = NULL;

	glPushMatrix();
	
	for(i = 0; i < nFaces; i++)
	{
		f = &face[i];		

		// uusitapa
		if(f)
		{
			v1 = f->a;
			v2 = f->b;
			v3 = f->c;
		}
	
		glBegin(GL_TRIANGLES);

		if(v1 && v2 && v3)
		{	
			//glNormal3f(f->normal.x, f->normal.y, f->normal.z);
			glNormal3f(v1->normal.x, v1->normal.y, v1->normal.z); glTexCoord2f(v1->u, v1->v); glVertex3f(v1->position.x, v1->position.y, v1->position.z);
			glNormal3f(v2->normal.x, v2->normal.y, v2->normal.z); glTexCoord2f(v2->u, v2->v); glVertex3f(v2->position.x, v2->position.y, v2->position.z);
			glNormal3f(v3->normal.x, v3->normal.y, v3->normal.z); glTexCoord2f(v3->u, v3->v); glVertex3f(v3->position.x, v3->position.y, v3->position.z);
		}

		glEnd();
	}
	
	glPopMatrix();
}

void Object::render(float u, float v)
{
	unsigned int i;
	Vertex *v1 = NULL;
	Vertex *v2 = NULL;
	Vertex *v3 = NULL;
	Face *f = NULL;

	glPushMatrix();
	
	for(i = 0; i < nFaces; i++)
	{
		f = &face[i];		

		// uusitapa
		if(f)
		{
			v1 = f->a;
			v2 = f->b;
			v3 = f->c;
		}
	
		glBegin(GL_TRIANGLES);

		if(v1 && v2 && v3)
		{	
			//glNormal3f(f->normal.x, f->normal.y, f->normal.z);
			glTexCoord2f(v1->u+u, v1->v+v); glNormal3f(v1->normal.x, v1->normal.y, v1->normal.z); glVertex3f(v1->position.x, v1->position.y, v1->position.z);
			glTexCoord2f(v2->u+u, v2->v+v); glNormal3f(v2->normal.x, v2->normal.y, v2->normal.z); glVertex3f(v2->position.x, v2->position.y, v2->position.z);
			glTexCoord2f(v3->u+u, v3->v+v); glNormal3f(v3->normal.x, v3->normal.y, v3->normal.z); glVertex3f(v3->position.x, v3->position.y, v3->position.z);
		}

		glEnd();
	}
	
	glPopMatrix();
}

void Object::renderCel(Vector3 lightPos, unsigned int id)
{
	unsigned int i;
	Vertex *v1 = NULL;
	Vertex *v2 = NULL;
	Vertex *v3 = NULL;
	Face *f = NULL;	

	glPushMatrix();	
	
	for(i = 0; i < nFaces; i++)
	{
		f = &face[i];		

		// uusitapa
		if(f)
		{
			v1 = f->a;
			v2 = f->b;
			v3 = f->c;
		}		
	
		glBegin(GL_TRIANGLES);

		if(v1 && v2 && v3)
		{	
			Vector3 n1 = f->a->normal;
			Vector3 n2 = f->b->normal;
			Vector3 n3 = f->c->normal;
			
			n1.normalize();
			n2.normalize();
			n3.normalize();
			float tx1 = lightPos.dotProduct(n1);
			float tx2 = lightPos.dotProduct(n2);
			float tx3 = lightPos.dotProduct(n3);
			if(tx1 < 0.0f) tx1 = 0.0f;
			if(tx2 < 0.0f) tx2 = 0.0f;
			if(tx3 < 0.0f) tx3 = 0.0f;			
			
			glTexCoord1f(tx1);
			glVertex3f(v1->position.x, v1->position.y, v1->position.z);
			
			glTexCoord1f(tx2);
			glVertex3f(v2->position.x, v2->position.y, v2->position.z);

			glTexCoord1f(tx3);
			glVertex3f(v3->position.x, v3->position.y, v3->position.z);

		}

		glEnd();
	}	
	
	glPopMatrix();
}
void Object::release()
{
	if(vertex)
	{
		delete [] vertex;
		vertex = NULL;
	}

	if(face)
	{
		delete [] face;
		face = NULL;
	}

	nFaces = 0;
	nVertices = 0;

	position = Vector3(0.0f, 0.0f, 0.0f);
}

bool Object::calculateNormals()
{
	unsigned int i;
	char buf[256] = {0};

	for(i = 0; i < nFaces; i++)
	{
		if(!face[i].calculateNormal())
		{
			dmsMsg("Object::calculateNormals() Error: Face normal calculation error\n");
			return false;
		}
	}

	return true;
}

bool Object::calculateVertexNormals()
{
	unsigned int i, j, n;
	Vector3 v;
	Vector3 normal;
	
	for(i = 0; i < nVertices; i++)
	{
		v = vertex[i].position;
		n = 0;
		normal = Vector3(0.0f, 0.0f, 0.0f);
		for(j = 0; j < nFaces; j++)
		{			
				if(face[j].a->position == v ||
				   face[j].b->position == v ||
				   face[j].c->position == v)
				{
					normal = normal + face[j].normal;
					n ++;
				}		
		}
		if(n > 0)
		{
			normal = normal * (1.0f / (float)n);
			normal.normalize();
			vertex[i].normal = normal;
		}
	}

	return true;
}

void Object::reduceToUnit()
{	
	float longest=0.0f;
	Vertex *vert = getVertexPointer();
	for (unsigned int i=0;i<getVertices();i++)
	{
		Vector3 position = vert->getPosition();
		const float dist = (position.x*position.x+position.y*position.y+position.z*position.z);
		if (dist > longest)
			longest = dist;
		vert++;
	}
	longest = (float)sqrt(longest);
	vert = getVertexPointer();
	for (i=0;i<getVertices();i++)
	{
		vert->position = vert->position * (1.0f / longest);
		vert++;
	}

}

void Object::debug()
{
	unsigned int i;
	Vector3 v;

	dmsMsg("<b>Object::debug()</b>\n");
	
	dmsMsg("<b>Number of vertices:</b> %d\n\n", nVertices);
		
	if(vertex)
	{
		for(i = 0; i < nVertices; i++)
		{
			v = vertex[i].getPosition();
			dmsMsg("<b>Vertex:</b> %d, <b>X:</b> %f, <b>Y:</b> %f, <b>Z:</b> %f, <b>U:</b> %f, <b>v:</b> %f\n", i, v.x, v.y, v.z, vertex[i].u, vertex[i].v);
		}
	}
	
	dmsMsg("<b>Number of faces:</b> %d</br></br>\n", nFaces);
	
	if(face)
	{
		for(i = 0; i < nFaces; i++)
		{			
			dmsMsg("<b>Face:</b> %d, <b>A:</b> %d, <b>B:</b> %d, <b>C:</b> %d\n", i, face[i].aa, face[i].bb, face[i].cc);
		}
	}
}

//-------------------------------------------------------
//	Getters
//-------------------------------------------------------

unsigned int Object::getFaces()
{
	return nFaces;
}

unsigned int Object::getVertices()
{
	return nVertices;
}

Vertex &Object::copyVertexArray()
{
	return *vertex;
}

Vertex *Object::getVertexPointer()
{	
	return vertex;
}

Face *Object::getFacePointer()
{
	return face;
}

//-------------------------------------------------------
//	Setters
//-------------------------------------------------------

bool Object::setVertex(unsigned int i, Vertex v)
{
	if(i >= 0 && i < nVertices && vertex)
	{
		vertex[i] = v;
		return true;
	}	

	return false;
}

bool Object::setFace(unsigned int i, Face f)
{
	if(i >= 0 && i < nFaces && face)
	{
		face[i] = f;
		return true;
	}

	return false;
}

void Object::setPosition(Vector3 v)
{
	position = v;
}
