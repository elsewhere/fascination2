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

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	//--------------------------------------------------------------------------------------------
	//  Traction 3D object vertex class
	//--------------------------------------------------------------------------------------------

	class T3DVertex
	{
		public:

			Vector position;
			Vector normal;
			float u ,v;
	};

	//--------------------------------------------------------------------------------------------
	//  Traction 3D object face class
	//--------------------------------------------------------------------------------------------

	class T3DFace
	{
		public:

			// Face normal
			Vector normal;
			int a, b, c;
	};

	//--------------------------------------------------------------------------------------------
	//  T3D - Traction 3D object class
	//--------------------------------------------------------------------------------------------

	class T3D
	{	
		public:

			T3D();
			~T3D();

			bool load(char *name);
			bool initVertices(unsigned int count);
			bool initFaces(unsigned int count);
			
			void debug();

			T3DVertex *getVertexArray();
			T3DFace *getFaceArray();
			unsigned int getVertexCount();
			unsigned int getFaceCount();

		private:

			T3DVertex *vertex;
			T3DFace *face;
			Matrix matrix;

			unsigned int vertices;
			unsigned int faces;		
	};
}

#endif