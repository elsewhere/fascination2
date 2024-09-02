#ifndef _Sade_HPP_
#define _Sade_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Sade : public Base
{
	public:

        Sade() {};
        Sade(int camera);
		~Sade();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int camref;
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
