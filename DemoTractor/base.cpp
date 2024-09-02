//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "globals.hpp"
#include "base.hpp"
#include "timer.hpp"
#include "sound.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Externals
//--------------------------------------------------------------------------------------------

extern Timer *timer;
extern Song music;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

bool Base::init(unsigned long s, unsigned long e)
{
	active = false;
	startTime = s;
	endTime = e;
	time = 0;

	return true;
}

void Base::update(float t)
{
	time = t;
}

void Base::release()
{

}

bool Base::isActive()
{
	if(time >= startTime && time <= endTime)
	{
		active = true;
	}
	else
	{
		active = false;
	}

	return active;
}