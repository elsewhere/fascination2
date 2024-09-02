#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Pikkuspiraalit.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Pikkuspiraalit::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.1f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

    filter.init(true);
	renderScene(pos, alpha);
     filter.glow(8, 0.005f, 0.005f, 0.92f, -1.0f, 1.0f);
}

void Pikkuspiraalit::renderScene(float pos, float alpha)
{
    int i = 0;
	cam->useCamera(0);
	
	this->timer->update();
	while (this->timer->stepsLeft())
	{
        for (i = 0; i < this->count; i++)
        {
            pikut[i]->update();
        }
		this->timer->endStep();
	}

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(3.0f);

    glPushMatrix();
//    glRotatef(pos*600, 0.4f- cosf(pos*11), 0.2f + pos*0.7f, 0.7f + 0.3f*cosf(pos*17));
    for (i = 0; i < this->count; i++)
    {
        this->pikut[i]->draw(pos, alpha);
    }
    glPopMatrix();

    glDisable(GL_LINE_SMOOTH);
}

void Pikku::draw(float pos, float alpha)
{
    float e = this->energy / this->startenergy;
    float a = sinf(e * 3.141592f) * alpha * this->fade;
    glColor4f(this->color.x, this->color.y, this->color.z, a);

    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);

    float t = 1 - e;

    if (this->cube)
    {
        Primitives::wireCube(t * 0.07f);
    }
    else
    {

        glBegin(GL_LINE_STRIP);
        for (float u = 0.0f; u < t; u += 0.03f)
        {
            float a = this->a1 + (this->a2 - this->a1) * u;
            float b = this->b1 + (this->b2 - this->b1) * u;
            float r = this->r1 + (this->r2 - this->r1) * u;

            Vector3 v = Mathematics::sphereToCartesian(r, b, a);
            glVertex3fv((float *)&v);


        }
        glEnd();
    }

    glPopMatrix();
}

void Pikku::update()
{
    this->pos += this->speed;
    this->energy -= this->de;
    if (this->energy < 0.00f)
    {
        this->init();
    }

}

void Pikku::init()
{
    this->fade = Mathematics::randBetween(0.50f, 0.95f);
    this->energy = Mathematics::randBetween(0.5f, 0.9f);
    this->startenergy = this->energy;
    this->de = Mathematics::randBetween(0.01f, 0.02f);
    this->color = getKasariColor();

    this->a1 = Mathematics::randBetween(0, 2*3.141592f);
    this->b1 = Mathematics::randBetween(0, 2*3.141592f);

    const float kierous = 5.0f;

    this->a2 = this->a1 + Mathematics::randBetween(0.3f, 1.7f) * kierous;
    this->b2 = this->b1 + Mathematics::randBetween(0.3f, 1.7f) * 0.5f * kierous;

    this->r1 = Mathematics::randBetween(0.04f, 0.07f);
    this->r2 = this->r1 + Mathematics::randBetween(0.04f, 0.4f);

    this->pos = Mathematics::randVectSphere() * powf(Mathematics::randFloat(), 0.5f) * 4;
    this->speed = this->pos;
    this->speed.y *= 6;
    this->speed.normalize();
    this->speed  *= 0.04f;
    this->speed += Vector3(0, 0.04f, 0);

    this->cube = false;//(rand()%2) == 1;
}

Pikku::Pikku()
{
    this->init();
}

Pikku::~Pikku()
{
}





Pikkuspiraalit::Pikkuspiraalit()
{	
    int i = 0;
	this->timer = new FrameTimer(1000 / 60, 20);
    this->count = 1000;

    this->pikut = new Pikku*[this->count];

    for (i = 0; i < this->count; i++)
    {
        this->pikut[i] = new Pikku();
    }
}

Pikkuspiraalit::~Pikkuspiraalit()
{
    int i = 0;
    for (i = 0; i < this->count; i++)
    {
        delete this->pikut[i];
    }
    delete [] this->pikut;

	delete this->timer;
}


bool Pikkuspiraalit::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

