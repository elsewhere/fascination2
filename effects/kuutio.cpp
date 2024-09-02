#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Kuutio.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Kuutio::draw()
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
    const float flash = 1-sinf(Mathematics::calcPosFloat(pos, 0.0f, 0.04f)*3.141592f*0.5f);
    if (flash > 0.0001f)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        Primitives::flatTausta(1,1,1,flash);
    }

}

void Kuutionosa::draw(float pos, float alpha)
{
//    glColor4f(this->color.x* this->fade, this->color.y* this->fade, this->color.z* this->fade, alpha);
    float f = this->fade * alpha;
    glColor3f(this->color.x * f, this->color.y * f, this->color.z * f);

    //etuosa
    glVertex3fv((float *)&this->v5);
    glVertex3fv((float *)&this->v6);
    glVertex3fv((float *)&this->v7);
    glVertex3fv((float *)&this->v8);

    //yläosa
    glVertex3fv((float *)&this->v5);
    glVertex3fv((float *)&this->v1);
    glVertex3fv((float *)&this->v2);
    glVertex3fv((float *)&this->v6);

    //vasen
    glVertex3fv((float *)&this->v6);
    glVertex3fv((float *)&this->v2);
    glVertex3fv((float *)&this->v3);
    glVertex3fv((float *)&this->v7);
    //alaosa
    glVertex3fv((float *)&this->v8);
    glVertex3fv((float *)&this->v4);
    glVertex3fv((float *)&this->v3);
    glVertex3fv((float *)&this->v7);
    
    //oikea
    glVertex3fv((float *)&this->v5);
    glVertex3fv((float *)&this->v1);
    glVertex3fv((float *)&this->v4);
    glVertex3fv((float *)&this->v8);
}

void Kuutionosa::update()
{
    this->fade -= 0.003f;
    this->t += this->dt;

    this->v5 = this->v1 + this->suunta * t;
    this->v6 = this->v2 + this->suunta * t;
    this->v7 = this->v3 + this->suunta * t;
    this->v8 = this->v4 + this->suunta * t;

    Vector3 cullpos = (this->v1 + this->v2 + this->v3 + this->v4 + this->v5 + this->v6 + this->v7 + this->v8) * 1.0f / 8.0f;

    //etsitään keskustasta kauimmainen piste. Se on joko v1 tai v8

    float l1 = (this->v1 - cullpos).length();
    float l2 = (this->v8 - cullpos).length();

    float cullradius = (l2 > l1) ? l2 : l1;

    this->bs.set(cullpos, cullradius);
}


void Kuutionosa::init()
{
    this->fade = 0.01f + 0.6f*powf(Mathematics::randFloat(), 6);//Mathematics::randBetween(0.1f, 0.25f);
    this->dt = Mathematics::randBetween(-0.02f, 0.02f);

    this->t = Mathematics::randBetween(0.5f, 2.3f);
    this->color = getKasariColor();
    this->color.normalize();

    this->v5 = this->v1 + this->suunta * this->t;
    this->v6 = this->v2 + this->suunta * this->t;
    this->v7 = this->v3 + this->suunta * this->t;
    this->v8 = this->v4 + this->suunta * this->t;

}

void Kuutio::renderGeometry(float pos, float alpha, float sync)
{
    int i = 0;
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    cull->setup();
    glBegin(GL_QUADS);

    float c = 1-Mathematics::calcPosFloat(pos, 0.97f, 0.99f);

    for (i = 0; i < this->count; i++)
    {
        if (cull->testSphere(this->osat[i]->bs))
        {
            this->osat[i]->draw(pos, alpha*c);
        }
        else
        {
        }
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    float greetalpha = alpha * sinf( (1-Mathematics::calcPosFloat(pos, 0.9f, 0.96f)*3.141592f*0.5f));
    for (i = 0; i < this->greetcount; i++)
    {
        this->greets[i].draw(pos, greetalpha, 10 + 2*(1-sync));

    }
}
void Kuutio::renderScene(float pos, float alpha)
{
    int i = 0;
    static int beatcount = 0;

    static Vector3 kasaricolor;

    //päivitys

    static float scalevalue = 0.0f;

    float sync = beat->getValue();
    if (beat->getChanged())
    {
        beatcount++;
        if ((beatcount & 1) == 0)
        {
            kasaricolor = getKasariColor();
            kasaricolor += Vector3(0.2f, 0.2f, 0.2f);
            this->reinit();
            scalevalue = 1.0f;
        }
    }

    this->timer->update();
    while (this->timer->stepsLeft())
    {
        for (i = 0; i < this->count; i++)
        {
            this->osat[i]->update();
        }
        scalevalue -= 0.01f;
        if (scalevalue < 0.0f)
            scalevalue = 0.0f;
        this->timer->endStep();
        
    }

    static bool ekaframe = true;

    //cubemapit
    this->cubemap->startRendering();
    for (i = 0; i < 6; i++)
    {
        this->cubemap->setupRenderSide(i);
        this->renderGeometry(pos, alpha * 3.5f, scalevalue); //lisää alphaa tähän koska ei ole glow:ta
        this->cubemap->finishRenderSide(i);
    }
    this->cubemap->endRendering();

    
    //varsinainen skene


    cam->useCamera(0);

    filter.init(true);

    //tausta
    glPushMatrix();
    const float taustasize = 1.0f;
    glScalef(taustasize, taustasize, taustasize);
    this->renderGeometry(pos, alpha, scalevalue);
    glPopMatrix();

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

    float ambient[]= { kasaricolor.x, kasaricolor.y, kasaricolor.z, 1.0f};
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

    glRotatef(pos*1000, 0.4f+cosf(pos*43), 1.0f-pos*1.2f, pos*pos*0.7f - cosf(pos*25));

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();	
	glLoadMatrixf(matriisi); //inverse matriisi teksturematrixiin niin saadaan pyöritys
	glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0.4f*(0.5f*cosf(pos*31)+0.25f*cosf(pos*21)), 0, 0);
    float scaleout = 1-Mathematics::calcPosFloat(pos, 0.9f, 0.96f);
    glScalef(scaleout, scaleout, scaleout);
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

    this->mesh->renderVBO();

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
/*
    glPushMatrix();
    const float objektisize = 0.2f;
    glScalef(objektisize, objektisize, objektisize);
    this->renderGeometry(pos, alpha);
    glPopMatrix();
*/
}


void Kuutio::reinit()
{
    int i = 0;

    for (i = 0; i < this->count; i++)
    {
        this->osat[i]->init();//color = getKasariColor();
    }
    for (i = 0; i < this->greetcount; i++)
    {
        this->greets[i].init();
    }
}

int GREETINGSCOUNT = 45;

static const char *greetings[] = 
{
    "ADAPT",
    "ADAM BLAIR",
    "ALCATRAZ",
    "ANANASMURSKA",
    "ANDROMEDA",
    "ATLANTIS",
    "ASD",
    "BAUKNECHT",
    "BDSE",
    "BITFELLAS",
    "BOMBSQUAD",
    "BRAIN CONTROL",
    "CALODOX",
    "CONSPIRACY",
    "DEMARCHE",
    "DIVISION",
    "EVOFLASH",
    "FAKE THAT",
    "FARBRAUSCH",
    "FLO",
    "HEDELMAE",
    "JUMALAUTA",
    "KAKIARTS",
    "KEYBOARDERS",
    "LAG",
    "MATT CURRENT",
    "MERCURY",
    "MFX",
    "MOONHAZARD",
    "NUANCE",
    "ORB",
    "OUTBREAK",
    "PLASTIC",
    "RICARDO TUBBS",
    "SONNY CROCKETT",
    "STILL",
    "STRAVAGANZA",
    "SYNESTHETICS",
    "TRILOBIT",
    "UMLAUT DESIGN",
    "UNKNOWN ARTISTS",
    "VANTAGE",
    "VOVOID",
    "WAMMA",
    "XPLSV",
};

void Greet::init()
{
    this->point = Mathematics::randVectSphere() * 10;

    int t = rand() % 3;
    switch(t)
    {
        case 0: this->orientation = WRITER_DIRECTION_POSITIVE_Z; break;
        case 1: this->orientation = WRITER_DIRECTION_POSITIVE_Y; break;
        case 2: this->orientation = WRITER_DIRECTION_POSITIVE_X; break;
    }
    this->textIndex = rand() % GREETINGSCOUNT;
    do
    {
        this->color = getKasariColor();
    } while (this->color.length() < 0.9f);

    this->fade = Mathematics::randBetween(0.7f, 0.86f);
}

void Greet::draw(float pos, float alpha, float scale)
{
    glColor4f(this->color.x, this->color.y, this->color.z, this->fade * alpha);
    writer->drawString3D(greetings[this->textIndex], this->point, scale, alpha, this->orientation);
}


Kuutio::Kuutio()
{
    int x, y;
    this->xres = 25;
    this->yres = 25;

    this->count = this->xres * this->yres * 6; //6 tahkoa
    this->greetcount = 350;
    this->greets = new Greet[this->greetcount];

    const int diff = this->xres * this->yres;

    this->osat = new Kuutionosa*[this->count];

    for (y = 0; y < this->yres; y++)
    {
        for (x = 0; x < this->xres; x++)
        {
            int offset = x + y * this->xres;

            this->osat[offset] = new Kuutionosa();
            this->osat[offset + diff] = new Kuutionosa();
            this->osat[offset + diff * 2] = new Kuutionosa();
            this->osat[offset + diff * 3] = new Kuutionosa();
            this->osat[offset + diff * 4] = new Kuutionosa();
            this->osat[offset + diff * 5] = new Kuutionosa();


            float xt = x / (float)this->xres - 0.5f;
            float yt = y / (float)this->yres - 0.5f;

            float xstep = 1.0f / (float)this->xres;
            float ystep = 1.0f / (float)this->yres;

            xstep *= Mathematics::randBetween(0.96f, 0.98f);
            ystep *= Mathematics::randBetween(0.96f, 0.98f);

            xt += 0.001f;
            yt += 0.001f;

            const float s = 20.0f;

            Kuutionosa *p1 = this->osat[offset];
            Kuutionosa *p2 = this->osat[offset + diff];
            Kuutionosa *p3 = this->osat[offset + diff * 2];
            Kuutionosa *p4 = this->osat[offset + diff * 3];
            Kuutionosa *p5 = this->osat[offset + diff * 4];
            Kuutionosa *p6 = this->osat[offset + diff * 5];

            const float l = 0.6f;

            p1->v1 = Vector3(xt, -l, yt) * s;
            p1->v2 = Vector3(xt + xstep, -l, yt) * s;
            p1->v3 = Vector3(xt + xstep, -l, yt + ystep) * s; 
            p1->v4 = Vector3(xt, -l, yt + ystep) * s;
            p1->suunta = Vector3(0, 1, 0);

            p2->v1 = Vector3(xt,  l, yt) * s;
            p2->v2 = Vector3(xt + xstep,  l, yt) * s;
            p2->v3 = Vector3(xt + xstep,  l, yt + ystep) * s; 
            p2->v4 = Vector3(xt,  l, yt + ystep) * s;
            p2->suunta = Vector3(0, -1, 0);

            p3->v1 = Vector3(l, xt, yt) * s;
            p3->v2 = Vector3(l, xt + xstep, yt) * s;
            p3->v3 = Vector3(l, xt + xstep, yt + ystep) * s; 
            p3->v4 = Vector3(l, xt, yt + ystep) * s;
            p3->suunta = Vector3(-1, 0, 0);

            p4->v1 = Vector3(-l, xt, yt) * s;
            p4->v2 = Vector3(-l, xt + xstep, yt) * s;
            p4->v3 = Vector3(-l, xt + xstep, yt + ystep) * s; 
            p4->v4 = Vector3(-l, xt, yt + ystep) * s;
            p4->suunta = Vector3(1, 0, 0);

            p5->v1 = Vector3(xt, yt, l) * s;
            p5->v2 = Vector3(xt + xstep, yt, l) * s;
            p5->v3 = Vector3(xt + xstep, yt + ystep, l) * s; 
            p5->v4 = Vector3(xt, yt + ystep, l) * s;
            p5->suunta = Vector3(0, 0, -1);

            p6->v1 = Vector3(xt, yt, -l) * s;
            p6->v2 = Vector3(xt + xstep, yt, -l) * s;
            p6->v3 = Vector3(xt + xstep, yt + ystep, -l) * s; 
            p6->v4 = Vector3(xt, yt + ystep, -l) * s;
            p6->suunta = Vector3(0, 0, 1);

        }
    }


    this->reinit();

    this->timer = new FrameTimer(1000 / 60, 10);
    this->cubemap = new Cubemap();
    this->cubemap->setupDynamic(512);

    this->mesh = TMeshFactory::importT3D("ball.t3d");
    this->mesh->scale(2.1f);
    this->mesh->removeDuplicateVertices(0.001f);
    this->mesh->createVBO(MESH_VERTEX_BIT | MESH_TEXTURE_BIT | MESH_NORMAL_BIT);

}

Kuutio::~Kuutio()
{
    int i = 0;
    for (i = 0; i < this->count; i++)
    {
        delete this->osat[i];
    }
    delete [] this->osat;
    
}


bool Kuutio::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

