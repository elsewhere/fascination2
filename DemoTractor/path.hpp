#ifndef _PATH_HPP_
#define _PATH_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "vector.hpp"
#include "lista.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Spline class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Spline
	{
	public:
		Spline();
		~Spline();
		
		void destroy();
		void addpoint(Vector3 &point);

		void draw();
		Vector3 getValue(float t);
		Vector3 getDerivative(float t);

	private:
		
		int count;
		Lista *points;

	};

}

#endif
