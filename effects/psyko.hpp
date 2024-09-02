#ifndef _Psyko_HPP_
#define _Psyko_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class Tahti
{
public:
    bool active;
    float size;
    Vector3 position;
    Vector3 direction;

    Vector3 color;
    void init();
    float energy;
    float maxenergy;
    float fade;

};


class Psyko : public Base
{
	public:

		Psyko();
		~Psyko();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int vcount;
        Vector *leftedge;
        Vector *rightedge;
        int count;
        CatmullRom *coords;
		
        int tahticount;
        int tahtiindex;
        Tahti *tahdet;

        FrameTimer *timer;
        void renderScene(float pos, float alpha);
};

#endif
