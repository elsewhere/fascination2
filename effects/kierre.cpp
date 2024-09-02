#ifdef _DEBUG
	#include <stdlib.h>
	#include "../mmgr.h"
#endif

#include <math.h>

#include "Kierre.hpp"
#include "../mathematics.hpp"
#include "../primitives.hpp"

void Kierre::draw()
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

void Kierre::renderScene(float pos, float alpha)
{
	cam->useCamera(0);
	
	this->timer->update();
	while (this->timer->stepsLeft())
	{
		this->timer->endStep();
		
	}
}




Kierre::Kierre()
{	
	this->timer = new FrameTimer(1000 / 60, 10);
}

Kierre::~Kierre()
{
	delete this->timer;
}


bool Kierre::init(unsigned long s, unsigned long e)
{
	startTime = s;
	endTime = e;
	return true;
}

