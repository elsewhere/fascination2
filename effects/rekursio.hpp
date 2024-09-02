#ifndef _Rekursio_HPP_
#define _Rekursio_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Rekursio : public Base
{
	public:

		Rekursio();
		~Rekursio();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
		void renderScene(float pos, float alpha);
};

#endif
