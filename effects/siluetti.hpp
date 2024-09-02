#ifndef _Siluetti_HPP_
#define _Siluetti_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Siluetti : public Base
{
	public:

		Siluetti();
		~Siluetti();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        TMesh *mesh;
		void renderScene(float pos, float alpha);
};

#endif
