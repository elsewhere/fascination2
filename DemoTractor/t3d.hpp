//--------------------------------------------------------------------------------------------
//  Notes!
//
//  T3D is a simple 3D-object format. It was made for one purpose only:
//  To present a single object in 3D and to contain all necessary 
//	information to do so.
//
//  T3D objects are in object space which means that any conversion to 
//	this format must take care of adjusting necessary coordinates
//
//--------------------------------------------------------------------------------------------

#ifndef _T3D_HPP_
#define _T3D_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

// Use our own vector/matrix routines
#include "vector.hpp"
#include "matrix.hpp"
#include "lista.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	//--------------------------------------------------------------------------------------------
	//  Traction 3D object vertex class
	//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) T3DVertex
	{
		public:

			Vector3 position;
			Vector3 normal;
			float u ,v;
	};

	//--------------------------------------------------------------------------------------------
	//  Traction 3D object face class
	//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) T3DFace
	{
		public:

			// Face normal
			Vector3 normal;
			int a, b, c;

			bool isNeighbour(int a1, int b1, int c1);
	};

	//--------------------------------------------------------------------------------------------
	//  T3D - Traction 3D edge class
	//--------------------------------------------------------------------------------------------
/*
	class __declspec(dllexport) T3DEdge
	{
		public:
			
			int face1, face2;
			int a, b;
	};
*/

	//--------------------------------------------------------------------------------------------
	//  T3D - Traction 3D object class
	//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) T3D
	{	
		public:

			T3D();
			~T3D();

			bool load(char *name);
			bool loadFromMemory(unsigned char *fileData, unsigned int fileSize);
			bool initVertices(unsigned int count);
			bool initFaces(unsigned int count);
			void debug();

			T3DVertex *getVertexArray();
			T3DFace *getFaceArray();
			unsigned int getVertexCount();
			unsigned int getFaceCount();

		protected:

			T3DVertex *vertex;
			T3DFace *face;
			Matrix matrix;

			unsigned int vertices;
			unsigned int faces;		
					
	};
}

#endif