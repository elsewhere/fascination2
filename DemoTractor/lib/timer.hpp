#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <windows.h>

//-------------------------------------------------------
//
//  Singleton Timeri-luokka
//  
//  Käyttää oletuksena High Resolution Timeria. Jos tätä ei 
//  löydy käytetään MultimediaTimeria (vaatii winmm.lib:n)
//
//	
//
//-------------------------------------------------------


class Timer
{
	public:

		~Timer();

		static Timer *create();
		void init();
		void update();
		float getTime();
		float getTimeMs();
		float getFPS();
		float getDeltaTime();

		void addMs(float a);
		void release();

	private:

		static bool createdFlag;
		static Timer *instance;
		
		bool HRT;
		UINT64 ticksPerSec;
		float startTime;
		float time, deltaTime;
		float lastTime, currentTime, fps;
		float addTime;
		unsigned int frames;

		Timer() {}
		Timer(const Timer &) {}
		Timer& operator = (const Timer &) {}
};

#endif