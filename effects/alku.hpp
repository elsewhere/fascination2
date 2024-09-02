#ifndef _Alku_HPP_
#define _Alku_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Alku : public Base
{
	public:

		Alku();
		~Alku();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
