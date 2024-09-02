#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Loppu.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Loppu::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.2f;
	const float fadeoutstart = 0.99f;
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

void Loppu::renderScene(float pos, float alpha)
{
    int realtime = dmsGetModulePosition();
    const float start = 200000;
    const float fade = powf(sinf(Mathematics::calcPosFloat((float)realtime, start, start+2100)*0.5f*3.141592f), 1.6f);
    const float a = alpha * (0.2f + fade * 0.8f);

    bool blur = fade < 0.99999f;

    if (blur)
    {
        filter.init();
    }

    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    dmsPerspective2D(1,1);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);


    glColor4f(1,1,1, a);

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

    if (blur)
    {
        float blurval = 0.01f * (1 - fade);
        filter.blur(5, blurval, blurval);
    }

}




Loppu::Loppu()
{	
    this->timer = new FrameTimer(1000 / 60, 10);
}

Loppu::~Loppu()
{
    delete this->timer;
}


bool Loppu::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

