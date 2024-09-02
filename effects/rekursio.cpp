#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Rekursio.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Rekursio::draw()
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

//    filter.init(true);
	renderScene(pos, alpha);
//    filter.glow(8, 0.005f, 0.005f, 0.92f, -1.0f, 1.0f);
}

void Rekursio::renderScene(float pos, float alpha)
{
    Vector3 cam = Vector3(0, 0, -5);
    Vector3 tgt = Vector3(0, 0, 0);
    Vector3 upw = Vector3(0, 1, 0);

    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z, tgt.x, tgt.y, tgt.z, upw.x, upw.y, upw.z);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("texture_03.jpg")->getID());
    glColor4f(1,1,1,1);

    glExt.bindTextureFBO512(glExt.glowTexture512ID);//dmsGetTexture("render512_0")->getID());

    glPushMatrix();
    glRotatef(pos*1701, 0.4f - cosf(pos*16), 0.8f-pos*0.4f, 0.91f+sinf(pos*31));
    Primitives::texturedCube(1, 1);
    glPopMatrix();


    glExt.unbindFBO();
    glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);//dmsGetTexture("render512_0")->getID());

    dmsPerspective2D(1,1);
    glLoadIdentity();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(1, 0);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(0, 1);


    glEnd();
    

    dmsPerspective3D();
    glLoadIdentity();


}




Rekursio::Rekursio()
{	
}

Rekursio::~Rekursio()
{
}


bool Rekursio::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

