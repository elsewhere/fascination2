#ifndef _Pikkuspiraalit_HPP_
#define _Pikkuspiraalit_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Pikku
{
public:

    Pikku();
    ~Pikku();
    void draw(float pos, float alpha);
    void update();
    void init();

    float energy, startenergy, de;
    Vector3 color;
    Vector3 pos;
    Vector3 speed;
    float fade;

    bool cube;


    float a1, a2;
    float b1, b2;
    float r1, r2;

};
class Pikkuspiraalit : public Base
{
	public:

		Pikkuspiraalit();
		~Pikkuspiraalit();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int count;
        Pikku **pikut;
		FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
