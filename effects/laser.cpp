#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Laser.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"


void Laser::draw()
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

Emitter::Emitter()
{
    int i = 0;
    this->pos = Mathematics::randVectSphere() * Mathematics::randBetween(0.2f, 3.0f);
    this->color = getKasariColor();

//    this->pos = Vector3(0, 0,0);

    this->color.normalize();

    this->beamcount = 5;
    this->beams = new Beam*[this->beamcount];

    float a = Mathematics::randBetween(0, 2 * 3.141592f);
    float b = Mathematics::randBetween(0, 2 * 3.141592f);

    float da = Mathematics::randBetween(0.001f, 0.0025f);
    float db = Mathematics::randBetween(0.001f, 0.0025f);

    float adelta = Mathematics::randBetween(0.02f, 0.06f);
    for (i = 0; i < this->beamcount; i++)
    {
        a += adelta;

        this->beams[i] = new Beam(this->color, a, b, da, db);
    }
}

Emitter::~Emitter()
{
    int i = 0;
    for (i = 0; i < this->beamcount; i++)
    {
        delete this->beams[i];
    }
    delete [] this->beams;
}

void Emitter::update(float pos, int reflectorcount, Reflector **reflectors)
{
    int i = 0;
    for (i = 0; i < this->beamcount; i++)
    {
        this->beams[i]->update(this->pos, pos, reflectorcount, reflectors);
    }
    
}

int Emitter::getBeamCount()
{
    return this->beamcount;
}

Beam **Emitter::getBeams()
{
    return this->beams;
}

void Emitter::draw(float pos, float alpha)
{
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);
    glColor4f(this->color.x, this->color.y, this->color.z, alpha * 0.7f);
    Primitives::wireCube(0.02f);
    glPopMatrix();
}


Reflector::Reflector()
{
    const float size = Mathematics::randBetween(0.15f, 0.4f);
    this->realposition = Mathematics::randVectSphere() * (0.3f + 5.0f * powf(Mathematics::randFloat(), 1.3f));
    this->v1 = Vector3(-size, -size, 0);
    this->v2 = Vector3( size, -size, 0);
    this->v3 = Vector3( size,  size, 0);

    this->boundingradiussquared = powf(this->v1.length(), 2.0f); //TODO?

    this->rotangle = Mathematics::randVectSphere() * 2 * 3.141592f;
    this->rotspeed = Mathematics::randVectSphere() * 0.01f;

    this->basenormal = (this->v3 - this->v1).crossProduct(this->v2 - this->v1);
    this->basenormal.normalize();

}

Reflector::~Reflector()
{
}

void Reflector::update(float pos)
{
    Matrix rot;
    rot.makeRotation(this->rotangle.x, this->rotangle.y, this->rotangle.z);

    this->hit = false;
    this->rotangle += this->rotspeed;

    const float scale = 8.0f;
    this->position = this->realposition * (scale-(scale-1)*sinf((1-Mathematics::calcPosFloat(pos, 0.96f, 0.99f))*
                                                                   Mathematics::calcPosFloat(pos, 0.1f, 0.75f)*3.141592f*0.5f));
    this->realv1 = this->position + this->v1 * rot;
    this->realv2 = this->position + this->v2 * rot;
    this->realv3 = this->position + this->v3 * rot;

    this->normal = this->basenormal * rot;

    this->fade = this->normal.dotProduct(Vector3(0.4f, 0.7f, 0.1f).normalize());
    this->edge1 = this->realv2 - this->realv1;
    this->edge2 = this->realv3 - this->realv1;
}

void Reflector::draw(float pos, float alpha)
{
    if (this->hit)
    {
        glColor4f(this->hitcolor.x, this->hitcolor.y, this->hitcolor.z, alpha);// * this->fade);
        glVertex3fv((float *)&this->realv1);
        glVertex3fv((float *)&this->realv2);
        glVertex3fv((float *)&this->realv3);

    }
    else
    {
        glColor4f(1, 1, 1, alpha * 0.2f * this->fade);
        glVertex3fv((float *)&this->realv1);
        glVertex3fv((float *)&this->realv2);
        glVertex3fv((float *)&this->realv3);
    }


}


Beam::Beam(Vector3 &color, float a, float b, float da, float db)
{

    this->a = a;
    this->b = b;
    this->da = da;
    this->db = db;

    this->dir = Mathematics::sphereToCartesian(1, a, b);
    this->color = color;

    this->maxlength = 5; //jos laittaa 8, niin kaatuu!!!!
    this->coords = new Vector3[this->maxlength];
    this->iteration = 0;

    this->realfade = Mathematics::randBetween(0.4f, 0.9f);
    this->fadephase = Mathematics::randFloat();
}

Beam::~Beam()
{
    delete [] this->coords;
}

void Beam::debug()
{
}


float Beam::intersect(Vector3 &point, Vector3 &dir, Reflector *reflector)
{
    const float EPSILON = 0.001f;
    float depth = -1.0f;

    float dx = point.x - reflector->position.x;
    float dy = point.y - reflector->position.y;
    float dz = point.z - reflector->position.z;
    //ensin bounding sphere

    float A = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    float B = 2 * (dir.x * dx + dir.y * dy + dir.z * dz);
    float C = dx * dx + dy * dy + dz * dz - reflector->boundingradiussquared;

    if (B*B - 4*A*C < 0.0f)
    {
        return depth;
    }

    //osui bounding sphereen, sitten testataan polygoni
    Vector3 &edge1 = reflector->edge1;
    Vector3 &edge2 = reflector->edge2;

    Vector3 pvec = dir.crossProduct(edge2);
    float det = edge1.dotProduct(pvec);

    const bool cull = false;
    
    if (cull)
    {
        if (det < EPSILON)
            return depth;

        Vector3 tvec = point - reflector->realv1;

        float u = tvec.dotProduct(pvec);
        if (u < 0.0f || u > det)
        {
            return depth;
        }
        Vector3 qvec = tvec.crossProduct(edge1);

        float v = dir.dotProduct(qvec);
        if (v < 0.0f || u + v > det)
        {
            return depth;
        }

        depth = edge2.dotProduct(qvec);
        float inv_det = 1.0f / det;
        depth *= inv_det;
    }
    else
    {
        if (det > - EPSILON && det < EPSILON)
        {
            return depth;
        }
        float inv_det = 1.0f / det;
        Vector3 tvec = point - reflector->realv1;

        float u = tvec.dotProduct(pvec) * inv_det;
        if (u < 0.0f || u > 1.0f)
        {
            return depth;
        }
        Vector3 qvec = tvec.crossProduct(edge1);
        float v = dir.dotProduct(qvec) * inv_det;

        if (v < 0.0f || u + v > 1.0f)
        {
            return depth;
        }
        depth = edge2.dotProduct(qvec) * inv_det;

    }
    return depth;
}

void Beam::trace(int reflectorcount, Reflector **reflectors)
{
    int i = 0;
    if (this->iteration >= this->maxlength)
    {
        return;
    }


    int closestIndex = -1;
    float nearest_t = 666666.0f;

    Vector3 startpoint = this->coords[this->iteration];

    //TODO: octree? 
    //TODO: bounding sphere? 

    for (i = 0; i < reflectorcount; i++)
    {
        if (i == this->lastIndex)
            continue;

        float t = this->intersect(startpoint, this->dir, reflectors[i]);

        //osuma
        if (t > 0.0f)
        {
            //l‰hin osuma toistaiseksi
            if (t < nearest_t)
            {
                closestIndex = i;
                nearest_t = t;
            }
        }
    }

    this->lastIndex = closestIndex;

    //osuma, jatketaan iterointia
    if (closestIndex != -1)
    {
        //merkataan osuma
        reflectors[this->lastIndex]->hit = true;
        reflectors[this->lastIndex]->hitcolor = this->color;
        //lasketaan seuraava piste

        this->coords[this->iteration + 1] = this->coords[this->iteration] + this->dir * nearest_t;

        this->iteration++;
        this->dir = this->dir + reflectors[closestIndex]->normal * 2;

        this->trace(reflectorcount, reflectors);
    }
    else
    {
        for (i = this->iteration + 1; i < this->maxlength; i++)
        {
            this->coords[i] = this->coords[i - 1] + this->dir * 560.0f; //TODO TODO TODO
        }
        return;
        this->iteration++;
    }
}

void Beam::update(Vector3 &startpos, float pos, int reflectorcount, Reflector **reflectors)
{
    int i = 0;
    this->coords[0] = startpos;

    this->a += this->da;
    this->b += this->db;

    this->dir = Mathematics::sphereToCartesian(1, a, b);
//    this->coords[1] = this->coords[0] + this->dir * 2; //TODO: remove

    this->fade = this->realfade * (0.8f + 0.2f * cosf(pos*51 + this->fadephase*3.141592f*2));
    this->iteration = 0;
    this->lastIndex = -1;
    this->trace(reflectorcount, reflectors);
}

void Beam::draw(float pos, float alpha)
{
    int i = 0;
    glColor4f(this->color.x, this->color.y, this->color.z, alpha * 0.7f * this->fade);

    glBegin(GL_LINE_STRIP);
    for (i = 0; i < this->maxlength - 1; i++)
    {
        glVertex3fv((float *)&this->coords[i]);
        glVertex3fv((float *)&this->coords[i + 1]);
    }
    glEnd();
}


void Laser::renderScene(float pos, float alpha)
{
    int i = 0;
    cam->useCamera(3);
/*
    glLoadIdentity();
    gluLookAt(0, -4, -7, 0, 0, 0, 0, 1, 0);
    glRotatef(pos*500, 0.4f, 0.7f, 0.2f);
*/

    this->timer->update();

    const float emittersfadein = Mathematics::calcPosFloat(pos, 0.0f, 0.2f);
    const int emittersdrawn = (int)(emittersfadein * this->emittercount);
    const float emittersfrac = emittersfadein * this->emittercount - emittersdrawn;
    
    while (this->timer->stepsLeft())
    {

        for (i = 0; i < this->reflectorcount; i++)
        {
            this->reflectors[i]->update(pos);
        }
        
        for (i = 0; i < emittersdrawn; i++)
        {
            //trace t‰‰ll‰
            this->emitters[i]->update(pos, this->reflectorcount, this->reflectors);
        }

        this->timer->endStep();
    }
/*

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, glExt.glowTexture256ID);
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor3f(0.7f, 0.7f, 0.7f);
    Primitives::texturedCube(100,1);


*/

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(3.0f);

    const float scenescale = 0.5f;

    glPushMatrix();
    glScalef(scenescale, scenescale, scenescale);


    //piirret‰‰n emitterit

    glDepthMask(0);
    for (i = 0; i < emittersdrawn; i++)
    {
        
        this->emitters[i]->draw(pos, alpha * ((i == emittersdrawn - 1) ? emittersfrac : 1));
    }

    float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
	float matriisi[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matriisi);	

	// Transponoidaan pyˆritysosa == inverse matriisi
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

	glEnable(GL_TEXTURE_CUBE_MAP_EXT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S); 
	glEnable(GL_TEXTURE_GEN_T); 
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);


	glMatrixMode(GL_TEXTURE);
	glPushMatrix();	
	glLoadMatrixf(matriisi); //inverse matriisi teksturematrixiin niin saadaan pyˆritys
	glMatrixMode(GL_MODELVIEW);

    this->cubemap->bind();
    //piirret‰‰n peilit
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(1);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < this->reflectorcount; i++)
    {
        this->reflectors[i]->draw(pos, alpha);
    }
    glEnd();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_CUBE_MAP_EXT);
	glDisable(GL_TEXTURE_GEN_S); 
	glDisable(GL_TEXTURE_GEN_T); 
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glLineWidth(1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < this->reflectorcount; i++)
    {
        this->reflectors[i]->draw(pos, alpha * 0.4f);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLineWidth(3.0f);
    
    glPopMatrix();
    filter.init(true);
    glPushMatrix();
    glScalef(scenescale, scenescale, scenescale);
    glDepthMask(0);
    //piirret‰‰n s‰teet
    for (i = 0; i < emittersdrawn; i++)
    {
        int count = this->emitters[i]->getBeamCount();
        Beam **beams = this->emitters[i]->getBeams();

        for (int j = 0; j < count; j++)
        {
            beams[j]->draw(pos, alpha * ((i == emittersdrawn - 1) ? emittersfrac : 1));
        }
    }
    glPopMatrix();
    glDepthMask(1);


    glDisable(GL_LINE_SMOOTH);
    filter.glow(7, 0.008f, 0.008f, 0.92f, -1.0f, 1.0f);
}




Laser::Laser()
{	
    int i = 0;
    this->emittercount = 20;
    this->reflectorcount = 450;

    this->emitters = new Emitter* [this->emittercount];
    this->reflectors = new Reflector* [this->reflectorcount];

    for (i = 0; i < this->emittercount; i++)
    {
        this->emitters[i] = new Emitter();
    }

    for (i = 0; i < this->reflectorcount; i++)
    {
        this->reflectors[i] = new Reflector();
    }

    this->timer = new FrameTimer(1000 / 60, 10);
    this->cubemap = new Cubemap();
    this->cubemap->setupStatic(dmsGetTexture("reflection.jpg"));
}

Laser::~Laser()
{
/*
    int i = 0; 

    for (i = 0; i < this->emittercount; i++)
    {
        delete this->emitters[i];
    }
    for (i = 0; i < this->emittercount; i++)
    {
        delete this->reflectors[i];
    }

    delete [] this->emitters;
    delete [] this->reflectors;

    delete this->timer;
*/
}


bool Laser::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}
