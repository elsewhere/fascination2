#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Tanssilattia.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Tanssilattia::draw()
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
	renderScene(pos, alpha);
}

void Lattianpala::draw(float pos, float alpha)
{
    float alphamod = 0.0f;
    if (pos < 0.5f)
    {
        alphamod = Mathematics::calcPosFloat(pos, this->st1, this->et1);
    }
    else
    {
        alphamod = 1 - Mathematics::calcPosFloat(pos, this->st2, this->et2);

    }
    float f = alpha * this->fade * this->basefade * alphamod;
    glColor4f(this->color.x, this->color.y, this->color.z, f);
    glVertex3fv((float *)&this->v1);
    glVertex3fv((float *)&this->v2);
    glVertex3fv((float *)&this->v3);
    glVertex3fv((float *)&this->v4);

    if (this->special)
    {
        const float keila = 1.33f;
        const float korkeus = 5.0f;
        const float keilaf = 0.8f;

        Vector3 v5 = this->v1 * keila; 
        Vector3 v6 = this->v2 * keila; 
        Vector3 v7 = this->v3 * keila; 
        Vector3 v8 = this->v4 * keila; 

        v5.y = korkeus;
        v6.y = korkeus;
        v7.y = korkeus;
        v8.y = korkeus;


        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v1);
        glVertex3fv((float *)&v2);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v6);
        glVertex3fv((float *)&v5);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v2);
        glVertex3fv((float *)&v3);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v7);
        glVertex3fv((float *)&v6);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v3);
        glVertex3fv((float *)&v4);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v8);
        glVertex3fv((float *)&v7);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v4);
        glVertex3fv((float *)&v1);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v5);
        glVertex3fv((float *)&v8);
        /*

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v1);
        glVertex3fv((float *)&v2);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v6);
        glVertex3fv((float *)&v5);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v2);
        glVertex3fv((float *)&v3);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v7);
        glVertex3fv((float *)&v6);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v3);
        glVertex3fv((float *)&v4);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v8);
        glVertex3fv((float *)&v7);

        glColor4f(this->color.x, this->color.y, this->color.z, f * keilaf);
        glVertex3fv((float *)&v4);
        glVertex3fv((float *)&v1);
        glColor4f(this->color.x, this->color.y, this->color.z, 0);
        glVertex3fv((float *)&v5);
        glVertex3fv((float *)&v8);

        */
    }
}

void Lattianpala::update()
{

}

void Lattianpala::init(float pos)
{
    this->color = getKasariColor();
    this->fade = 0.02f + 0.9f * powf(Mathematics::randFloat(), 6); //Mathematics::randBetween(0.1f, 0.5f);

    if (pos > 0.2f || pos < 0.0001f)
    {
        this->special = (rand()%15) == 0; 
    }
    else
    {
        this->special = false;
    }
}

void Tanssilattia::renderScene(float pos, float alpha)
{
    int i = 0;

   
    this->cubemap->startRendering();
    for (i = 0; i < 6; i++)
    {
        this->cubemap->setupRenderSide(i);
        this->renderGeometry(pos, alpha * 3.5f); //lisää alphaa tähän koska ei ole glow:ta
        this->cubemap->finishRenderSide(i);
    }
    this->cubemap->endRendering();



    cam->useCamera(0);

    static int beatcount = 0;

    float sync = beat->getValue();
    if (beat->getChanged())
    {
        beatcount++;

        if (beatcount == 0 || beatcount == 4 || beatcount == 8 || beatcount == 10 || beatcount == 12 || 
            beatcount == 16 || beatcount == 20 || beatcount == 24 || beatcount == 26 || beatcount == 28)
        {
            this->reinit(pos);
        }
/*
        if ((beatcount & 1) == 0)
        {
            this->reinit(pos);
        }
*/
    }

    static int particleindex = 0;

    this->timer->update();
    while (this->timer->stepsLeft())
    {
        for (i = 0; i < this->count; i++)
        {
            this->palat[i]->update();
        }

        for (i = 0; i < this->particlecount; i++)
        {
            LattiaParticle &p = this->particles[i];
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
        for (i = 0; i < 20; i++)
        {
            if (!this->particles[particleindex].active)
            {
                this->particles[particleindex].init();
            }
            particleindex++;
            particleindex %= this->particlecount;
        }
        this->timer->endStep();
    }


    filter.init(true);
/*
    if (GetAsyncKeyState(VK_SPACE))
    {
        dmsMsg("time = %d beatcount = %d\n", dmsGetModulePosition, beatcount);
    }
*/

    //lattia
    renderGeometry(pos, alpha);



    //particlet
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("circle.jpg")->getID());
    Vector3 xr, yr, zr;
    Mathematics::antiRotate(&xr, &yr, &zr);
    glBegin(GL_QUADS);

    float particlefade = Mathematics::calcSaturate(pos, 0.03f, 0.97f, 4.6f);
    for (i = 0; i < this->particlecount; i++)
    {
        LattiaParticle &p = this->particles[i];
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


    //meshi
    	float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
	float matriisi[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matriisi);	

	// Transponoidaan pyöritysosa == inverse matriisi
	a1 = matriisi[ 0];
	a2 = matriisi[ 1];
	a3 = matriisi[ 2];
	a4 = matriisi[ 3];
	b1 = matriisi[ 4];
	b2 = matriisi[ 5];
	b3 = matriisi[ 6];
	b4 = matriisi[ 7];
	c1 = matriisi[ 8];
	c2 = matriisi[ 9];
	c3 = matriisi[10];
	c4 = matriisi[11];
	d1 = matriisi[12];
	d2 = matriisi[13];
	d3 = matriisi[14];
	d4 = matriisi[15];

	matriisi[ 0] = a1;
	matriisi[ 1] = b1;
	matriisi[ 2] = c1;
	matriisi[ 3] = d1;
	matriisi[ 4] = a2;
	matriisi[ 5] = b2;
	matriisi[ 6] = c2;
	matriisi[ 7] = d2;
	matriisi[ 8] = a3;
	matriisi[ 9] = b3;
	matriisi[10] = c3;
	matriisi[11] = d3;
	matriisi[12] = a4;
	matriisi[13] = b4;
	matriisi[14] = c4;
	matriisi[15] = d4;
  

    const float valospeed = 3.0f;
    Vector3 valopos = Vector3(cosf(pos*11*valospeed) - sinf(pos*17*valospeed)*0.5f, 
                              cosf(pos*9*valospeed) * 1.2f,
                              0.7f + cosf(pos*21*valospeed)) * 10;

    float ambient[]= { 1,1,1, 1.0f};
	float diffuse[]={1.0f, 1.0f, 1.0f, 1.0f};
	float position[]={ valopos.x, valopos.y, valopos.z, 0.0f};
	float specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glPushMatrix();


	glMatrixMode(GL_TEXTURE);
	glPushMatrix();	
	glLoadMatrixf(matriisi); //inverse matriisi teksturematrixiin niin saadaan pyöritys
	glMatrixMode(GL_MODELVIEW);

    //objekti
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_CUBE_MAP_EXT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S); 
	glEnable(GL_TEXTURE_GEN_T); 
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

    
    glPushMatrix();
    const float s = sinf(3.141592f*0.5f*Mathematics::calcPosFloat(pos, 0.0f, 0.2f));
    glTranslatef(0, 3*powf(sinf(3.141592f*0.5f*Mathematics::calcPosFloat(pos, 0.92f, 0.99f)), 2.0f), 0);
    glScalef(s, s, s);
    glRotatef(pos*1000, 0.4f+cosf(pos*43), 1.0f-pos*1.2f, pos*pos*0.7f - cosf(pos*25));
    this->mesh->renderVBO(MESH_VERTEX_BIT | MESH_NORMAL_BIT);
    glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glDisable(GL_TEXTURE_CUBE_MAP_EXT);
	glDisable(GL_TEXTURE_GEN_S); 
	glDisable(GL_TEXTURE_GEN_T); 
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

    filter.glow(7, 0.009f, 0.009f, 0.92f, -1.0f, 1.0f);

}

void Tanssilattia::renderGeometry(float pos, float alpha)
{
    int i = 0;
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);

//    const int dc = (int)(this->count * (1-Mathematics::calcPosFloat(pos, 0.97f, 0.99f)) * Mathematics::calcPosCos(pos, 0.0f, 0.1f));
    for (i = 0; i < this->count; i++)
    {
        this->palat[i]->draw(pos, alpha);
    }
    glEnd();

}

void Tanssilattia::reinit(float pos)
{
    int x = 0;
    int y = 0;

    for (y = 0; y < this->yres; y++)
    {
        for (x = 0; x < this->xres; x++)
        {
            int offset = x + y * this->xres;
            this->palat[offset]->init(pos);//color = getKasariColor();
        }
    }
}

void LattiaParticle::init()
{
    this->size = Mathematics::randBetween(0.04f, 0.1f);
    this->direction = Mathematics::randVectSphere()*2;

    this->position.x = Mathematics::randBetween(-7, 7);
    this->position.y = Mathematics::randBetween(-3.0f, 4.0f);
    this->position.z = Mathematics::randBetween(-7, 7);
    this->direction.y /= 4.0f;

    this->direction.x += 4.8f;

    this->color = getKasariColor();
    this->energy = Mathematics::randBetween(0.05f, 0.4f);
    this->fade = Mathematics::randBetween(0.2f, 0.35f);

    this->maxenergy = this->energy;
    this->active = true;
}

Tanssilattia::Tanssilattia()
{
    int i = 0;
    int x, y;
    this->xres = 50;
    this->yres = 50;

    this->particlecount = 700;
    this->particles = new LattiaParticle[this->particlecount];
    for (i = 0; i < this->particlecount; i++)
    {
        this->particles[i].active = false;
    }



    this->count = this->xres * this->yres;
    this->palat = new Lattianpala*[this->count];


    for (y = 0; y < this->yres; y++)
    {
        for (x = 0; x < this->xres; x++)
        {
            int offset = x + y * this->xres;
            this->palat[offset] = new Lattianpala();

            Lattianpala *p = this->palat[offset];

            float xt = x / (float)this->xres - 0.5f;
            float yt = y / (float)this->yres - 0.5f;

            float xstep = 1.0f / (float)this->xres;
            float ystep = 1.0f / (float)this->yres;

            const float s = 20.0f;

            p->v1 = Vector3(xt, 0, yt) * s;
            p->v2 = Vector3(xt + xstep, 0, yt) * s;
            p->v3 = Vector3(xt + xstep, 0, yt + ystep) * s; 
            p->v4 = Vector3(xt, 0, yt + ystep) * s;

            const float korkeus = -3.0f;
            p->v1.y = korkeus;
            p->v2.y = korkeus;
            p->v3.y = korkeus;
            p->v4.y = korkeus;

            float l = sqrt(xt * xt + yt * yt);

            if (l > 0.5f)
            {
                p->basefade = 0.0f;
            }
            else
            {
                p->basefade  = (0.5f - l) * 2;
            }

            p->st1 = Mathematics::randBetween(0.01f, 0.1f);
            p->et1 = p->st1 + Mathematics::randBetween(0.02f, 0.04f);

            p->st2 = Mathematics::randBetween(0.93f, 0.95f);
            p->et2 = p->st2 + Mathematics::randBetween(0.02f, 0.05f);
        }
    }
    this->reinit(0.0f);
    this->timer = new FrameTimer(1000 / 60, 10);

    this->cubemap = new Cubemap();
    this->cubemap->setupDynamic(512);

    this->mesh = TMeshFactory::importT3D("ball.t3d");
    this->mesh->scale(1.5f);
    this->mesh->createVBO(MESH_VERTEX_BIT | MESH_NORMAL_BIT);
}

Tanssilattia::~Tanssilattia()
{
    int i = 0;
    for (i = 0; i < this->count; i++)
    {
        delete this->palat[i];
    }
    delete [] this->palat;
    
}


bool Tanssilattia::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

