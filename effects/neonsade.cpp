#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Neonsade.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Neonsade::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = 0.0f;
	const float fadeinstop = 0.1f;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
//	if (pos >= fadeoutstart && pos <= fadeoutstop)
//		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

	renderScene(pos, alpha);
}

Neonpisara::Neonpisara()
{
    this->count = 10;
    this->positions = new Vector3[this->count];
    this->speeds = new Vector3[this->count];

    this->state = PISARA_STATE_NONE;
    this->init();

}

Neonpisara::~Neonpisara()
{
    delete [] this->positions;
}

const float downspeed = 0.055f;

void Neonpisara::init()
{
    int i = 0;
    this->color = getKasariColor();//Mathematics::randVectSphere();

    float a = Mathematics::randBetween(0, 2*3.141592f);

    const float max_r = 3.0f;
    float r = powf(Mathematics::randFloat(), 1.0f) * max_r;

    Vector3 basepos = Vector3(cosf(a), 0, sinf(a)) * r;

    basepos.y = Mathematics::randBetween(0.3f, 4.0f);
    Vector3 p = basepos;

    for (i = 0; i < this->count; i++)
    {
        this->positions[i] = p;
        this->speeds[i] = Vector3(0, -downspeed, 0);
        p.y += 0.025f;
    }
    this->fade = Mathematics::randBetween(0.14f, 0.3f) * (0.6f + 0.4f * (max_r - r));
    this->state = PISARA_STATE_FALL;

}
void Neonpisara::draw(float pos, float alpha)
{
    if (this->state == PISARA_STATE_FALL)
    {

    }
    else if (this->state == PISARA_STATE_BOUNCE || this->state == PISARA_STATE_DID_NOT_HIT)
    {
        alpha *= (float)this->updatesLeft / (float)this->updatesFromStart;
    }
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < this->count; i++)
    {
        glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade * (1.0f - 0.2f * i / (float)this->count));
        glVertex3fv((float *)&this->positions[i]);
    }
    glEnd();

}

void Neonpisara::update(float area)
{
    int i = 0;

    if (this->state == PISARA_STATE_FALL)
    {
        for (i = 0; i < this->count; i++)
        {
            this->positions[i] += this->speeds[i];
        }

        if (this->positions[0].y < 0.0f) //etummainen
        {
            if (this->positions[0].x > -area && 
                this->positions[0].x <  area && 
                this->positions[0].z > -area && 
                this->positions[0].z <  area)
            {
                this->dir = Mathematics::randVectSphere() * 0.05f;
                this->dir.y = fabsf(this->dir.y) * 3.0f;
                this->state = PISARA_STATE_BOUNCE;
                this->updatesLeft = 30 + rand() % 50;
                this->updatesFromStart = this->updatesLeft;
                this->pointsHit = 0;
            }
            else
            {
                this->state = PISARA_STATE_DID_NOT_HIT;
                this->updatesLeft = 30 + rand() % 50;
                this->updatesFromStart = this->updatesLeft;
            }
        }
    }
    else if (this->state == PISARA_STATE_DID_NOT_HIT)
    {
        for (i = 0; i < this->count; i++)
        {
            this->positions[i] += this->speeds[i];
        }
        this->updatesLeft--;
        if (this->updatesLeft < 0)
        {
            this->init();
        }
    }
    else if (this->state == PISARA_STATE_BOUNCE)
    {
        this->updatesLeft--;
        if (this->updatesLeft < 0)
        {
            this->init();
        }

        if (this->pointsHit >= this->count)
        {
            this->pointsHit = this->count;
        }
        else //this->pointsHit < this->count
        {
            this->speeds[this->pointsHit] = this->dir;
            this->pointsHit++;
        }

        //liikutetaan
        for (i = 0; i < this->count; i++)
        {
            this->positions[i] += this->speeds[i];
        }

        for (i = 0; i < this->pointsHit; i++)
        {
            this->speeds[i].y -= 0.003f;
        }



    }


}
void Neonsade::renderScene(float pos, float alpha)
{
    int i = 0;
    cam->useCamera(0);

/*    glLoadIdentity();
    glTranslatef(0, 0, -40);
    glRotatef(pos*610, 0.4f, 0.7f, 0.1f);
*/


    static float yoff = 0.0f;
    static float xoff = 0.3f;
    static float yoff2 = 0.0f;
    static float xoff2 = 0.3f;



    this->timer->update();
    while (this->timer->stepsLeft())
    {
        yoff += 0.01f;
        yoff2 += 0.005f;
        for (i = 0; i < this->count; i++)
        {
            this->pisarat[i]->update(this->area);
        }
        this->timer->endStep();
    }
    filter.init(true);

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);

    for (i = 0; i < this->reunuscount; i++)
    {
        this->reunukset[i]->draw(pos, alpha);
    }
    glEnd();
    glLineWidth(2.0f);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    for (i = 0; i < this->reunuscount; i++)
    {
        this->reunukset[i]->drawOutline(pos, alpha);
    }
    glEnd();


    //kuutio

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(3.0f);
    float y = 0.0f;
    float depth = 43.0f;
    float linedepth = 4.0f;
   
    Vector k1 = Vector(-this->area, y, -this->area);
    Vector k2 = Vector( this->area, y, -this->area);
    Vector k3 = Vector( this->area, y,  this->area);
    Vector k4 = Vector(-this->area, y,  this->area);
    Vector k5 = Vector(-this->area, y - depth, -this->area);
    Vector k6 = Vector( this->area, y - depth, -this->area);
    Vector k7 = Vector( this->area, y - depth,  this->area);
    Vector k8 = Vector(-this->area, y - depth,  this->area);

    Vector lk5 = Vector(-this->area, y - linedepth, -this->area);
    Vector lk6 = Vector( this->area, y - linedepth, -this->area);
    Vector lk7 = Vector( this->area, y - linedepth,  this->area);
    Vector lk8 = Vector(-this->area, y - linedepth,  this->area);

    glDisable(GL_BLEND);
    glColor4f(0,0,0,1);

    glBegin(GL_QUADS);
    glVertex3fv((float *)&k1);
    glVertex3fv((float *)&k2);
    glVertex3fv((float *)&k3);
    glVertex3fv((float *)&k4);

    glVertex3fv((float *)&k1);
    glVertex3fv((float *)&k2);
    glVertex3fv((float *)&k6);
    glVertex3fv((float *)&k5);

    glVertex3fv((float *)&k3);
    glVertex3fv((float *)&k4);
    glVertex3fv((float *)&k8);
    glVertex3fv((float *)&k7);

    glVertex3fv((float *)&k1);
    glVertex3fv((float *)&k5);
    glVertex3fv((float *)&k8);
    glVertex3fv((float *)&k4);

    glVertex3fv((float *)&k2);
    glVertex3fv((float *)&k6);
    glVertex3fv((float *)&k7);
    glVertex3fv((float *)&k3);

    glEnd();


    const float linefadeout = 1.0f - sinf(Mathematics::calcPosFloat(pos, 0.94f, 0.99f)*3.141592f*0.5f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glColor4f(0.4f,0.7f,0.9f,alpha * Mathematics::calcPosFloat(pos, 0.03f, 0.25f)*linefadeout);

    float rise = 0.01f;
    Vector3 trans = Vector3(0, rise, 0);
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBegin(GL_LINE_LOOP);
    glVertex3fv((float *)&(k1 + trans + Vector3(-rise, 0, -rise)));
    glVertex3fv((float *)&(k2 + trans + Vector3( rise, 0, -rise)));
    glVertex3fv((float *)&(k3 + trans + Vector3( rise, 0,  rise)));
    glVertex3fv((float *)&(k4 + trans + Vector3(-rise, 0, rise)));
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.7f,0.4f,0.9f,alpha * Mathematics::calcPosFloat(pos, 0.03f, 0.25f) * linefadeout);
    glVertex3fv((float *)&(k1 + trans + Vector3(-rise, 0, -rise)));
    glColor4f(0.7f,0.4f,0.9f,0);
    glVertex3fv((float *)&(lk5 + trans + Vector3(-rise, 0, -rise)));
    glColor4f(0.7f,0.4f,0.9f,alpha * Mathematics::calcPosFloat(pos, 0.03f, 0.25f) * linefadeout);
    glVertex3fv((float *)&(k2 + trans + Vector3( rise, 0, -rise)));
    glColor4f(0.7f,0.4f,0.9f,0);
    glVertex3fv((float *)&(lk6 + trans + Vector3( rise, 0, -rise)));
    glColor4f(0.7f,0.4f,0.9f,alpha * Mathematics::calcPosFloat(pos, 0.03f, 0.25f) * linefadeout);
    glVertex3fv((float *)&(k3 + trans + Vector3( rise, 0,  rise)));
    glColor4f(0.7f,0.4f,0.9f,0);
    glVertex3fv((float *)&(lk7 + trans + Vector3( rise, 0,  rise)));
    glColor4f(0.7f,0.4f,0.9f,alpha * Mathematics::calcPosFloat(pos, 0.03f, 0.25f) * linefadeout);
    glVertex3fv((float *)&(k4 + trans + Vector3(-rise, 0, rise)));
    glColor4f(0.7f,0.4f,0.9f,0);
    glVertex3fv((float *)&(lk8 + trans + Vector3(-rise, 0, rise)));
    glEnd();
    glDepthMask(0);

    const float pisarafadeout = 1.0f - sinf(Mathematics::calcPosFloat(pos, 0.96f, 0.99f)*3.141592f*0.5f);

    for (i = 0; i < this->count; i++)
    {
        pisarat[i]->draw(pos, alpha * pisarafadeout);
    }
    glDisable(GL_LINE_SMOOTH);
    glDepthMask(1);
    filter.glow(8, 0.007f, 0.007f, 0.91f, -1.0f, 1.0f);

    const float mahtuuX = 0.7f;
    const float mahtuuY = mahtuuX*(480/640.0f);
    const float mahtuuX2 = 0.9f;
    const float mahtuuY2 = mahtuuX*(480/640.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("rain_tex.png")->getID());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);


    Camera c = cam->getCamera(0);
    float cameratime = cam->getCameraTime(0);

    Vector3 campos = c.path->getValue(cameratime);
    Vector3 camtarget = c.target->getValue(cameratime);

    Vector3 dir = camtarget - campos;
    dir.normalize();

    Vector3 down = Vector3(0, -1, 0);
    float kulma = acosf(dir.dotProduct(down) / (dir.length() * down.length()));

    const float alphamod = kulma;

    dmsMsg("kulma = %1.3f dir.y = %1.3f. suhde = %1.3f\n", kulma, dir.y, kulma / dir.y);


    glLoadIdentity();
    dmsPerspective2D(1,1);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor4f(1, 1,1, alpha*0.24f*alphamod);

    glTexCoord2f(xoff, yoff);
    glVertex2f(0, 0);
    glTexCoord2f(xoff+mahtuuX, yoff);
    glVertex2f(1, 0);
    glTexCoord2f(xoff+mahtuuX, yoff+mahtuuY);
    glVertex2f(1, 1);
    glTexCoord2f(xoff, yoff+mahtuuY);
    glVertex2f(0, 1);

    glColor4f(1, 1,1, alpha*0.18f*alphamod);
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

}

Reunus::Reunus()
{
    this->count = 7 + (rand()%4);

    this->vertices = new Vector3[this->count * 4];
    do
    {
        this->color = getKasariColor();
    } while (this->color.length() < 0.9f);

    this->fade = Mathematics::randBetween(0.1f, 0.12f);

    this->st = Mathematics::randBetween(0.1f, 0.7f);
    this->et = this->st + Mathematics::randBetween(0.02f, 0.04f);

    Vector3 point;
    Vector3 pointdelta;
    Vector3 c1, c2, c3;

    static int tahkocount = 0;
    int tahko = (tahkocount++)%4;//rand()%4;
    //paikan muuttujat
    const float dist = Mathematics::randBetween(12.5f, 15.0f);
    const float minkorkeus = -15.0f;
    const float maxkorkeus = 35.0f;
    const float minsyvyys = -15.0f;
    const float maxsyvyys =  15.0f;

    bool suunta = (rand()%2)==1?true:false;
    //jutun muuttujat
    float stripwidth = Mathematics::randBetween(0.5f, 0.7f) * suunta?-1:1;
    float stripmargin = Mathematics::randBetween(0.5f, 0.55f) * suunta?-1:1;
    float stripheight = Mathematics::randBetween(1.5f, 3.0f);// * suunta?-1:1;//5.0f;


    
    switch(tahko)
    {
        case 0: 
            point.x = dist;
            point.y = Mathematics::randBetween(minkorkeus, maxkorkeus);
            point.z = Mathematics::randBetween(minsyvyys, maxsyvyys);
            pointdelta = Vector3(0, 0, stripwidth + stripmargin);
            c1 = Vector3(0, 0, stripwidth);
            c2 = Vector3(0, stripheight, stripwidth);
            c3 = Vector3(0, stripheight, 0);
            break;
       case 1:
            point.x = -dist;
            point.y = Mathematics::randBetween(minkorkeus, maxkorkeus);
            point.z = Mathematics::randBetween(minsyvyys, maxsyvyys);
            pointdelta = Vector3(0, 0, stripwidth + stripmargin);
            c1 = Vector3(0, 0, stripwidth);
            c2 = Vector3(0, stripheight, stripwidth);
            c3 = Vector3(0, stripheight, 0);
            break;
        case 2: 
            point.x = Mathematics::randBetween(minsyvyys, maxsyvyys);
            point.y = Mathematics::randBetween(minkorkeus, maxkorkeus);
            point.z = dist;
            pointdelta = Vector3(stripwidth + stripmargin, 0, 0);
            c1 = Vector3(stripwidth, 0, 0);
            c2 = Vector3(stripwidth, stripheight, 0);
            c3 = Vector3(0, stripheight, 0);
            break;
        case 3:
            point.x = Mathematics::randBetween(minsyvyys, maxsyvyys);
            point.y = Mathematics::randBetween(minkorkeus, maxkorkeus);
            point.z = -dist;
            pointdelta = Vector3(stripwidth + stripmargin, 0, 0);
            c1 = Vector3(stripwidth, 0, 0);
            c2 = Vector3(stripwidth, stripheight, 0);
            c3 = Vector3(0, stripheight, 0);
            break;
    }

    






    for (int i = 0; i < this->count; i++)
    {
        int offs = i << 2;
        this->vertices[offs] = point;
        this->vertices[offs + 1] = point + c1;
        this->vertices[offs + 2] = point + c2;
        this->vertices[offs + 3] = point + c3;

        point += pointdelta;

    }

}

void Reunus::draw(float pos, float alpha)
{
    int i = 0;

    float t = Mathematics::calcPosFloat(pos, this->st, this->et) * (1.0f - Mathematics::calcPosFloat(pos, 0.98f, 1.0f));

    if (t > 0.0001f)
    {
        for (i = 0; i < (int)(count * t); i++)
        {
            glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade * sinf(t * 3.141592f * 0.5f));
            int offs = i << 2;
            glVertex3fv((float *)&this->vertices[offs]);
            glVertex3fv((float *)&this->vertices[offs+1]);
            glVertex3fv((float *)&this->vertices[offs+2]);
            glVertex3fv((float *)&this->vertices[offs+3]);

        }
    }

}
void Reunus::drawOutline(float pos, float alpha)
{
    int i = 0;

    float t = Mathematics::calcPosFloat(pos, this->st, this->et);

    if (t > 0.0001f)
    {
        for (i = 0; i < count; i++)//(int)(count * t); i++)
        {
            glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade * 1.5f * sinf(t * 3.141592f * 0.5f));
            int offs = i << 2;
            glVertex3fv((float *)&this->vertices[offs+0]);
            glVertex3fv((float *)&this->vertices[offs+1]);
            glVertex3fv((float *)&this->vertices[offs+1]);
            glVertex3fv((float *)&this->vertices[offs+2]);
            glVertex3fv((float *)&this->vertices[offs+2]);
            glVertex3fv((float *)&this->vertices[offs+3]);
            glVertex3fv((float *)&this->vertices[offs+3]);
            glVertex3fv((float *)&this->vertices[offs+0]);

        }
    }

}


Neonsade::Neonsade()
{
    int i = 0;
    timer = new FrameTimer(1000/60, 10);

    this->area = 1.2f;

    srand(6101);
    this->reunuscount = 140;
    this->reunukset = new Reunus*[this->reunuscount];

    for (i = 0; i < this->reunuscount; i++)
    {
        this->reunukset[i] = new Reunus();
    }

    this->count = 5000;
    this->pisarat = new Neonpisara*[this->count];

    for (i = 0; i < this->count; i++)
    {
        this->pisarat[i] = new Neonpisara();
    }
}

Neonsade::~Neonsade()
{
    int i = 0; 
    for (i = 0; i < this->count; i++)
    {
        delete this->pisarat[i];
    }
    delete [] this->pisarat;

    delete timer;
}


bool Neonsade::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

