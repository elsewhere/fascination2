//-------------------------------------------------------
// Includes
//-------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "timer.hpp"
#include "globals.hpp"

//-------------------------------------------------------
// Staattiset julkiset j‰senet
//-------------------------------------------------------

bool Timer::createdFlag = false;
Timer *Timer::instance = NULL;

//-------------------------------------------------------
// Destructori, Constructorit ovat privoja jotta niit‰ ei 
// voisi kutsua
//-------------------------------------------------------


Timer::~Timer()
{
}

//-------------------------------------------------------
//	Public functions
//-------------------------------------------------------

Timer *Timer::create()
{	
	if(!createdFlag)
	{
		instance = new Timer;
		if(!instance)
		{
			throw "Timer::create(): Memory allocation error";
			return NULL;
		}

		createdFlag = true;

		dmsMsg("Timer::create(): Timer instance created\n");
	}
	else
	{		
		throw "One instance of class Log allready running";
		return NULL;
	}	

	return instance;
}

void Timer::init()
{
	LONGLONG freq;
	LONGLONG ticks;	

	//	High Resolution Timerin taajuutta ei voi muuttaa niin kauan
	//	kuin systeemi on p‰‰ll‰. Taajuus haetaan vain kerran.
		
	HRT = true;
	startTime = 0;
	addTime = 0.0f;
	frames = 0;
	lastTime = 0;	
	fps = 0;
	time = 0;	
			
	if( !QueryPerformanceFrequency( ( LARGE_INTEGER * )&freq ) )
	{				
		// Jos ep‰onnistui k‰ytet‰‰n MultimediaTimeria		
		HRT = false;		
		startTime = (float)timeGetTime();
	}
	else
	{		
		QueryPerformanceCounter( ( LARGE_INTEGER * )&ticks );
		startTime = ( float ) ticks;
		ticksPerSec = 1.0f / ( float )freq;
	}		
}

void Timer::update()
{						
	if( HRT )
	{
		LONGLONG ticks;

		// onnistuu
		QueryPerformanceCounter( ( LARGE_INTEGER * )&ticks );
		
		// jaetaan taajuudella jotta saadaan sekunnit
		//time = ((float)(__int64)ticks)/((float)(__int64)ticksPerSec);
		//time = ( ( float )ticks ) / ( ( float )ticksPerSec );
		time = ( ( float ) ticks - startTime ) * ticksPerSec;
	}
	else
	{
		// Jos ei ole HRT-ajastinta, k‰ytet‰‰n Multimedia timeria
		// vaatii WINMM.LIB:n				
		time = ( float )timeGetTime() - startTime;		
	}	
	
	deltaTime = ( time - lastTime );
	lastTime = time;
	
	frames++;		
	
	fps = ( float ) frames / time;
}

//-------------------------------------------------------
//	Getters
//-------------------------------------------------------

// Palauttaa ajan sekunteina
float Timer::getTime()
{	
	return time;
}

// Palauttaa ajan millisekunteina
float Timer::getTimeMs()
{	
	return time * 1000.0f;
}

float Timer::getFPS()
{
	return fps;
}

float Timer::getDeltaTime()
{
	return deltaTime;
}

//-------------------------------------------------------
//	Misc.
//-------------------------------------------------------

void Timer::addMs(float a)
{	
	addTime += a;
}

void Timer::release()
{
	createdFlag = false;

	if(instance)
	{
		delete instance;
		instance = NULL;
	}	

	dmsMsg("Timer::release(): Instance deleted\n");
}
