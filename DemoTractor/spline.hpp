#ifndef _SPLINE_HPP_
#define _SPLINE_HPP_

#pragma warning(disable: 4251)

//-------------------------------------------------------
//	Headers
//-------------------------------------------------------

#include "Vector.hpp"
#include "list.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//-------------------------------------------------------
//	SplineKey-luokka
//-------------------------------------------------------

	class __declspec(dllexport) SplineKey
	{
		public:
			SplineKey () {};
			~SplineKey() {};

			float bias;
			float continuity;
			float tension;
			unsigned int frame;
			Vector3 v;
	};

//-------------------------------------------------------
//	SplineSystem-luokka
//-------------------------------------------------------

	class __declspec(dllexport) SplineSystem
	{
		public:

			SplineSystem();
			~SplineSystem();

			void addKey( unsigned int frame, Vector3 v, float b, float c, float t );
			void update( unsigned int frame );
			void updateKey( unsigned int i, Vector3 v );
			Vector3 getValue( float position );
			SplineKey *getKey( unsigned int i );

		private:

			Vector3 calculateHermiteTangent( Node <SplineKey> *key, int sel );

			float t;
			List < SplineKey > keys;
			Node < SplineKey > *currentKey;
	};

}

#endif