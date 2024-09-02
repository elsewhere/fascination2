#ifndef _Kareet_HPP_
#define _Kareet_HPP_

#include <stdio.h>
#include "../externs.hpp"
#include "../bpm.hpp"
#include "kareet.hpp"

class Kare
{
public:
    Kare();
    ~Kare();

    void update(float pos);
    void draw(float pos, float alpha);
    void init(class KarePisara &p);

    static Vector3 aalto(float pos, Vector3 &center);

    Vector3 color;
    Vector3 center;

    Vector3 centerdelta;
    Matrix rotationmatrix;

    bool active;
    float fade;
    float r;
    float d;
};

class KarePisara
{
public:
    KarePisara();
    ~KarePisara();
    void init();
    bool update();
    void draw(float pos, float alpha);


    bool special;
    Vector3 position;
    Vector3 color;

    float fade;
    float length;
    Vector3 speed;
};

class KareParticle
{
public:
    KareParticle() {};
    ~KareParticle() {};

    void set(KarePisara &p);

    void update();
    Vector3 position;
    Vector3 speed;
    Vector3 color;
    float velocity;
    float maxlife;
    float life;

    float fade;

    bool active;

};

class Saippua
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

class Kareet : public Base
{
	public:

		Kareet();
		~Kareet();

		bool init(unsigned long s, unsigned long e);
		void draw();

	private:
        void initKare(KarePisara *pisara);

        int kareoffset;
        int karecount;
        int pisaracount;
        FrameTimer *timer;
        Kare **kareet;
        KarePisara **pisarat;

        int particlecount;
        int particleindex;
        KareParticle **particlet;

        int saippuacount;
        int saippuaindex;
        Saippua *saippuat;

		void renderScene(float pos, float alpha);
};

#endif
