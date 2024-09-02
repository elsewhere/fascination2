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
			bool createWindow(int w, int h, int b, bool screen, bool onTop, int fsaa);

			bool getFullscreen();
			bool getActive();
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
			void setActive(bool a);

			friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			void setKey(int i, bool b);
			bool getKey(int i);

			bool	leftMouse;
			bool	rightMouse;
			float	mouseX, mouseY;


		private:

		// Muuttujat jotka osoittavat laajennus funkkareihin //
		///////////////////////////////////////////////////////
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
		PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;	

		// Muut muuttujat									 //
		///////////////////////////////////////////////////////
		unsigned int bpp, zbpp, sbpp;		// Bit Depths for buffers
		unsigned int width, height;			// Window width and height
		bool fullscreen;					// Fullscreen flag
		char *title;						// Window name
		char *className;					// Class name for registeration

		int fsaa;							// Fullscreenalias multisamples
		bool onTop;							// Always-on-top 
		bool active;
		bool verticalSyncFlag;				// Flag for Vertical retrace
		int verticalSync;					// Holds the value of vertical retrace (on/off)

		bool	keys[256];

		HWND hwnd;
		HINSTANCE hinstance;
		HDC hdc;
		HGLRC hrc;

		// Nämä funktiot eivät näy muille
		///////////////////////////////////////////////////////
		int fetchFSAAMode(HDC hdc,int suggestedFormat, PIXELFORMATDESCRIPTOR p, int requestedmultisamples);
		bool extensionExist(const char *extension);


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

			bool init(int w, int h, int aspectratio=0);
			void resize(int w, int h);
			void loadOMeter(int current, int max);
			void resetViewport();
									
			// Setters
			void setFov(float fov);			
			void setPerspective(float fov, float zNear, float zFar);
			void setClearColor(float r, float g, float b, float a);					

		private:		

			float zNear, zFar, fov;

			int width, height;			

			int aspectratio;
	};

}

#endif
