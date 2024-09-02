#ifndef _Runko_HPP_
#define _Runko_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Runko : public Base
{
	public:

		Runko();
		~Runko();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
