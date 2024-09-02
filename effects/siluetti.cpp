#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Siluetti.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Siluetti::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.1f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;
/*
	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);
*/
    filter.init(true);
	renderScene(pos, alpha*0.1f);
    filter.glow(6, 0.004f, 0.004f, 0.92f, -1.0f, 1.0f);
}

void Siluetti::renderScene(float pos, float alpha)
{
    int i = 0;
    glLoadIdentity();
    glTranslatef(0, 0, -7.0f);
    glRotatef(10+pos*20, 0, 0, 1);

    float sync = beat4->getValue();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
    glBegin(GL_QUADS);
    const int strips = 70;
    int dc = (int)(strips * Mathematics::calcSaturate(pos, 0.0f, 1.0f, 5));
    for (i = 0; i < dc; i++)
    {
        float t = i / (float)strips - 0.5f;

        float width = 12.0f;
        float height = 9.2f * t;
        const float stripheight = 0.025f;
        
        Vector3 p1 = Vector3(-width, height, 0);
        Vector3 p2 = Vector3( width, height, 0);
        Vector3 p3 = Vector3( width, height + stripheight, 0);
        Vector3 p4 = Vector3(-width, height + stripheight , 0);

        glColor4f(0.5f, 0.9f, 0.9f, 
            alpha * (0.4f + 0.1f*sync) * (0.8 + 0.3f*cosf(i * (0.3f + 0.1f*cosf(i*0.1f+pos*11)) + pos*18 - 13 * sinf(i * 0.1f + pos*11))));
        glVertex3fv((float *)&p1);
        glVertex3fv((float *)&p2);
        glVertex3fv((float *)&p3);
        glVertex3fv((float *)&p4);
    }
    glEnd();


    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glColor4f(0,0,0,0);
    glTranslatef(0, 0, 1);
    glRotatef(pos*4610, 0.7f-cosf(pos*51), 0.4f*sinf(pos*33), 0.11f + pos*0.7f);
//    this->mesh->renderVBO(MESH_VERTEX_BIT);

    glPopMatrix();



}




Siluetti::Siluetti()
{
    this->mesh = TMeshFactory::createTorus(4, 1, 64, 64, 1.0f);
    this->mesh->scale(2.0f);
    this->mesh->createVBO(MESH_VERTEX_BIT);
}

Siluetti::~Siluetti()
{
}


bool Siluetti::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

