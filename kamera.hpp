#ifndef _KAMERA_HPP_
#define _KAMERA_HPP_

#include "externs.hpp"
#include "DemoTractor/vector.hpp"

class Kamera  
{
public:
	Kamera();
	virtual ~Kamera();

	// Apply the current camera view (call glulookat)
	void apply();
	// Apply the current camera view - subtract dpos and dtarget from values
	void apply(Vector dpos, Vector dtarget);

	Vector pos;
	Vector target;
	Vector normal;


};

#endif 
