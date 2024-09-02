#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Sauhu.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Sauhu::draw()
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
/*
    filter.init();
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    dmsPerspective2D(1,1);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor4f(1,1,1,alpha*0.2f);

    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("neonrain.jpg")->getID());

    glPushMatrix();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(0, 0);
    glTexCoord2f(1, 1);
    glVertex2f(1, 0);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(0, 1);

    glEnd();

    glPopMatrix();

    dmsPerspective3D();
    glLoadIdentity();
    glDepthMask(1);

    filter.blur(5, 0.01f, 0.01f);
*/
//    filter.init();
	renderScene(pos, alpha);
//    filter.blur(3, 0.003f, 0.003f);
}

void Sauhu::renderScene(float pos, float alpha)
{
    int i = 0;
	cam->useCamera(2);
	
    float sync = beat4->getValue();
    if (beat4->getChanged())
    {
        for (i = 0; i < this->valocount; i++)
        {
//            this->valot[i].init();//update(sync);
        }
    }

	this->timer->update();
	while (this->timer->stepsLeft())
	{
        for (i = 0; i < this->count; i++)
        {
            this->particles1[i].update(this->valot, this->valocount);
            this->particles2[i].update(this->valot, this->valocount);
            this->particles3[i].update(this->valot, this->valocount);
            this->particles4[i].update(this->valot, this->valocount);
        }

        for (i = 0; i < this->valocount; i++)
        {
            this->valot[i].update(sync);
        }
		this->timer->endStep();
	}

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("smoke1.jpg")->getID());
    renderSauhut(this->particles1, this->count, alpha);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("smoke2.jpg")->getID());
    renderSauhut(this->particles2, this->count, alpha);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("smoke3.jpg")->getID());
    renderSauhut(this->particles3, this->count, alpha);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("smoke4.jpg")->getID());
    renderSauhut(this->particles4, this->count, alpha);
}

void Sauhu::renderSauhut(SauhuParticle *src, int amount, float alpha)
{
    int i = 0;

    TTexCoord uv1 = TTexCoord(0, 0);
    TTexCoord uv2 = TTexCoord(1, 0);
    TTexCoord uv3 = TTexCoord(1, 1);
    TTexCoord uv4 = TTexCoord(0, 1);

    Vector3 x, y, z;
    Mathematics::antiRotate(&x, &y, &z);

    glBegin(GL_QUADS);

    for (i = 0; i < amount; i++)
    {
        float s = src[i].size;

        float colorval = src[i].color.x + src[i].color.y + src[i].color.z;
        if (colorval < 0.03f)
            continue;



        Vector3 p1 = src[i].pos - x * s - y * s;
        Vector3 p2 = src[i].pos + x * s - y * s;
        Vector3 p3 = src[i].pos + x * s + y * s;
        Vector3 p4 = src[i].pos - x * s + y * s;

        glColor4f(src[i].color.x, src[i].color.y, src[i].color.z, 
          sinf((src[i].energy / src[i].energy_at_start)* 3.141592f) * alpha * src[i].fade);

        glTexCoord2fv((float *)&uv1);
        glVertex3fv((float *)&p1);
        glTexCoord2fv((float *)&uv2);
        glVertex3fv((float *)&p2);
        glTexCoord2fv((float *)&uv3);
        glVertex3fv((float *)&p3);
        glTexCoord2fv((float *)&uv4);
        glVertex3fv((float *)&p4);
    }
    glEnd();

}

void SauhuParticle::update(SauhuValo *valot, int amount)
{
    int i = 0;
    this->pos += this->speed;
    this->energy -= 0.001f;
    if (this->energy < 0.0f)
    {
        this->init();
    }

    const float base = 0.01f;//0.1f;//5f;
    this->color = Vector3(base, base, base);

    for (i = 0; i < amount; i++)
    {
        float dx = valot[i].pos.x - this->pos.x;
        float dy = valot[i].pos.y - this->pos.y;
        float dz = valot[i].pos.z - this->pos.z;

        float d2 = dx*dx + dy*dy + dz*dz;

        if (d2 < valot[i].power)
        {
            float d = sqrtf(d2);
            if (d < 0.1f)
                d = 0.1f;
            this->color += valot[i].color * (1.0f / d);
        }
    }
}

void SauhuParticle::init()
{
    const float minsize = 0.27f;
    const float maxsize = 0.75f;
    const float minenergy = 0.05f;
    const float maxenergy = 0.13f;
    const float minfade = 0.03f * 4;
    const float maxfade = 0.05f * 4;

    this->size = Mathematics::randBetween(minsize, maxsize);

    const float distval = powf(Mathematics::randBetween(0.05f, 1.0f), 0.7f);
    const float dist = distval * 8;

    this->pos = Mathematics::randVectSphere() * dist;
    this->energy = Mathematics::randBetween(minenergy, maxenergy);
    this->energy_at_start = this->energy;
    this->fade = Mathematics::randBetween(minfade, maxfade) * (0.6f + 0.4f * distval);

    this->speed = Mathematics::randVectSphere() * Mathematics::randBetween(0.003f, 0.008f) + Vector3(0, 0.007f, 0);
}

void SauhuValo::update(float sync)
{
    this->power = this->basepower / 3.0f + (this->basepower * 2 / 3) * sync;
//    this->pos += this->speed;
}

void SauhuValo::init()
{
    this->pos = Mathematics::randVectSphere() * Mathematics::randBetween(0.7f, 2.5f);
    this->speed = Mathematics::randVectSphere() * Mathematics::randBetween(0.012f, 0.017f);
    this->color = getKasariColor();
    this->basepower = 4.0f;
}

Sauhu::Sauhu()
{	
    int i = 0;
	this->timer = new FrameTimer(1000 / 60, 10);

    this->count = 500;

    this->particles1 = new SauhuParticle[this->count];
    this->particles2 = new SauhuParticle[this->count];
    this->particles3 = new SauhuParticle[this->count];
    this->particles4 = new SauhuParticle[this->count];

    for (i = 0; i < this->count; i++)
    {
        this->particles1[i].init();
        this->particles2[i].init();
        this->particles3[i].init();
        this->particles4[i].init();
    }

    this->valocount = 5;
    this->valot = new SauhuValo[this->valocount];

    srand(1066); //10611
    for (i = 0; i < this->valocount; i++)
    {
        this->valot[i].init();

    }
}

Sauhu::~Sauhu()
{
	delete this->timer;

    delete [] this->particles1;
    delete [] this->particles2;
    delete [] this->particles3;
    delete [] this->particles4;

    delete [] this->valot;

}


bool Sauhu::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

