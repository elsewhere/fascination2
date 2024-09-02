#ifndef _Kierre_HPP_
#define _Kierre_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Kierre : public Base
{
	public:

		Kierre();
		~Kierre();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
		FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
