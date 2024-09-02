#ifndef _Sauhu_HPP_
#define _Sauhu_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class SauhuValo
{
public:

    void init();
    void update(float sync);

    Vector3 pos;
    Vector3 color;
    Vector3 speed;
    
    float basepower;
    float power;


};

class SauhuParticle
{
public:

    void init();
    void update(SauhuValo *valot, int amount);

    Vector3 pos;
    Vector3 speed;
    Vector3 color;
    float size;
    float energy;
    float energy_at_start;
    float fade;

};

class Sauhu : public Base
{
	public:

		Sauhu();
		~Sauhu();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:

        int valocount;
        SauhuValo *valot;

        void renderSauhut(SauhuParticle *src, int amount, float alpha);
        int count;

        SauhuParticle *particles1;
        SauhuParticle *particles2;
        SauhuParticle *particles3;
        SauhuParticle *particles4;
		FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
