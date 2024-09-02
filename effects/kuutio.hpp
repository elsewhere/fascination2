#ifndef _Kuutio_HPP_
#define _Kuutio_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"


class Kuutionosa
{
public:
    void update();
    void init();
    void draw(float pos, float alpha);

    Vector3 v1, v2, v3, v4;
    Vector3 v5, v6, v7, v8;
    Vector3 color;
    Vector3 suunta;
    float t;
    float dt;

    float fade;


    BoundingSphere bs;
};

class Greet
{
public:
    void init();
    Vector3 point;
    int orientation;

    int textIndex;
    Vector3 color;
    float fade;

    void draw(float pos, float alpha, float scale);


};

class Kuutio : public Base
{
	public:

		Kuutio();
		~Kuutio();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:


        void renderGeometry(float pos, float alpha, float sync);

        FrameTimer *timer;

        void reinit();
        int xres, yres;
        int count;
        int greetcount;

        TMesh *mesh;
        Kuutionosa **osat;
        Cubemap *cubemap;
        Greet *greets;
		void renderScene(float pos, float alpha);
};

#endif
