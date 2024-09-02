#ifndef _OPENGL_HPP_
#define _OPENGL_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "glext.h"
#include "wglext.h"
#include "log.hpp"
#include "enums.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  OpenGL Window class
//--------------------------------------------------------------------------------------------

	class GLWindow
	{	
		friend class GLSystem;

		public:

			GLWindow();
			~GLWindow();

			bool init();		
			bool kill();
			
			bool createWindow();
			bool createWindow(int w, int h, int b, bool screen);

			bool getFullscreen();
			unsigned int getWidth();
			unsigned int getHeight();
			HWND getHandle();
			HINSTANCE getInstance();
			HDC getHDC();

			void setPerspective2D();
			void setPerspective2D(int w, int h);
			void setPerspective3D();
			void setWidth(unsigned int w);
			void setHeight(unsigned int h);
			void setBpp(unsigned int b);
			void setZbpp(unsigned int z);
			void setSbpp(unsigned int s);
			void setFullscreen(bool f);
			void setTitle(char *t);
			void setClassName(char *c);

			friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		private:

		// Muuttujat jotka osoittavat laajennus funkkareihin //
		///////////////////////////////////////////////////////
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
		PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;	

		// Muut muuttujat									 //
		///////////////////////////////////////////////////////
		unsigned int bpp, zbpp, sbpp;		// Bit Depths for buffers
		unsigned int width, height;			// Window witdth and height
		bool fullscreen;					// Fullscreen flag
		char *title;						// Window name
		char *className;					// Class name for registeration

		bool verticalSyncFlag;				// Flag for Vertical retrace
		int verticalSync;					// Holds the value of vertical retrace (on/off)

		HWND hwnd;
		HINSTANCE hinstance;
		HDC hdc;
		HGLRC hrc;
	};

//--------------------------------------------------------------------------------------------
//  OpenGL System class
//--------------------------------------------------------------------------------------------

	class GLSystem
	{
		friend class GLWindow;

		public:

			GLSystem();
			~GLSystem();

			bool init(int w, int h);
			void resize(int w, int h);
			void checkState();
			void myEnable(int c);
			void myDisable(int c);
			void myBlendFunc(int src, int dst);

			// Getters
			int getIndex();
			int getPrevSrc();
			int getPrevDst();

			// Setters
			void setFov(float fov);
			void setPrevSrc(int c);
			void setPrevDst(int c);
			void setClearColor(float r, float g, float b, float a);

		private:		

			int width, height;
			int nIndex;
			int prev_src, prev_dst;
	};

}

#endif