//--------------------------------------------------------------------------------------------
//  
//	Format description:
//
//	4 bytes : Vertex count
//  4 bytes : Face count
//  
//  Vertex count * 32 bytes : Vertex data (float pos[3], float norm[3], float u, float v)
//  Face count * 24 bytes : Face data (float norm[3], int a, int b, int c)
//
//--------------------------------------------------------------------------------------------

#define DEBUG_STUFF

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmgr.h"
#include "t3d.hpp"

#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Code
//--------------------------------------------------------------------------------------------

T3D::T3D()
{
	vertex = NULL;
	face = NULL;

}

T3D::~T3D()
{
	if(face)
	{
		delete [] face;
		face = NULL;
	}

	if(vertex)
	{
		delete [] vertex;
		vertex = NULL;
	}
}

bool T3D::load(char *name)
{
	unsigned int i;

	FILE *f = fopen(name, "rb");
	if(!f)
	{
		return false;
	}

	// Read vertex and face count
	fread(&this->vertices, 1, sizeof(this->vertices), f);
	fread(&this->faces, 1, sizeof(this->faces), f);

	
	if(!initVertices(this->vertices)) return false;
	if(!initFaces(this->faces)) return false;

	// Read in all vertex data
	for(i = 0; i < this->vertices; i++)
	{
		float pos[3], norm[3], u, v;

		fread(&pos, 3, sizeof(float), f);
		fread(&norm, 3, sizeof(float), f);
		fread(&u, 1, sizeof(float), f);
		fread(&v, 1, sizeof(float), f);

		vertex[i].position.x = pos[0];
		vertex[i].position.y = pos[1];
		vertex[i].position.z = pos[2];
		vertex[i].normal.x = norm[0];
		vertex[i].normal.y = norm[1];
		vertex[i].normal.z = norm[2];
		vertex[i].u = u;
		vertex[i].v = v;
	}

	// Read in all face data
	for(i = 0; i < this->faces; i++)
	{
		float norm[3];
		int a, b, c;
		
		fread(&norm, 3, sizeof(float), f);
		fread(&a, 1, sizeof(int), f);
		fread(&b, 1, sizeof(int), f);
		fread(&c, 1, sizeof(int), f);

		face[i].normal.x = norm[0];
		face[i].normal.y = norm[1];
		face[i].normal.z = norm[2];
		face[i].a = a;
		face[i].b = b;
		face[i].c = c;
	}

	fclose(f);


	return true;
}

bool T3D::loadFromMemory(unsigned char *fileData, unsigned int fileSize)
{
	unsigned int i, offset = 0;
	
	// Read vertex and face count	
	memcpy(&this->vertices, fileData + offset, sizeof(this->vertices));
	offset += sizeof(this->vertices);

	memcpy(&this->faces, fileData + offset, sizeof(this->faces));
	offset += sizeof(this->faces);

	
	if(!initVertices(this->vertices)) return false;
	if(!initFaces(this->faces)) return false;

	// Read in all vertex data
	for(i = 0; i < this->vertices; i++)
	{
		float pos[3], norm[3], u, v;
		
		memcpy(&pos, fileData + offset, sizeof(float)*3);
		offset += sizeof(float)*3;

		memcpy(&norm, fileData + offset, sizeof(float)*3);
		offset += sizeof(float)*3;

		memcpy(&u, fileData + offset, sizeof(float));
		offset += sizeof(float);

		memcpy(&v, fileData + offset, sizeof(float));
		offset += sizeof(float);

		vertex[i].position.x = pos[0];
		vertex[i].position.y = pos[1];
		vertex[i].position.z = pos[2];
		vertex[i].normal.x = norm[0];
		vertex[i].normal.y = norm[1];
		vertex[i].normal.z = norm[2];
		vertex[i].u = u;
		vertex[i].v = v;
	}

	// Read in all face data
	for(i = 0; i < this->faces; i++)
	{
		float norm[3];
		int a, b, c;
				
		memcpy(&norm, fileData + offset, sizeof(float)*3);
		offset += sizeof(float)*3;

		memcpy(&a, fileData + offset, sizeof(int));
		offset += sizeof(int);

		memcpy(&b, fileData + offset, sizeof(int));
		offset += sizeof(int);

		memcpy(&c, fileData + offset, sizeof(int));
		offset += sizeof(int);

		face[i].normal.x = norm[0];
		face[i].normal.y = norm[1];
		face[i].normal.z = norm[2];
		face[i].a = a;
		face[i].b = b;
		face[i].c = c;
	}

	return true;
}

bool T3D::initVertices(unsigned int count)
{
	vertex = new T3DVertex[count];
	if(!vertex)
	{
		return false;
	}

	return true;
}

bool T3D::initFaces(unsigned int count)
{
	face = new T3DFace[count];
	if(!face)
	{
		return false;
	}

	return true;
}

void T3D::debug()
{
	unsigned int i;
	char buf[256];

	sprintf(buf,"\n----------\n");
	dmsMsg("%s", buf);
	sprintf(buf,"T3D DEBUG:\n");
	dmsMsg("%s", buf);
	sprintf(buf,"----------\n");
	dmsMsg("%s", buf);
	sprintf(buf,"Vertex count: %d\n", vertices);
	dmsMsg("%s", buf);
	sprintf(buf,"Face count: %d\n\n", faces);
	dmsMsg("%s", buf);

	for(i = 0; i < this->vertices; i++)
	{
		Vector3 p = vertex[i].position;
		Vector3 n = vertex[i].normal;
		float u = vertex[i].u;
		float v = vertex[i].v;

		sprintf(buf,"Vertex: %d, POS: (%f, %f %f) NOR: (%f, %f %f) U: %f V: %f\n", i, p.x, p.y, p.z, n.x, n.y, n.z, u, v);
		dmsMsg("%s", buf);
	}

	for(i = 0; i < this->faces; i++)
	{		
		Vector3 n = face[i].normal;
		int a = face[i].a;
		int b = face[i].b;
		int c = face[i].c;
		
		sprintf(buf,"Face: %d, NOR: (%f, %f %f) A: %d B: %d C: %d\n", i, n.x, n.y, n.z, a, b, c);
		dmsMsg("%s", buf);
	}

}

T3DVertex *T3D::getVertexArray()
{
	return vertex;
}

T3DFace *T3D::getFaceArray()
{
	return face;
}

unsigned int T3D::getVertexCount()
{
	return this->vertices;
}

unsigned int T3D::getFaceCount()
{
	return this->faces;
}


//------------------------------------------
// T3DFace
//------------------------------------------

bool T3DFace::isNeighbour(int a1, int b1, int c1) 
{
	// naapureita jos löytyy kaksi yhteistä vertexiä

	int vert[3] = { a, b, c };
	
	int i, found=0;
	for(i=0; i<3; i++) 
	{
		if(vert[i] == a1) found++;
		if(vert[i] == b1) found++;
		if(vert[i] == c1) found++;
	}

	if(found==2)  
		return true;
	else 
		return false;
}


// EDGE FINDER SOURCES
// two versions

/*

bool T3D::initEdges(unsigned int count)
{

	// Tämä menetelmä löytää kaikki edget, mutta ei 
	// sorttaa niitä
/*	  
	int i, a, b;

	count = this->faces * 3;

	int edgecount = -1;
	T3DEdge *tmpedge = new T3DEdge[count];
	if(!tmpedge) return false;

	T3DFace *facelist = this->face;	
	T3DFace *f1, *f2;

   
   
   for (a=0; unsigned(a)<faces; a++)
   {
 	  f1 = &face[a];

		for(b=1; unsigned(b)<faces; b++) 
		{

			// face a == face b 
			if(a==b) 
				continue;

			 f2 = &face[b];

			 if(f1->isNeighbour(f2->a, f2->b, f2->c)==true)
			 {

				 bool is_old_edge = false;

				 // onko jo lisätty
				 for(i=0; i<edgecount+1; i++) 
				 {
					if((tmpedge[i].face1 == a && tmpedge[i].face2 == b) || 
					   (tmpedge[i].face1 == b && tmpedge[i].face2 == a)) 
					{					
						is_old_edge = true;
						break;
					}
				 }

			
				if(is_old_edge==false) 
				{

					// etsitään yhteiset edget

					int vert[3] = { f1->a, f1->b, f1->c };
					int indx[2] = { -1, -1 };
					int m=0;

					for(i=0; i<3; i++) 
					{
						if(vert[i] == f2->a)
						{
							indx[m] = f2->a;
							m++;
						}

						if(vert[i] == f2->b)
						{
							indx[m] = f2->b;
							m++;
						}

						if(vert[i] == f2->c)
						{
							indx[m] = f2->c;
							m++;
						}

						if(m==2) 
							break;
					}

					edgecount++;
					tmpedge[edgecount].a = indx[0];
					tmpedge[edgecount].b = indx[1];
					tmpedge[edgecount].face1 = a;
					tmpedge[edgecount].face2 = b;
				}

			 } // endif

		} // end for

   }


    this->edges = edgecount;

	// copy tmpedge to this->edge
	this->edge = new T3DEdge[edgecount];
	if(!this->edge)
	{
		return false;
	}

	for(a=0; a<edgecount; a++) {
		this->edge[a] = tmpedge[a];
	}

	delete [] tmpedge;

	return true;

/**/
/*

	// ei löydä vastinpareja kaikille edgeille	
	unsigned long a;

    // Allocate enough space to hold all edges
   T3DEdge *edgeArray;
   edgeArray = new T3DEdge[this->faces*3];

   long edgeCount = 0;

   // First pass: find edges
   for (a=0; a<faces; a++)
   {
      long i1 = face[a].a;
      long i2 = face[a].b;
      long i3 = face[a].c;

      if (i1 < i2)
      {
         edgeArray[edgeCount].a = i1;
         edgeArray[edgeCount].b = i2;
         edgeArray[edgeCount].face1 = a;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }

      if (i2 < i3)
      {
         edgeArray[edgeCount].a = i2;
         edgeArray[edgeCount].b = i3;
         edgeArray[edgeCount].face1 = a;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }

      if (i3 < i1)
      {
         edgeArray[edgeCount].a = i3;
         edgeArray[edgeCount].b = i1;
         edgeArray[edgeCount].face1 = a;
         edgeArray[edgeCount].face2 = -1;
         edgeCount++;
      }
   }

   // Second pass: match triangles to edges
   //triangle = this->face;
   for (a = 0; a<this->faces; a++)
   {
      long i1 = face[a].a;
      long i2 = face[a].b;
      long i3 = face[a].c;

      if (i1 > i2)
      {
         //edgelist = edgeArray;
         for (long b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i2) &&
				(edgeArray[b].b == i1) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = a;
               break;
            }
         }
      }

      if (i2 > i3)
      {
         //edgelist = edgeArray;
         for (long b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i3) &&
				(edgeArray[b].b == i2) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = a;
               break;
            }
         }
      }

      if (i3 > i1)
      {
         //edgelist = edgeArray;
         for (long b=0; b<edgeCount; b++)
         {
            if ((edgeArray[b].a == i1) &&
				(edgeArray[b].b == i3) &&
				(edgeArray[b].face2 == -1))
            {
               edgeArray[b].face2 = a;
               break;
            }
         }
      }

//      triangle++;
   }

    this->edges = edgeCount;

	// copy tmpedge to this->edge
	this->edge = new T3DEdge[edgeCount];
	if(!this->edge)
	{
		return false;
	}

	for(a=0; a<unsigned(edgeCount); a++) {
		this->edge[a] = edgeArray[a];
	}

	delete [] edgeArray;



	return true;
}
*/