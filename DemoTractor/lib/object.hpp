#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "vector.hpp"
#include "vertex.hpp"
#include "face.hpp"
#include "matrix.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Object class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Object
	{	
		public:
			
		// Scene ja Loader3DS ovat ystäviä ja saavat kopeloida meitä
		friend class Vertex;
		friend class Scene;
		friend class Loader3DS;

			Object();
			~Object();

			bool initVertices(unsigned int i);
			bool initFaces(unsigned int i);
			void render();
			void render(float u, float v);
			void renderCel(Vector lightPos, unsigned int id);
			void release();

			bool calculateNormals();
			bool calculateVertexNormals();		
			void reduceToUnit();

			void debug();		

			// Getters
			unsigned int getVertices();
			unsigned int getFaces();
			Vertex &copyVertexArray();
			Vertex *getVertexPointer();
			Face *getFacePointer();

			// Setters
			bool setVertex(unsigned int i, Vertex v);
			bool setFace(unsigned int i, Face f);
			void setPosition(Vector v);

		private:		

			unsigned int nFaces, nVertices;
			Vector position;

			Vertex *vertex;
			Face *face;

			Matrix matrix;
	};
}

#endif