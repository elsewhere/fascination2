#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Nauhat.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Nauhat::draw()
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
    filter.glow(6, 0.009f, 0.009f, 0.90f, -1.0f, 1.0f);
}

void Nauhat::renderScene(float pos, float alpha)
{
    int i = 0;
	cam->useCamera(2);
	
	this->timer->update();
	while (this->timer->stepsLeft())
	{
		//todo stuff
        
        for (i = 0; i < this->count; i++)
        {
            this->nauhat[i]->update();

        }
		this->timer->endStep();
	}

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);//_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    const float posmod = (pos > 0.5f)?alpha : 1;
    for (i = 0; i < this->count; i++)
    {
        this->nauhat[i]->draw(pos, alpha);
    }
    glDisable(GL_LINE_SMOOTH);


    glDisable(GL_BLEND);


}


Nauha::Nauha()
{
    int i = 0;
    int j = 0;

    this->count = 1 + rand()%3;
    this->strips = new PolyStrip*[this->count];

    this->st = Mathematics::randBetween(0.0f, 0.98f);
    this->et = this->st + 0.25f;

    CatmullRom *base = new CatmullRom();

    base->startCreation();
    float a = Mathematics::randBetween(0, 2 * 3.141592f);
    float b = Mathematics::randBetween(0, 3.141592f);

    const float curl = 13.0f;

    float da = Mathematics::randBetween(-0.1f * curl, 0.1f * curl);
    float db = Mathematics::randBetween(-0.1f * curl, 0.01f * curl);

    Vector3 start = Mathematics::randVectSphere();

    for (i = 0; i < 10; i++)
    {
        base->addPoint(start);
        start += Mathematics::sphereToCartesian(0.5f, a, b);

        a += da;
        b += db;
    }
    base->endCreation();




    base->arcLengthParametrize(0, 1000);
    Vector3 color = getKasariColor();

    for (i = 0; i < this->count; i++)
    {
        const int accuracy = 20;

        CatmullRom *displace = new CatmullRom();
        CatmullRom *translation = new CatmullRom();

        displace->startCreation();
        Vector3 dp = Vector3(Mathematics::randBetween(0.002f, 0.005f), 0, 0) * Matrix::rotation(Mathematics::randVectSphere()*2*3.141592f);

        for (j = 0; j < accuracy; j++)
        {
            displace->addPoint(dp + Mathematics::randVectSphere() * Mathematics::randBetween(0.01f, 0.02f));
        }
        displace->endCreation();
        displace->arcLengthParametrize(0, 1000);
 
        translation->startCreation();
        for (j = 0; j < accuracy; j++)
        {
            translation->addPoint(Mathematics::randVectSphere() * Mathematics::randBetween(-0.15f, 0.15f));
            
        }

        translation->endCreation();
        float fade = Mathematics::randBetween(0.75f, 0.95f) / (i + 1);

        this->strips[i] = new PolyStrip(base, displace, translation, color, fade);
        delete displace;
        delete translation;
    }

    delete base;
}

Nauha::~Nauha()
{
    int i = 0; 
    for (i = 0; i < this->count; i++)
    {
        delete this->strips[i];
    }
    delete [] this->strips;
}

void Nauha::draw(float pos, float alpha)
{
    int i = 0;

    float t = Mathematics::calcPosFloat(pos, this->st, this->et);

    if (t > 0.0001f && t < 0.9999f)
    {
        float a = alpha * powf(sinf(t * 3.141592f), 0.8f);
        glPushMatrix();
        float s = 1.0f + t * 2.02f;
        glScalef(s, s, s);
        for (i = 0; i < this->count; i++)
        {
            this->strips[i]->draw(sinf(t * 3.141592f)*alpha, a);
        }
        glPopMatrix();
    }
}


void Nauha::update()
{
    int i = 0;
    for (i = 0; i < this->count; i++)
    {
        this->strips[i]->update();
    }
}

PolyStrip::PolyStrip(CatmullRom *src, CatmullRom *displacement, CatmullRom *translation, Vector3 &color, float fade)
{
    int i = 0;
    this->count = 100;

    this->vertices = new Vector3[this->count * 2]; //strip
    this->colors = new Vector3[this->count * 2]; //strip
    this->color = color;

    float t = 0.0f;
    Vector3 light = Vector3(0.7f, 0.5f, -0.968f).normalize();
    for (i = 0; i < this->count; i++)
    {
        Vector3 p = src->getValue(t) + translation->getValue(t);
        Vector3 d = displacement->getValue(t);

        this->vertices[(i << 1)] = p - d;
        this->vertices[(i << 1) + 1] = p + d;   
        this->colors[(i << 1)] = this->color * (p - d).normalize().dotProduct(light);
        this->colors[(i << 1) + 1] = this->color * (p + d).normalize().dotProduct(light);

        t += 1.0f / this->count;
    }

    this->fade = fade;//Mathematics::randBetween(0.75f, 0.95f);

}

PolyStrip::~PolyStrip()
{
    delete [] this->vertices;
}

void PolyStrip::update()
{
}


void PolyStrip::draw(float pos, float alpha)
{
    int i = 0;
//    glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade);
    glColor4f(this->color.x * this->fade, this->color.y* this->fade, this->color.z* this->fade, 1);

    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);//_MINUS_SRC_ALPHA);
    
    glBegin(GL_TRIANGLE_STRIP);

    int draw = (int)(this->count * 2 * pos);
    for (i = 0; i < draw; i++)
    {
        glColor3fv((float *)&this->colors[i]);
        glVertex3fv((float *)&this->vertices[i]);
    }
    glEnd();

    glColor4f(this->color.x * this->fade, this->color.y* this->fade, this->color.z* this->fade, 0.4f*alpha);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < draw; i+=2)
    {
        glVertex3fv((float *)&this->vertices[i]);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (i = 1; i < draw; i+=2)
    {
        glVertex3fv((float *)&this->vertices[i]);
    }
    glEnd();
}


Nauhat::Nauhat()
{	
    int i = 0;
    this->count = 150;


    this->nauhat = new Nauha*[this->count];

    srand(1061916);
    for (i = 0; i < this->count; i++)
    {
        this->nauhat[i] = new Nauha();
    }
	this->timer = new FrameTimer(1000 / 60, 10);
}

Nauhat::~Nauhat()
{
    int i = 0;
    for (i = 0; i < this->count; i++)
    {
        delete this->nauhat[i];
    }
    delete [] this->nauhat;
	delete this->timer;
}


bool Nauhat::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

