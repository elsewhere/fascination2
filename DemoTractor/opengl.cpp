//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include "opengl.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

GLWindow::GLWindow()
{
	hwnd = NULL;
	hinstance = NULL;
	hdc = NULL;
	hrc = NULL;

	// Default setup
	width = 640;
	height = 480;
	bpp = 32;
	zbpp = 16;
	sbpp = 8;
	fullscreen = false;
	active = true;
	title = "DemoTractor";
	className = "DemoTractorGL";
	onTop = false;
	fsaa = 0;

	wglSwapIntervalEXT = NULL;
	wglGetSwapIntervalEXT = NULL;

	verticalSyncFlag = false;
	verticalSync = 0;
}

GLWindow::~GLWindow()
{
	kill();
}

bool GLWindow::createWindow()
{
	WNDCLASSEX wc;
	DWORD eStyle;
	DWORD style;
	RECT rect;	
	static PIXELFORMATDESCRIPTOR p;	
	char buf[256];
	int format;
	//int xpos = 200;
	//int ypos = 200;
	int xpos = 0;
	int ypos = 0;

	rect.left = (long)0;
	rect.right = (long)width;
	rect.top = (long)0;
	rect.bottom = (long)height;
	
	hinstance = GetModuleHandle(NULL);	

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;	
	wc.hInstance = hinstance;
	//wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if(!RegisterClassEx(&wc))
	{
		sprintf(buf,"GLWindow::createWindow(): %s luokan rekister�inti ep�onnistui!\n",className);
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST );
		return false;
	}	
	
	ZeroMemory(&p, sizeof(p));
	p.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	p.nVersion = 1;
	p.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	p.iPixelType = PFD_TYPE_RGBA;
	p.cColorBits = bpp;
	p.cDepthBits = zbpp;
	p.iLayerType = PFD_MAIN_PLANE;
	p.cStencilBits = sbpp;

	if(fullscreen)
	{
		DEVMODE dmScreenSettings; // device mode

		ZeroMemory(&dmScreenSettings, sizeof(DEVMODE)); // nollataan 
		dmScreenSettings.dmSize = sizeof(DEVMODE);
		dmScreenSettings.dmPelsWidth = width;		// ruudun koko
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bpp;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// kokeillaan josko wintoosa suostuisi vaihtamaan moodia:
		// CDS_FULLSCREEN: ei start bar:a 
		if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			fullscreen = false;			
		}		

		eStyle = WS_EX_APPWINDOW | WS_EX_TOPMOST;
		style = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;		
		ShowCursor(FALSE);

	}
	else
	{
		eStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_SYSMENU;
		// | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
	}	

	if( fullscreen )
	{
		xpos = 0;
		ypos = 0;
	}

	AdjustWindowRectEx(&rect, style, FALSE, eStyle);
	hwnd = CreateWindowEx(eStyle, 
						  className,
						  title,
						  style,
						  xpos,
						  ypos,
						  rect.right - rect.left,
						  rect.bottom - rect.top,
						  HWND_DESKTOP,
						  NULL,
						  hinstance,
						  NULL);

	// Korjataan ruudun kokoa jos ollaan ikkunoidussa tilassa
	if(!fullscreen)
	{
		height = rect.bottom - rect.top + 5;
	}

	if(!hwnd)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda ikkunaa!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST );
		return false;
	}

	hdc = GetDC(hwnd);
	if(!hdc)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda device contexia!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		return false;
	}

	format = ChoosePixelFormat(hdc, &p);
	if(!format)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): haettua resoluutiota ei tueta!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		return false;
	}
	
	if(!SetPixelFormat(hdc, format, &p))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut asettaa haettua resoa!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}
	
	if(!(hrc = wglCreateContext(hdc)))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda GL-device contexia!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	if(!wglMakeCurrent(hdc, hrc))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut aktivoida rendreing contexia\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;	
	}

	// Vertical Syncin poisto alkaa. Tapahtuu WGL-laajennuksen avulla
	
	// haetaan funkkarit
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");

	// verticalSyncFlag = false jos laajennusten haku ei onnistunut.
	// Ohjelma ei kuitenkaan kaadu t�h�n
	if (!wglSwapIntervalEXT || !wglGetSwapIntervalEXT) 
	{
		verticalSyncFlag = false;
	}
	else
	{
		// ...muulloin haetaan V-syncin arvo ennen kuin ajetaan ohjelma.
		verticalSync = wglGetSwapIntervalEXT();

		// Nyt voi ottaa V-Syncin turvallisesti pois p��lt�
		wglSwapIntervalEXT(1);
	}
		
	ShowWindow(hwnd, SW_SHOW);	
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	return true;
}

// width, height, bpp, fullscreen, alwaysontop, fsaa-samples (0,2,4,6,8)
bool GLWindow::createWindow(int w, int h, int b, bool screen, bool onTop, int fsaa)
{
	WNDCLASSEX wc;
	DWORD eStyle;
	DWORD style;
	RECT rect;	
	static PIXELFORMATDESCRIPTOR p;	
	char buf[256];
	int format;
	int xpos = 0;
	int ypos = 0;

	width = w;
	height = h;
	bpp = b;
	fullscreen = screen;
	this->onTop = onTop;

	rect.left = (long)0;
	rect.right = (long)width;
	rect.top = (long)0;
	rect.bottom = (long)height;

	hinstance = GetModuleHandle(NULL);	

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;	
	wc.hInstance = hinstance;
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
	//wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wc.lpszClassName = className;

	if(!RegisterClassEx(&wc))
	{
		sprintf(buf,"GLWindow::createWindow(): %s luokan rekister�inti ep�onnistui!\n",className);
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}	

	ZeroMemory(&p, sizeof(p));
	p.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	p.nVersion = 1;
	p.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	p.iPixelType = PFD_TYPE_RGBA;
	p.cColorBits = bpp;
	p.cDepthBits = zbpp;
	p.iLayerType = PFD_MAIN_PLANE;

	//---------------------
	// DUMMY FSAA WINDOW
	// ikkuna ja ogl auki 
	// ja haetaan tuettu 
	// fsaa moodi
	//---------------------

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;	


	HWND hStupid =  CreateWindowEx(dwExStyle, className, "Dummy FSAA window", dwStyle, 0, 0, 1, 1, NULL, NULL, NULL, NULL);
	if(!hStupid)
	{

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda FSAA dummy ikkunaa!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	  // opengl context
	HDC temphDC = GetDC(hStupid);
	HGLRC temphRC;

	int requestedFormat;
	int tempformat = 0;
	tempformat = ChoosePixelFormat( temphDC, &p );
    if (tempformat  == 0 || 
		(SetPixelFormat( temphDC, tempformat, &p ) == FALSE) || 
		((temphRC = wglCreateContext(temphDC)) == NULL)
		)
	{
		ReleaseDC(hStupid,temphDC);
		DestroyWindow(hStupid);

		sprintf(buf,"GLWindow::createWindow(): FSAA testi ikkunan luonti ep�onnistui!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	// get pixelformat
	if(!wglMakeCurrent(temphDC,temphRC))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut aktivoida fsaa test contextia!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;	
	}

	requestedFormat = fetchFSAAMode(temphDC, tempformat, p, fsaa);

	// kill dummy test window
	wglMakeCurrent(NULL,NULL);
	ReleaseDC(hStupid,temphDC);
	wglDeleteContext(temphRC);	
	DestroyWindow(hStupid);
	
	// ----------
	// FSAA test END
	// * now we have fsaa suitable mode in 'int requestedFormat'
	// * next feed it into setpixelformat
	// ----------

	if(fullscreen)
	{
		DEVMODE dmScreenSettings; // device mode

		ZeroMemory(&dmScreenSettings, sizeof(DEVMODE)); // nollataan 
		dmScreenSettings.dmSize = sizeof(DEVMODE);
		dmScreenSettings.dmPelsWidth = width;		// ruudun koko
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bpp;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		// kokeillaan josko wintoosa suostuisi vaihtamaan moodia:
		// CDS_FULLSCREEN: ei start bar:a 
		if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			fullscreen = false;			
		}		

		eStyle = WS_EX_APPWINDOW;// | WS_EX_TOPMOST; //[topmostin poisti; rale 12.9-06]
		style = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;		
		ShowCursor(FALSE);

	}
	else
	{

		if(onTop) {
			eStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE | WS_EX_TOPMOST; 	// taskbariin | raised edge border | alwaysontop
			//style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_SYSMENU;
		} else {
			eStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		}

		//style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		// | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
	}	

	if( fullscreen )
	{
		xpos = 0;
		ypos = 0;
	}

	AdjustWindowRectEx(&rect, style, FALSE, eStyle);
	hwnd = CreateWindowEx(eStyle, 
						  className,
						  title,
						  style,
						  xpos,
						  ypos,
						  rect.right - rect.left,
						  rect.bottom - rect.top,
						  HWND_DESKTOP,
						  NULL,
						  hinstance,
						  NULL);

	// Korjataan ruudun kokoa jos ollaan ikkunoidussa tilassa
	if(!fullscreen)
	{
		height = rect.bottom - rect.top + 5;
	}

	if(!hwnd)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda ikkunaa!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	hdc = GetDC(hwnd);
	if(!hdc)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda device contexia!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	format = ChoosePixelFormat(hdc, &p);
	if(!format)
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): haettua resoluutiota ei tueta!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	if(!SetPixelFormat(hdc, requestedFormat, &p))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut asettaa haettua resoa!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}
	
	if(!(hrc = wglCreateContext(hdc)))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut luoda GL-device contexia!\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;
	}

	if(!wglMakeCurrent(hdc, hrc))
	{
		kill();

		sprintf(buf,"GLWindow::createWindow(): ei voinut aktivoida rendreing contexia\n");
		MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
		return false;	
	}

	// Vertical Syncin poisto alkaa. Tapahtuu WGL-extensionin avulla
	// Muuttujat jotka osoittavat laajennus funkkareihin
	PFNWGLSWAPINTERVALEXTPROC		wglSwapIntervalEXT = 0;
	PFNWGLGETSWAPINTERVALEXTPROC	wglGetSwapIntervalEXT = 0;

	// haetaan funkkarit
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");

	// verticalSyncFlag = false jos laajennusten haku ei onnistunut.
	// Ohjelma ei kuitenkaan kaadu t�h�n
	if (!wglSwapIntervalEXT || !wglGetSwapIntervalEXT) 
	{
		verticalSyncFlag = false;
	}
	else
	{
		// ...muulloin haetaan V-syncin arvo ennen kuin ajetaan ohjelma.
		verticalSync = wglGetSwapIntervalEXT();

		// Enabloidaan vsync (1=enable, 0=disable)
		wglSwapIntervalEXT(1);
	}

	ShowWindow(hwnd, SW_SHOW);	
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	return true;
}

bool GLWindow::kill()
{
	//ChangeDisplaySettings(NULL, 0);						// Switch Back To Desktop Resolution
	//ShowCursor(true);									// Show The Cursor

	if(hwnd)
	{
		char buf[256] = {0};

		// jos verticalSync:� on n�pel�ity ...
		if(verticalSyncFlag)
		{
			// ... palautetaan se alkuper�iseksi
			wglSwapIntervalEXT(verticalSync);
		}

		if(hrc)
		{
				wglMakeCurrent(hdc, 0);
				if(hrc)
				{
					wglDeleteContext(hrc);
					hrc = NULL;
				}

				ReleaseDC(hwnd, hdc);
				hdc = NULL;
		}

		DestroyWindow(hwnd);
		hwnd = NULL;

		if(!UnregisterClass(className, hinstance))
		{	
			sprintf(buf,"GLWindow::kill(): ei voinut vapauttaa luokkaa %s\n", className);
			MessageBox(NULL, buf,"Error", MB_OK | MB_ICONEXCLAMATION| MB_TOPMOST);
			return false;	
		}

		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}	

	return true;
}

bool GLWindow::getFullscreen()
{
	return fullscreen;
}

bool GLWindow::getActive()
{
	return active;
}

//	Getterit
unsigned int GLWindow::getWidth()
{
	return width;
}

unsigned int GLWindow::getHeight()
{
	return height;
}

HWND GLWindow::getHandle()
{
	return hwnd;
}

HINSTANCE GLWindow::getInstance()
{
	return hinstance;
}

HDC GLWindow::getHDC()
{
	return hdc;
}

// Setterit
void GLWindow::setWidth(unsigned int w)
{
	width = w;
}

void GLWindow::setHeight(unsigned int h)
{
	height = h;
}

void GLWindow::setBpp(unsigned int b)
{
	bpp = b;
}

void GLWindow::setZbpp(unsigned int z)
{
	zbpp = z;
}

void GLWindow::setSbpp(unsigned int s)
{
	sbpp = s;
}

void GLWindow::setFullscreen(bool f)
{
	fullscreen = f;
}

void GLWindow::setActive(bool a)
{
	active = a;
}

void GLWindow::setTitle(char *t)
{
	title = t;
}

void GLWindow::setClassName(char *c)
{
	className = c;
}

void GLWindow::setPerspective2D(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0,640, 0,480,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glLoadIdentity();
}

void GLWindow::setPerspective2D(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0,w,0,h,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glLoadIdentity();
}

void GLWindow::setPerspective3D(void)
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

bool GLWindow::extensionExist(const char *extension)
{
  // try to find extension from wgl/gl extensions lists
  PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = 0;
  wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
  if(wglGetExtensionsStringARB)
  {
	const char *winsys_extensions = wglGetExtensionsStringARB(wglGetCurrentDC());
	if (winsys_extensions && (strstr(winsys_extensions,extension)))
	  return true;
  }
  const char *glExtensions = (const char*)glGetString(GL_EXTENSIONS);
  if (!glExtensions)
	return false;

  return (strstr(glExtensions,extension) != NULL);
}

// Try with requestedmultisamples
// fail => Fallback to 2
// fail => Fallback to 0
int GLWindow::fetchFSAAMode(HDC hdc, int suggestedFormat, PIXELFORMATDESCRIPTOR p, int requestedmultisamples)
{
  // if multisamples are not wanted, 
  if(requestedmultisamples <= 0)
	  return suggestedFormat;

  HDC hDC = wglGetCurrentDC();

  PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = 
	  (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");	

  if (!wglChoosePixelFormatARB)
	return suggestedFormat;

  if (!extensionExist("WGL_ARB_multisample"))
	return suggestedFormat;

  int pixelFormat;
  BOOL bStatus;
  UINT numFormats;
  float fAttributes[] = {0,0};
  int iAttributes[] = { 
	WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
	WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
	WGL_COLOR_BITS_ARB,		p.cColorBits,
	WGL_ALPHA_BITS_ARB,		8,
	WGL_DEPTH_BITS_ARB,		p.cDepthBits,
	WGL_STENCIL_BITS_ARB,	p.cStencilBits,
	WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
	WGL_SAMPLE_BUFFERS_ARB,	GL_TRUE,
	WGL_SAMPLES_ARB,requestedmultisamples,
	0,0};

  bStatus = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
  if ((bStatus == GL_TRUE) && (numFormats == 1))
	return pixelFormat;	  

  // try 2 samples
  iAttributes[19] = 2;
  bStatus = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
  if ((bStatus == GL_TRUE) && (numFormats == 1))
	return pixelFormat;	  
  

  // return default format, we didn't have support for FSAA
  return suggestedFormat;
}


bool GLWindow::getKey(int i)
{
	return keys[i];
}

void GLWindow::setKey(int i, bool b)
{
	this->keys[i] = b;
}


GLSystem::GLSystem()
{	
	width = 640;
	height = 480;	
	aspectratio = 0;

	fov = 45.0f;
	zNear = 0.1f;
	zFar = 14000.0f;

}

GLSystem::~GLSystem()
{

}

bool GLSystem::init(int w, int h, int aspectratio)
{
	resize(w, h);

	width = w;
	height = h;

	this->aspectratio = aspectratio;

	if(height == 0) height = 1;
	
	if(aspectratio==1)			// 16:10
		h = int(w*0.625f);
	else if(aspectratio==2)		// 16:9
		h = int(w*0.5625f);

	glViewport(0, (height-h)/2, w, h);
	float aspect = (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);	
		
	glEnable(GL_DEPTH_TEST);
	
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);		
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
				
	glDisable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);				
	glEnable(GL_TEXTURE_2D);	

	return true;
}

void GLSystem::resize(int w, int h)
{

	width = w;
	height = h;

	if(height == 0) height = 1;

	if(aspectratio==1)			// 16:10
		h = int(w*0.625f);
	else if(aspectratio==2)		// 16:9
		h = int(w*0.5625f);

	float aspect = (float)w/(float)h;

	glViewport(0, (height-h)/2, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, aspect, 0.1f, 14000.0f);
	gluPerspective(fov, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLSystem::resetViewport() 
{
	int h = height;
	int w = width;

	if(this->aspectratio==1)			// 16:10
		h = int(w*0.625f);
	else if(this->aspectratio==2)		// 16:9
		h = int(w*0.5625f);

	glViewport(0, (height-h)/2, w, h);
}

void GLSystem::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void GLSystem::setFov(float fov)
{
	this->fov = fov;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(fov, (float)width/(float)height, 0.5f, 14000.0f);
	gluPerspective(fov, (float)width/(float)height, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLSystem::setPerspective(float fov, float zNear, float zFar)
{
	this->fov = fov;
	this->zNear = zNear;
	this->zFar = zFar;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(fov, (float)width/(float)height, 0.5f, 14000.0f);
	gluPerspective(fov, (float)width/(float)height, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLSystem::loadOMeter(int current, int max)
{
	float step = float(current - max) / float(max);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	

	for(int i = 0; i < current; i++)
	{	
		glLoadIdentity();
		glTranslatef(0, 0, -50);

		glBegin(GL_QUADS);
			glVertex3f(-1.0f+i, -1.0f, 0);
			glVertex3f( 1.0f+i, -1.0f, 0);
			glVertex3f( 1.0f+i,  1.0f, 0);
			glVertex3f(-1.0f+i,  1.0f, 0);	
		glEnd();
	}	
}




//--------------------------------------------------------------------------------------------
//  Includes global functions to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{
	LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg,	WPARAM wParam, LPARAM lParam)
	{			
		
		extern GLWindow glWindow;

		switch(uMsg)
		{	
			case WM_KEYDOWN:
			{
				glWindow.setKey(wParam, true);
				return 0;
			} break;

			case WM_KEYUP:
			{
				glWindow.setKey(wParam, false);
				return 0;
			} break;

			case WM_LBUTTONDOWN:
			{
				glWindow.mouseX = LOWORD(lParam);
				glWindow.mouseY = HIWORD(lParam);
				glWindow.leftMouse = true;
				return 0;
			} break;

			case WM_RBUTTONDOWN:
			{
				glWindow.mouseX = LOWORD(lParam);
				glWindow.mouseY = HIWORD(lParam);
				glWindow.rightMouse = true;
				return 0;
			} break;

			case WM_LBUTTONUP:
			{
				glWindow.leftMouse = false;
				return 0;
			} break;

			case WM_RBUTTONUP:
			{
				glWindow.rightMouse = false;
				return 0;
			} break;

			case WM_MOUSEMOVE:
			{
				glWindow.mouseX = LOWORD(lParam);
				glWindow.mouseY = HIWORD(lParam);

				return 0;
			} break;


			case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
					return 0;
				}		
				break;									
			} break;

			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			} break;

			case WM_DESTROY:
			{
				return 0;
			} break;
			case WM_GETMINMAXINFO:
			{
				return 0;
			} break;
			case WM_SIZE:
			{
				switch(wParam)
				{
					extern GLWindow glWindow;
					extern GLSystem glSystem;

					case SIZE_MINIMIZED:
					{
						glWindow.setActive(false);
						return 0;
					} break;

					case SIZE_MAXIMIZED:
					case SIZE_RESTORED:
					{						
						int width = LOWORD(lParam);
						int height = HIWORD(lParam);

						glWindow.setWidth(width);
						glWindow.setHeight(height);
						glWindow.setActive(true);
						glSystem.resize(width, height);
						return 0;
					} break;
				}

				return 0;
			} break;
		}	

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
