#ifndef _Starfield_HPP_
#define _Starfield_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Star
{
public:

    Vector3 start;
    Vector3 end;
    Vector3 color;

    float phase;
    float length;
    float fade;


};

class Starfield : public Base
{
	public:

		Starfield();
		~Starfield();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int count;
        Star *stars;


		void renderScene(float pos, float alpha);
};

#endif
