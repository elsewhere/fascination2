#ifndef _Nauhat_HPP_
#define _Nauhat_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"


class PolyStrip
{
public:
    PolyStrip() {}; 
    PolyStrip(CatmullRom *src, CatmullRom *displacement, CatmullRom *translation, Vector3 &color, float fade);
    ~PolyStrip();

    void update();
    void draw(float pos, float alpha);

    int count;
    Vector3 *colors;
    Vector3 *vertices;

    float fade;
    Vector3 color;
};

class Nauha
{
public:

    Nauha();
    ~Nauha();
    void update();
    void draw(float pos, float alpha);

    int count;
    PolyStrip **strips;

    float st, et;

};



class Nauhat : public Base
{
	public:

		Nauhat();
		~Nauhat();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        int count;

        Nauha **nauhat;

		FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
