#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "vector.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Vertex class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Vertex
	{
		public:

		// Object, Face ja Loader3DS ovat ystäviä ja saavat kopeloida meitä
		friend class Face;	
		friend class Object;
		friend class Scene;
		friend class Loader3DS;	

			Vertex();
			Vertex(Vector vec);
			Vertex(float x, float y, float z);

			~Vertex();

			Vector getPosition();
			Vector getOldPosition();
			Vector getNormal();
			float getU() { return u; }
			float getV() { return v; }
			
			void setPosition(Vector vec);
			void setNormal(Vector vec);
			void setUV(float uu, float vv);		
			float u, v;	

		private:

			Vector position, old;
			Vector normal;		
	};
}

#endif