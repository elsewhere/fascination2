#ifndef _Loppu_HPP_
#define _Loppu_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Loppu : public Base
{
	public:

		Loppu();
		~Loppu();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
