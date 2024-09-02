#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Sade.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Sade::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.15f;
	const float fadeoutstart = 0.80f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

//    filter.init(true);
	renderScene(pos, alpha);
//    filter.glow(8, 0.005f, 0.005f, 0.92f, -1.0f, 1.0f);
}

void Sade::renderScene(float pos, float alpha)
{
/*
    Vector cam = Vector(0, 0, -7);
    Vector tgt = Vector(0, 0, 0);
    Vector upw = Vector(0, 1, 0);

    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z, tgt.x, tgt.y, tgt.z, upw.x, upw.y, upw.z);
*/


    glLoadIdentity();
    dmsPerspective2D(1,1);
    glLoadIdentity();

    static float yoff = 0.0f;
    static float xoff = 0.3f;
    static float yoff2 = 0.0f;
    static float xoff2 = 0.3f;

    this->timer->update();
    while (this->timer->stepsLeft())
    {

        yoff += 0.01f;
        yoff2 += 0.005f;

        this->timer->endStep();
    }

/*
    const float yoff = pos*21;
    const float xoff = 0.3f;
    const float yoff2 = pos*11;
    const float xoff2 = 0.3f;
*/
    const float mahtuuX = 0.7f;
    const float mahtuuY = mahtuuX*(480/640.0f);
    const float mahtuuX2 = 0.9f;
    const float mahtuuY2 = mahtuuX*(480/640.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("rain_tex.png")->getID());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBegin(GL_QUADS);
    glColor4f(1, 1,1, alpha*0.24f);

    glTexCoord2f(xoff, yoff);
    glVertex2f(0, 0);
    glTexCoord2f(xoff+mahtuuX, yoff);
    glVertex2f(1, 0);
    glTexCoord2f(xoff+mahtuuX, yoff+mahtuuY);
    glVertex2f(1, 1);
    glTexCoord2f(xoff, yoff+mahtuuY);
    glVertex2f(0, 1);

    glColor4f(1, 1,1, alpha*0.18f);
    glTexCoord2f(xoff2, yoff2);
    glVertex2f(0, 0);
    glTexCoord2f(xoff2+mahtuuX2, yoff2);
    glVertex2f(1, 0);
    glTexCoord2f(xoff2+mahtuuX2, yoff2+mahtuuY2);
    glVertex2f(1, 1);
    glTexCoord2f(xoff2, yoff2+mahtuuY2);
    glVertex2f(0, 1);

    glEnd();

    dmsPerspective3D();
    glLoadIdentity();

	//glDisable(GL_BLEND);
}




Sade::Sade(int camera)
{	
    this->timer = new FrameTimer(1000 / 60, 10);
    this->camref = camera;
}

Sade::~Sade()
{
    delete this->timer;
}


bool Sade::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

