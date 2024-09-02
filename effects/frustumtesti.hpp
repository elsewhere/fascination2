#ifndef _FrustumTesti_HPP_
#define _FrustumTesti_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"


class TestiPallo
{
public:

    float r;
    Vector3 pos;


};

class FrustumTesti : public Base
{
	public:

		FrustumTesti();
		~FrustumTesti();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int count;
        TestiPallo *pallot;
        TMesh *pallomesh;

        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
