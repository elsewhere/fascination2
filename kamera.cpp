#include "Kamera.hpp"


Kamera::Kamera()
{
	pos =  Vector(0,0,0);
	target = Vector(0,0,-50);
	normal = Vector(0,1,0);
}

Kamera::~Kamera()
{
}

void Kamera::apply() {

	gluLookAt( pos.x, pos.y, pos.z,
			   target.x, target.y, target.z,
			   normal.x, normal.y, normal.z);
}

void Kamera::apply(Vector dpos, Vector dtarget) {

	Vector from, to;

	from = pos-dpos;
	to = target-dtarget;

	gluLookAt( from.x, from.y, from.z,
			 to.x, to.y, to.z,
			normal.x, normal.y, normal.z);
	
}
