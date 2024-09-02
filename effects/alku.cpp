#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Alku.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Alku::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.01f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

    if (pos < fadeinstart)
    {
        alpha = 0.0f;
    }

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

	renderScene(pos, alpha);
}

void Alku::renderScene(float pos, float alpha)
{
    cam->useCamera(0);

    this->timer->update();
    while (this->timer->stepsLeft())
    {
        this->timer->endStep();
    }


    float sync = beat4->getValue();
    if (beat4->getChanged())
    {
    }
    int realtime = dmsGetModulePosition();

    bool secondimage = realtime > 8000;


    if (secondimage)
    {
        filter.init(true);
    }

    float secondt = Mathematics::calcPosFloat(realtime, 8000.0f, this->endTime);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    dmsPerspective2D(1,1);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);


    int index = realtime / 2000;
    if (index > 3)
        index = 3;

    glColor4f(1,1,1,alpha);
    const int flickerlength = 500;
    if (index == 1)
    {
        if (realtime >= 2000 && realtime <= 2000 + flickerlength)
        {
            float r = (realtime - 2000) / (float)(flickerlength);
            if (Mathematics::randFloat() > r)
            {
//                glColor4f(1,1,1,alpha*Mathematics::randFloat()*r);
                index = 0;
            }

        }
    }
    if (index == 3)
    {
        if (realtime >= 6000 && realtime <= 6000 + flickerlength)
        {
            float r = (realtime - 6000) / (float)(flickerlength);
            if (Mathematics::randFloat() > r)
            {
//                glColor4f(1,1,1,alpha*Mathematics::randFloat()*r);
                index = 2;
            }

        }

    }

/*
    const char textures[8][20] = 
    {
        "traction_off.jpg",
        "traction_on.jpg",
        "brainstorm_off.jpg",
        "brainstorm_on.jpg",
        "traction_off.jpg",
        "traction_on.jpg",
        "brainstorm_off.jpg",
        "brainstorm_on.jpg",
    };
*/
    const char textures[4][20] = 
    {
        "traction1.png",
        "traction2.png",
        "brainstorm1.png",
        "brainstorm2.png",
    };
    if (realtime < 8000)
    {
        glBindTexture(GL_TEXTURE_2D, dmsGetTexture(textures[index])->getID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, dmsGetTexture("title.png")->getID());
    }

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

    const float f = Mathematics::calcPosFloat(secondt, 0.0f, 0.2f);
    const float fadein = powf(cosf(f*3.141595f*0.5f), 2.0f) + sync * 0.4f;
    
    if (secondimage)
    {
        filter.glow(8, 0.005f + fadein*0.006f, 0.005f + fadein*0.006f, 0.92f - (1-fadein)*0.15f, -1.0f, 1.0f);
    }

}




Alku::Alku()
{	
    this->timer = new FrameTimer(1000 / 60, 10);
}

Alku::~Alku()
{
    delete this->timer;
}


bool Alku::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

