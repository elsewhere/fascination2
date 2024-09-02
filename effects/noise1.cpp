#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Noise1.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

extern void bindRandomImage();

void Noise1::draw()
{
	const float pos = (time - startTime) / (endTime - startTime);
	float alpha = 1.0f;

	const float fadeinstart = this->startfade;
	const float fadeinstop = this->endfade;
	const float fadeoutstart = 0.90f;
	const float fadeoutstop = 1.0f;

	if (pos >= fadeinstart && pos <= fadeinstop)
		alpha *= (pos-fadeinstart) / (fadeinstop-fadeinstart);
	if (pos >= fadeoutstart && pos <= fadeoutstop)
		alpha *= 1-(pos-fadeoutstart) / (fadeoutstop-fadeoutstart);

    renderScene(pos, alpha);

}

void Noise1::renderScene(float pos, float alpha)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor4f(1,1,1,alpha*this->fade*(0.9f+0.1f*Mathematics::randFloat()));

    switch(rand()%3)
    {
        case 0: glBindTexture(GL_TEXTURE_2D, dmsGetTexture("noise1.jpg")->getID()); break;
        case 1: glBindTexture(GL_TEXTURE_2D, dmsGetTexture("noise2.jpg")->getID()); break;
        case 2: glBindTexture(GL_TEXTURE_2D, dmsGetTexture("noise3.jpg")->getID()); break;
    }

    Primitives::textureTaustaMove((rand()%2)==0?true:false, (rand()%2)==0?true:false, 
        Mathematics::randFloat(), Mathematics::randFloat());

/*
    shaders.displace->bind();

		glExt.glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(MY_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D,t->getID());
        bindRandomImage();

		glExt.glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);

        bindRandomImage();
        glExt.glActiveTextureARB(GL_TEXTURE0);
	    shaders.displace->setUniform1i("texunit0", 0);  
	    shaders.displace->setUniform1i("texunit1", 1);  
        shaders.displace->setUniform1f("displace_amount", 0.02f+0.04f*Mathematics::randFloat());
        Primitives::textureTaustaMove((rand()%2)==0?true:false, (rand()%2)==0?true:false, 
                                      Mathematics::randFloat(), Mathematics::randFloat());

        shaders.unbind();
*/
}

Noise1::Noise1(float startfade, float endfade, float fade)
{	
    this->startfade = startfade;
    this->endfade = endfade;
    this->fade = fade;
}

Noise1::~Noise1()
{
}

bool Noise1::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

