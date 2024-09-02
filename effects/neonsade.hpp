#ifndef _Neonsade_HPP_
#define _Neonsade_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"

const int PISARA_STATE_NONE = 0;
const int PISARA_STATE_FALL = 1;
const int PISARA_STATE_BOUNCE = 2;
const int PISARA_STATE_DID_NOT_HIT = 3;
const int PISARA_STATE_FLY = 4;

class Neonpisara
{
public:

    Neonpisara();
    ~Neonpisara();

    int count;

    void init();
    void update(float area);
    void draw(float pos, float alpha);

    Vector3 *positions;
    Vector3 *speeds;
    Vector3 color;

    Vector3 dir;
    int state;
    int updatesFromStart;
    int updatesLeft;
    int pointsHit;

    float fade;

};

class Reunus
{
public:
    Reunus();
    void draw(float pos, float alpha);
    void drawOutline(float pos, float alpha);

    int count;
    Vector3 color;
    float fade;
    float st, et;
    Vector3 *vertices;


};


class Neonsade : public Base
{
	public:

		Neonsade();
		~Neonsade();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:

        int reunuscount;
        Reunus **reunukset;

        float area; 
        int count;
        Neonpisara **pisarat;
        FrameTimer *timer;
		void renderScene(float pos, float alpha);
};

#endif
