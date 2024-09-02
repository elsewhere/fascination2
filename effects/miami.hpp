#ifndef _Miami_HPP_
#define _Miami_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

class LandSegment
{
public:
    LandSegment() {};
    LandSegment(int which, int count, float segmentwidth, float segmentlength);
    void setNumber(int number);
    void set(int which, float segmentwidth, float segmentlength);
    void setHeights(float *ptr);

    Vector3 *vertices;
    Vector3 *uv;
    Vector3 *colors;
    int piececount;

    Vector3 keilacolor;
    Vector3 tiecolor;
    float fog;
    int number;
};

class Miami : public Base
{
	public:

		Miami();
		~Miami();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        void shiftLandscape();
        void drawHorizon(float pos, float alpha);
        void drawLandscape(float pos, float alpha);
        void drawKeila(float dist, float z, Vector3 &color, float alpha);
        void drawTienPala(float x, float z, float syvyys, float leveys);
        float cameramovement;

        float segmentlength;
        float segmentwidth;
        int segmentcount;
        int piececount;
        LandSegment **segments;

        int shifts;

        float *soundbuffer;
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
