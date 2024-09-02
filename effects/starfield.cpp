#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Starfield.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Starfield::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.1f;
	const float fadeoutstart = 0.97f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

    filter.init(true);
	renderScene(pos, alpha);
    filter.glow(8, 0.006f, 0.006f, 0.93f, -1.0f, 1.0f);
}

void Starfield::renderScene(float pos, float alpha)
{
    int i = 0;
/*
    Vector campos = Vector(-8.0f, 0, 0);
    Vector camtgt = Vector(0, 0, 0);
    Vector camup = Vector(0, 1, 0);

    glLoadIdentity();
    gluLookAt(campos.x, campos.y, campos.z,
              camtgt.x, camtgt.y, camtgt.z,
              camup.x, camup.y, camup.z);
*/
    cam->useCamera(1);

    glRotatef(pos*250 + 150*cosf(pos*7), 1, 0, 0);
    
    glRotatef(70 * powf(sinf(Mathematics::calcPosFloat(pos, 0.67f, 1.00f)*3.141592f*0.5f), 1.4f), 0, 0, 1);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    int lc = (int)(this->count * Mathematics::calcPosFloat(pos, 0.0f, 0.1f));
    glBegin(GL_LINES);
    for (i = 0; i < lc; i++)
    {
        float t = fmodf(pos * 4 + this->stars[i].phase, 1);
        Vector3 p = this->stars[i].start + (this->stars[i].end - this->stars[i].start) * t;
        glColor4f(this->stars[i].color.x, this->stars[i].color.y, this->stars[i].color.z, 
                  alpha * sinf(t * 3.141592f) * this->stars[i].fade);
        glVertex3fv((float *)&p);
        glColor4f(this->stars[i].color.x, this->stars[i].color.y, this->stars[i].color.z, 
                  0);//alpha * sinf(t * 3.141592f) * this->stars[i].fade);
        glVertex3fv((float *)&(p + Vector3(this->stars[i].length, 0, 0)));
        
    }
    glEnd();
    glDisable(GL_LINE_SMOOTH);

}




Starfield::Starfield()
{	
    int i = 0;
    this->count = 45000;
    this->stars = new Star[count];

    for (i = 0; i < this->count; i++)
    {
        float r = powf(Mathematics::randFloat(), 0.8f)*12.0f;
        float a = Mathematics::randBetween(0, 2*3.141592f);
        this->stars[i].start = Vector3(0, cosf(a), sinf(a)) * r;
        this->stars[i].end = Vector3(0, cosf(a), sinf(a)) * r;

        const float l = 30.0f;
        this->stars[i].start.x = l;
        this->stars[i].end.x = -l;
        this->stars[i].phase = Mathematics::randFloat();
        this->stars[i].color = getKasariColor();
        this->stars[i].length = Mathematics::randBetween(0.3f, 0.51f);
        this->stars[i].fade = Mathematics::randBetween(0.5f, 0.9f);


    }
}

Starfield::~Starfield()
{
    delete [] this->stars;
}


bool Starfield::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

