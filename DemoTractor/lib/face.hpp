#ifndef _FACE_HPP_
#define _FACE_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "vector.hpp"
#include "vertex.hpp"
#include "texture.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Face class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Face
	{
		public:

		// Object ja Loader3DS ovat ystäviä ja saavat kopeloida meitä	
		friend class Object;
		friend class Scene;
		friend class Loader3DS;

			Face();
			~Face();

			bool setVertex(Vertex *v1, Vertex *v2, Vertex *v3);
			bool setTexture(char *name);
			bool calculateNormal();

			void debug();
			Vertex *a, *b, *c;
			Vector normal;
			Texture *texture;

		private:

			int aa, bb, cc;

			char textureName[80];
	};
}

#endif