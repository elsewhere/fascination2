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
			Vertex(Vector3 vec);
			Vertex(float x, float y, float z);

			~Vertex();

			Vector3 getPosition();
			Vector3 getOldPosition();
			Vector3 getNormal();
			float getU() { return u; }
			float getV() { return v; }
			
			void setPosition(Vector3 vec);
			void setNormal(Vector3 vec);
			void setUV(float uu, float vv);		
			float u, v;	

		private:

			Vector3 position, old;
			Vector3 normal;		
	};
}

#endif