#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "FrustumTesti.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void FrustumTesti::draw()
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

    filter.init(true);
	renderScene(pos, alpha);
    filter.glow(4, 0.007f, 0.007f, 0.901f, -1.0f, 1.0f);
}

void FrustumTesti::renderScene(float pos, float alpha)
{
    cam->useCamera(0);

    this->timer->update();
    while (this->timer->stepsLeft())
    {


        this->timer->endStep();
    }

    
    glBindTexture(GL_TEXTURE_2D, dmsGetTexture("texture_03.jpg")->getID());

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glColor4f(1,1,1,1);

    cull->setup();
    for (int i = 0; i < this->count; i++)
    {
        if (cull->testSphere(this->pallot[i].pos, this->pallot[i].r))
        {
            glPushMatrix();
            glTranslatef(this->pallot[i].pos.x, this->pallot[i].pos.y, this->pallot[i].pos.z);
            glScalef(this->pallot[i].r, this->pallot[i].r, this->pallot[i].r);

            TVertex *v = this->pallomesh->getVertices();
            int vc = this->pallomesh->getVertexCount();
            TFace *f = this->pallomesh->getFaces();
            int fc = this->pallomesh->getFaceCount();


            glBegin(GL_TRIANGLES);
            for (int j = 0; j < fc; j++)
            {
                TVertex &v1 = v[f[j].a];
                TVertex &v2 = v[f[j].b];
                TVertex &v3 = v[f[j].c];

                glTexCoord2fv((float *)&v1.uv);
                glVertex3fv((float *)&v1.position);
                glTexCoord2fv((float *)&v2.uv);
                glVertex3fv((float *)&v2.position);
                glTexCoord2fv((float *)&v3.uv);
                glVertex3fv((float *)&v3.position);
            }

            glEnd();

//            this->pallomesh->renderVBO();
            glPopMatrix();
        }

    }
}




FrustumTesti::FrustumTesti()
{	
    this->timer = new FrameTimer(1000 / 60, 10);

    this->count = 5000;

    this->pallot = new TestiPallo[this->count];
    for (int i = 0; i < this->count; i++)
    {
        this->pallot[i].r = Mathematics::randBetween(0.03f, 0.2f);
        this->pallot[i].pos = Mathematics::randVectSphere() * Mathematics::randBetween(2.0f, 16.0f);
    }

    this->pallomesh = TMeshFactory::createSphere(1.0f, 16, 16, 1.0f);
    this->pallomesh->createVBO(MESH_VERTEX_BIT | MESH_TEXTURE_BIT | MESH_NORMAL_BIT);
}

FrustumTesti::~FrustumTesti()
{
    delete this->timer;
}


bool FrustumTesti::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

