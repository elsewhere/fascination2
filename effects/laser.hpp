#ifndef _Laser_HPP_
#define _Laser_HPP_

#include <stdio.h>
#include <vector>
#include "../externs.hpp"
#include "../bpm.hpp"

using namespace std;

class Emitter
{
    public:
        Emitter();
        ~Emitter();
        void update(float pos, int reflectorcount, class Reflector **reflectors);
        void draw(float pos, float alpha);

        class Beam **getBeams();
        int getBeamCount();

    private:

        Vector3 pos;
        Vector3 color;

        int beamcount;
        Beam **beams;
        
};

class Reflector
{
    public:
        Reflector();
        ~Reflector();
        void update(float pos);
        void draw(float pos, float alpha);

        float fade;
        bool hit;
        Vector3 hitcolor;

        Vector3 realposition;
        Vector3 position;
        Vector3 v1, v2, v3;
        Vector3 realv1, realv2, realv3;
        Vector3 rotangle;
        Vector3 rotspeed;
        Vector3 normal;
        Vector3 basenormal;

        Vector3 edge1, edge2;

        float boundingradiussquared;

        

};

class Beam
{
    public:
        Beam(Vector3 &color, float a, float b, float da, float db);
        ~Beam();

        void update(Vector3 &startpos, float pos, int reflectorcount, Reflector **reflectors);
        void draw(float pos, float alpha);
        void debug();
    private:
        void trace(int reflectorcount, Reflector **reflectors);
        float intersect(Vector3 &point, Vector3 &dir, Reflector *reflector);

        int iteration;
        int lastIndex;

        Vector3 color;
        int maxlength;
        Vector3 *coords;
        float fade;
        float realfade;
        float fadephase;

        float a, b; //suunta pallokoordinaatistossa

        float da, db;
        Vector3 dir;
};

class Laser : public Base
{
	public:

		Laser();
		~Laser();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:

        Cubemap *cubemap;

        int emittercount;
        Emitter **emitters;

        int reflectorcount;
        Reflector **reflectors;

        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
