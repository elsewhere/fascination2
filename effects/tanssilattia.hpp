#ifndef _Tanssilattia_HPP_
#define _Tanssilattia_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"


class Lattianpala
{
public:
    void update();
    void init(float pos);
    void draw(float pos, float alpha);

    Vector3 v1, v2, v3, v4;
    Vector3 color;

    float st1, et1;
    float st2, et2;

    float basefade;
    float fade;

    bool special;

};

class LattiaParticle
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


class Tanssilattia : public Base
{
	public:

		Tanssilattia();
		~Tanssilattia();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:

        Cubemap *cubemap;
        TMesh *mesh;
        FrameTimer *timer;

        void reinit(float pos);
        int xres, yres;
        int count;

        Lattianpala **palat;

        int particlecount;
        LattiaParticle *particles;
        void renderGeometry(float pos, float alpha);
		void renderScene(float pos, float alpha);
};

#endif
