#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Psyko.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Psyko::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.1f;
	const float fadeinstop = 0.17f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

    if (pos < fadeinstart)
        alpha = 0.0f;
	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
//	if (pos >= fadeoutstart && pos <= fadeoutstop)
//		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

    filter.init(true);
	renderScene(pos, alpha);
    filter.glow(5, 0.008f, 0.008f, 0.92f, -1.0f, 1.0f);
}

void Psyko::renderScene(float pos, float alpha)
{
    int i = 0;

    this->timer->update();
    while (this->timer->stepsLeft())
    {
        for (i = 0; i < this->tahticount; i++)
        {
            Tahti &p = this->tahdet[i];
            if (p.active)
            {
                p.position += p.direction * 0.01f;
                p.energy -= 0.001f;
                if (p.energy <= 0.000f)
                {
                    p.active = false;
                }
            }
        }
        //add

        if (pos < 0.97f)
        {
            for (i = 0; i < 4; i++)
            {
                if (!this->tahdet[tahtiindex].active)
                {
                    this->tahdet[tahtiindex].init();
                }
                tahtiindex++;
                tahtiindex %= this->tahticount;
            }
        }

        this->timer->endStep();
    }





    cam->useCamera(2);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);


    if (alpha > 0.00001f)
    {
        int offs = 0;
        const float speedmod = 0.35f;

        Matrix rotation;

        for (float t = 0.0f; t < 1.0f; t += 1.0f / vcount)
        {
            Vector sp = coords->getValue(t);

            sp.x += 0.3f*cosf(t * 100 + pos*speedmod*111) + 0.07f*cosf(t * 150 - pos*speedmod*70);
            if (sp.x < 0.05f)
                sp.x = 0.05f;
            sp.y += 0.1f*cosf(t * 600 + pos*speedmod*70);
            sp.z += 0.1f*cosf(t * 400 + pos*speedmod*170);
        
            Vector p = Mathematics::sphereToCartesian(sp.x, sp.y, sp.z) * 4;

            float w = 0.12f + 0.14f*cosf(t * 100);

            rotation.makeRotation(t*100, t*200, t*70);

            Vector v1 = p + Vector(w, 0, 0) * rotation;
            Vector v2 = p + Vector(-w, 0, 0) * rotation;

            leftedge[offs] = v1;
            rightedge[offs] = v2;

            offs++;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUAD_STRIP);
        int end = (int)(Mathematics::calcSaturate(pos, 0.07f, 1, 3) * vcount); 

        Vector c1 = Vector(0.7f, 0.2f, 0.5f);
        Vector c2 = Vector(0.4f, 0.2f, 0.2f) * 0;
        for (i = 0; i < end; i++)
        {
            float it = i / (float)vcount;

            float colort = sinf(fmodf(it * 20, 1)*3.141592f);

            Vector c = c1 * (colort) + c2 * (1 - colort);//(c2 - c1) * (1 - colort);
            glColor4f(c.x, c.y, c.z, alpha * 0.18f);

            glVertex3fv((float *)&leftedge[i]);
            glVertex3fv((float *)&rightedge[i]);
        }
        glEnd();

        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glLineWidth(3.0f);
        glColor4f(0.4f, 0.74f, 0.9f, alpha*0.8f);
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < end; i++)
        {
            glVertex3fv((float *)&leftedge[i]);
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < end; i++)
        {
            glVertex3fv((float *)&rightedge[i]);
        }
        glEnd();

    }

    //particlet
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("circle.jpg")->getID());
    Vector3 xr, yr, zr;
    Mathematics::antiRotate(&xr, &yr, &zr);
    glBegin(GL_QUADS);

    float particlefade = Mathematics::calcSaturate(pos, 0.00f, 0.97f, 4.6f);
    for (i = 0; i < this->tahticount; i++)
    {
        Tahti &p = this->tahdet[i];
        if (p.active)
        {
            float t = sinf((p.energy / p.maxenergy)*3.141592f);
            glColor4f(p.color.x,p.color.y,p.color.z, particlefade * t * p.fade);

            float s = p.size * t;

            Vector3 v1 = p.position - xr * s - yr * s;
            Vector3 v2 = p.position + xr * s - yr * s;
            Vector3 v3 = p.position + xr * s + yr * s;
            Vector3 v4 = p.position - xr * s + yr * s;

            glTexCoord2f(0, 0);
            glVertex3fv((float *)&v1);
            glTexCoord2f(1, 0);
            glVertex3fv((float *)&v2);
            glTexCoord2f(1, 1);
            glVertex3fv((float *)&v3);
            glTexCoord2f(0, 1);
            glVertex3fv((float *)&v4);



        }
    }
    glEnd();

    glDisable(GL_LINE_SMOOTH);

}


void Tahti::init()
{
    this->size = Mathematics::randBetween(0.02f, 0.035f);
    this->direction = Mathematics::randVectSphere()*2;

    this->position.x = Mathematics::randBetween(-7, 7);
    this->position.y = Mathematics::randBetween(-3.0f, 3.0f);
    this->position.z = Mathematics::randBetween(-7, 7);
    this->direction.y /= 4.0f;

    this->direction.x += 1.8f;

    this->color = Vector(0.4f, 0.74f, 0.9f);
    this->energy = Mathematics::randBetween(0.05f, 0.2f);
    this->fade = Mathematics::randBetween(0.2f, 0.65f);

    this->maxenergy = this->energy;
    this->active = true;
}


Psyko::Psyko()
{	
    int i;
    count = 150;

    vcount = 2000;
    leftedge = new Vector[vcount];
    rightedge = new Vector[vcount];

    coords = new CatmullRom();

    srand(101961);

    float a = 0.0f;
    float b = 0.0f;
    float rt = 0.0f;

    coords->startCreation();
    for (i = 0; i < count; i++)
    {
        float it = i / (float)count;
        float r = 0.2f+0.15f*cosf(rt);

        Vector3 p = Vector3(r, a, b);
        coords->addPoint(p);

        a += Mathematics::randBetween(0.1f, 0.2f);
        b += Mathematics::randBetween(0.2f, 0.4f);

        rt += Mathematics::randBetween(0.3f, 1.0f);

    }
    coords->endCreation();

    this->tahticount = 1500;
    this->tahdet = new Tahti[this->tahticount];
    this->tahtiindex = 0;

    for (i = 0; i < this->tahticount; i++)
    {
        this->tahdet[i].active = false;
    }

    this->timer = new FrameTimer(1000 / 60, 10);

}

Psyko::~Psyko()
{
    delete [] leftedge;
    delete [] rightedge;
    delete coords;
}


bool Psyko::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

