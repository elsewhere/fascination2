#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Kareet.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Kareet::draw()
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

	renderScene(pos, alpha);
}

Kare::Kare()
{
}


Kare::~Kare()
{

}

const float KARE_MAX_DIST = 12.0f;

void Kare::init(KarePisara &p)
{
    this->center = p.position;//Vector3(cosf(a), 0, sinf(a)) * r;
    this->center.y = 0.0f;

    this->d = this->center.length();
    this->color = p.color;//getKasariColor();
    this->r = Mathematics::randBetween(0.02f, 0.06f);
    this->fade = p.fade * 1.5f;//Mathematics::randBetween(0.6f, 0.9f);

    if (p.special)
    {
        this->fade *= 2.0f;
    }
    this->active = true;
}


Vector3 Kare::aalto(float pos, Vector3 &center)
{
    //TODO: paremmin
    float x = 0.0f;
    float y = 0.12f * sinf(center.x + pos * 37);
    float z = 0.0f;
    return Vector3(x, y, z);

}

void Kare::update(float pos)
{
    if (this->active)
    {
        this->r += 0.007f;
        this->fade -= 0.01f;

        const float epsilon = 0.04f;
        Vector3 here = Kare::aalto(pos, this->center);
        Vector3 dx = Kare::aalto(pos, this->center - Vector3(epsilon, 0, 0));
        Vector3 dz = Kare::aalto(pos, this->center - Vector3(0, 0, epsilon));

        Vector3 rotation = Vector3(here.x - dx.x, 0, here.z - dz.z) * 2 * 3.141592f;

        this->rotationmatrix.makeIdentity();
        this->rotationmatrix.makeRotation(rotation.x, rotation.y, rotation.z);

        this->centerdelta = this->center + Kare::aalto(pos, this->center);

        if (this->fade <= 0.0f)
        {
            this->active = false;
        }
    }
}

KarePisara::KarePisara()
{
    this->init();
}
KarePisara::~KarePisara()
{
}

void KarePisara::draw(float pos, float alpha)
{
    glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade);
    glVertex3fv((float *)&this->position);
    glColor4f(this->color.x, this->color.y, this->color.z, alpha * this->fade * 0.2f);
    glVertex3fv((float *)&(this->position + Vector3(0, this->length, 0)));
}
bool KarePisara::update()
{
    this->position += this->speed;//0.06f;

    if (this->position.y < 0.0f)
    {
        return false;
    }
    return true;
}

void KarePisara::init()
{
    float r = 0.1f + powf(Mathematics::randFloat(), 0.6f) * KARE_MAX_DIST;
    float a = Mathematics::randBetween(0, 2*3.141592f);

    this->special = (rand()%25) == 0;

    this->position = Vector3(cosf(a), 0, sinf(a)) * r;
    this->position.y = Mathematics::randBetween(3.0f, 5.0f) * (this->special?1.7f:1.0f);

    this->color = getKasariColor();
    this->fade = Mathematics::randBetween(0.4f, 0.7f);
    this->length = Mathematics::randBetween(0.1f, 0.3f);

    this->speed = Vector3(0, -Mathematics::randBetween(0.05f, 0.125f), 0);
   
}


void KareParticle::set(KarePisara &p)
{
    this->position = p.position;
    this->color = p.color + (Vector3(1,1,1) - p.color) * Mathematics::randBetween(0.5f, 0.8f);
    this->speed = Mathematics::randVectSphere();

    this->velocity = p.speed.y * 0.1f;
    this->life = Mathematics::randBetween(0.3f, 0.6f);
    this->maxlife = this->life;

    this->fade = p.fade;

    this->active = true;
}


void KareParticle::update()
{
    this->active = this->life > 0.0f;

    if (this->active)
    {
        this->life -= 0.01f;
        this->position += this->speed * this->velocity;
        this->speed.y += 0.01f;
        this->speed.x += 0.04f;
    }
}


void Kare::draw(float pos, float alpha)
{
    if (!this->active)
        return;
    
    int i = 0;
    const int steps = 32;

    glColor4f(this->color.x, this->color.y, this->color.z, this->fade * alpha * ((KARE_MAX_DIST - this->d) / KARE_MAX_DIST));

    glBegin(GL_LINE_LOOP);
    for (float t = 0.0f; t < 1.0f; t += 1.0f / steps)
    {
        float a = t * 2 * 3.141592f;
        Vector3 p = Vector3(cosf(a), 0, sinf(a)) * this->r + centerdelta;
        glVertex3fv((float *)&(p * this->rotationmatrix));
    }
    glEnd();


}

void Kareet::initKare(KarePisara *p)
{
    int tries = 0;
    while (this->kareet[kareoffset]->active || tries > 1000)
    {
        tries++;
        kareoffset++;
        kareoffset %= this->karecount;
    }

    this->kareet[kareoffset]->init(*p);



}

void Kareet::renderScene(float pos, float alpha)
{
    int i = 0;
    cam->useCamera(0);
    filter.init(true);

    static float yoff = 0.0f;
    static float xoff = 0.3f;
    static float yoff2 = 0.0f;
    static float xoff2 = 0.3f;

    this->timer->update();
    while (this->timer->stepsLeft())
    {
        yoff += 0.01f;
        yoff2 += 0.005f;

        for (i = 0; i < this->pisaracount; i++)
        {
            //luodaan kare
            if (!this->pisarat[i]->update())
            {
                initKare(this->pisarat[i]);
                this->pisarat[i]->init();
            }
            if (this->pisarat[i]->special)
            {
                this->particlet[this->particleindex++]->set(*this->pisarat[i]);
                this->particleindex %= this->particlecount;
            }
        }

        for (i = 0; i < this->karecount; i++)
        {
            this->kareet[i]->update(pos);
        }

        for (i = 0; i < this->particlecount; i++)
        {
            this->particlet[i]->update();
        }

        
        
        for (i = 0; i < this->saippuacount; i++)
        {
            Saippua &p = this->saippuat[i];
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
        for (i = 0; i < 4; i++)
        {
            if (!this->saippuat[saippuaindex].active)
            {
                this->saippuat[saippuaindex].init();
            }
            saippuaindex++;
            saippuaindex %= this->saippuacount;
        }
        
        
        
        this->timer->endStep();
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glLineWidth(2.0f);
    for (i = 0; i < this->karecount; i++)
    {
        kareet[i]->draw(pos, alpha);
    }
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (i = 0; i < this->pisaracount; i++)
    {
        pisarat[i]->draw(pos, alpha);
    }
    glEnd();

    //particlet
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("circle.jpg")->getID());

    Vector3 xr, yr, zr;
    Mathematics::antiRotate(&xr, &yr, &zr);
    glBegin(GL_QUADS);
    for (i = 0; i < this->particlecount; i++)
    {
        if (this->particlet[i]->active)
        {
            float size = 0.07f * (this->particlet[i]->life / this->particlet[i]->maxlife);
            glColor4f(this->particlet[i]->color.x, 
                      this->particlet[i]->color.y, 
                      this->particlet[i]->color.z, 
                      0.3f*alpha*this->particlet[i]->fade);

            Vector3 v1 = this->particlet[i]->position - xr * size - yr * size;
            Vector3 v2 = this->particlet[i]->position + xr * size - yr * size;
            Vector3 v3 = this->particlet[i]->position + xr * size + yr * size;
            Vector3 v4 = this->particlet[i]->position - xr * size + yr * size;

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


    //particlet
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("circle.jpg")->getID());
    glBegin(GL_QUADS);

    float particlefade = powf(sinf(Mathematics::calcPosFloat(pos, 0.0f, 0.1f)*3.141592f*0.5f), 3) * powf(sinf((1-Mathematics::calcPosFloat(pos, 0.98f, 1.00f))*3.141592f*0.5f), 2);
    
    
    
    //Mathematics::calcSaturate(pos, 0.03f, 0.97f, 4.6f);
    for (i = 0; i < this->saippuacount; i++)
    {
        Saippua &p = this->saippuat[i];
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


    filter.glow(8, 0.005f, 0.005f, 0.92f, -1.0f, 1.0f);
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


void Saippua::init()
{
    this->size = Mathematics::randBetween(0.04f, 0.1f);
    this->direction = Mathematics::randVectSphere()*2;

    this->position.x = Mathematics::randBetween(-7, 7);
    this->position.y = Mathematics::randBetween(0.5f, 4.0f);
    this->position.z = Mathematics::randBetween(-7, 7);
    this->direction.y /= 4.0f;

    this->direction.x += 4.8f;

    this->color = getKasariColor();
    this->energy = Mathematics::randBetween(0.05f, 0.4f);
    this->fade = Mathematics::randBetween(0.2f, 0.35f);

    this->maxenergy = this->energy;
    this->active = true;
}


Kareet::Kareet()
{	
    int i = 0;
    this->kareoffset = 0;
    this->karecount = 3000;
    this->pisaracount = 500;
    this->kareet = new Kare*[this->karecount];

    this->saippuacount = 1000;
    this->saippuat = new Saippua[this->saippuacount];
    this->saippuaindex = 0;

    for (i = 0; i < this->saippuacount; i++)
    {
        this->saippuat[i].active = false;
    }


    for (i = 0; i < this->karecount; i++)
    {
        this->kareet[i] = new Kare();
    }

    this->pisarat = new KarePisara*[this->pisaracount];

    for (i = 0; i < this->pisaracount; i++)
    {
        this->pisarat[i] = new KarePisara();
    }


    this->particlecount = 5000;
    this->particleindex = 0;
    this->particlet = new KareParticle*[this->particlecount];

    for (i = 0; i < this->particlecount; i++)
    {
        this->particlet[i] = new KareParticle();
    }

    this->timer = new FrameTimer(1000 / 60, 10);

}

Kareet::~Kareet()
{
    int i = 0;
    delete this->timer;

    for (i = 0; i < this->karecount; i++)
    {
        delete this->kareet[i];
    }
    delete [] this->kareet;

    for (i = 0; i < this->pisaracount; i++)
    {
        delete this->pisarat[i];
    }
    delete [] this->pisarat;
}


bool Kareet::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

