#ifndef _Noise1_HPP_
#define _Noise1_HPP_

#include <stdio.h>
#include "../externs.hpp"

class Noise1 : public Base
{
	public:

        Noise1(){}
		Noise1(float startfade, float endfade, float fade);
		~Noise1();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        float startfade, endfade;
        float fade;
		void renderScene(float pos, float alpha);

};

#endif
