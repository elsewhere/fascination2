#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

//-------------------------------------------------------
//	Headerit
//-------------------------------------------------------

#include <windows.h>

//-------------------------------------------------------
// Window editorissa CTRL+D ja CTRL+click 
// vaihtaa tab orderia
//-------------------------------------------------------

//-------------------------------------------------------
// Config-luokka
//
// Hoitaa demon conffaamisen.
//-------------------------------------------------------

class Config
{		
	public:
		
		Config();
		~Config();

		bool run();
		
		// getterit
		int getScreenX();
		int getScreenY();
		int getBpp();		
		int getGamma();
		int getFsaa();
		int getAspectRatio();
		bool getFullscreen();
		bool getSound();
		bool getVsync();
		bool getOnTop();
		bool getAnaglyphic();
		bool getRunFlag();
		
		static CALLBACK ConfigProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
		static int screenX, screenY, bpp, gamma, fsaa, aspectratio;
		static bool fullscreen, sound, vsync, runFlag, anaglyphic, alwaysOnTop;

	private: 

};

#endif