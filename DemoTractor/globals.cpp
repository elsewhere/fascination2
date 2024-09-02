/*
	[1.1.0]
    - Added dmsCalcPos, dmsCalcSaturate, and dmsRandFloat-functions [28.9.2005 Vulture]
	- dmsErrorMsg-function removed [25.9.2005 Vulture]

	[1.1.1]
	- Added missing functions of ancient versions for non-OpenGL-stuff [3.12.2005 Vulture]
	- Fixed dmsRun more robust with software rendering [4.12.2005 Vulture]
	- Fixed dmsLoadSong more robust [4.12.2005 Vulture]
	- Fixed readSetup and readPak to more robust and changed them to dmsReadSetup and 
	  dmsReadPak [4.12.2005 Vulture]
	- Added dmsGetModulePosition [4.12.2005 Vulture]
    - Fixed bug in crossProduct function of Vector3 class [23.1.2006 Vulture]
	- Added makeScale function to Matrix class [23.1.2006 Vulture]
	- Added support for OGG format [23.1.2006 Vulture]
	- Removed path.hpp and lista.hpp from the project [23.1.2006 Vulture]
	- Finished fixing timer bug [13.2.2006]

    [1.2.0]
	- Added console support for debugging purposes with two new functions:
	  dmsClearConsole and dmsConsoleMsg [28.2.2006 Vulture]	
	- Added Vector33 class [28.2.2006 Vulture]
	- Fixed some timer issues [11.3.2006 Vulture]

	[1.2.2]
	- Added Vector33 class [26.6.2006 Vulture]
	- Changed JPEGLIB to DevIL [26.6.2006 Vulture]
	- Added support for PNG images [26.6.2006 Vulture]
	- Fixed bug in the dmsMakePAK. Checks for file type so that hidden files and 
	  directories aren't packed [27.6.2006 Vulture]
	- Added Path and Lista classes with DLL export [27.6.2006 Vulture]
	-.Added BPM class [3.7.2006 Vulture]
	-.Updated FMOD [3.7.2006 Vulture]
	- Updated dmsGetSpectrum to suite updated FMOD [7.7.2006 Vulture]
	- Reverted dmsGetSpectrum to get spectrum again :) [11.7.2006 rale]
	- Implemented dmsGetWaveData [11.7.2006 rale]
	- Added SplineKey and SplineSystem classes [17.7.2006 Vulture]
	- Fixed window positioning on fullscreen mode [18.7.2006 Vulture]
	- Added enum for Alpha testing [31.7.2006 Vulture]

    [1.2.3]
	- Fixed sound switch [23.8.2006 rale]
	- Fixed window opening position [23.8.2006 rale]
	- Added VSync to default to ON [23.8.2006 rale]
	- Added Always on top switch [23.8.2006 rale]
	- Added "void dmsLogStateGL()" for opengl error checking [23.8.2006 rale]
	- Added MB_TOPMOST to all dialogboxes, (now displayed on top of always on top window) [30.9.2006 rale]
	- Added Log messages when texture, font or t3d was not found on dmsGet*()
	- Added getHWND() [7.9.2006  rale]
	- Added support for FSAA 
	- Added matrix4 [23.11.2006 rale]
 

 // [notes]

 - Volume control..
 - Removed EnumTable Functions from opengl states..

*/

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

// This extracts MFC stuff off
#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN           

#include <stdio.h>
#include "globals.hpp"
#include "list.hpp"
#include "PAKfile.hpp"
#include "glext.h"

#define DMS_TEXTURE 0x01

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Enumerations for OpenGL statewrapper
//--------------------------------------------------------------------------------------------

struct enums
{
	bool flag;
	int code;
	char *name;
} enumTable[] = {	
					{ false, GL_BLEND, "Blending" },
					{ false, GL_TEXTURE_1D, "1D Textures" },
					{ false, GL_TEXTURE_2D, "2D Textures" },
					{ false, GL_DEPTH_TEST, "Depth testing" },
					{ false, GL_LIGHTING, "Lighting" }, 
					{ false, GL_LIGHT0, "Light0" },
					{ false, GL_LIGHT1, "Light1" },
					{ false, GL_LIGHT2, "Light2" },
					{ false, GL_LIGHT3, "Light3" },
					{ false, GL_LIGHT4, "Light4" },
					{ false, GL_LIGHT5, "Light5" },
					{ false, GL_LIGHT6, "Light6" },
					{ false, GL_LIGHT7, "Light7" },
					{ false, GL_NORMALIZE, "Normalization" },					
					{ false, GL_CULL_FACE, "Face culling" },
					{ false, GL_TEXTURE_CUBE_MAP_EXT, "Cube mapping" },
					{ false, GL_TEXTURE_GEN_S, "Texture coordinate (S) generation" },
					{ false, GL_TEXTURE_GEN_T, "Texture coordinate (T) generation" },
					{ false, GL_TEXTURE_GEN_R, "Texture coordinate (R) generation" },
					{ false, GL_FOG, "Fog" },
					{ false, GL_LINE_SMOOTH, "Antialised lines" },
					{ false, GL_POINT_SMOOTH, "Antialised points" },
					{ false, DUMMY, "Depth Mask" },
					{ false, GL_ALPHA_TEST, "Alpha test" }
				};

	int nIndex = sizeof(enumTable) / 12;
	int prev_src = 0;
	int prev_dst = 0;
};


//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Global instances
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{
	GLWindow glWindow;
	GLSystem glSystem;
	unsigned int *frameBuffer = NULL;
}

Log *logFile = NULL;
Timer *timer = NULL;
Sound *sound = NULL;
Song music;
TextureManager *tManager = NULL;
EffectManager *eManager = NULL;
FontManager *fManager = NULL;
ObjectManager *oManager = NULL;
List <int> syncs;
unsigned int currentSync = 0;
bool enableLogging = false;
HANDLE standardOutput = NULL;

//--------------------------------------------------------------------------------------------
//  Prototype implementations
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
//  Function: void dmsMsg(const char *text, ...)
//  Param1: String to be written
//  Param2: Printf-style parameters
//
//  Usage: Output text to log.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsMsg(const char *text, ...)
{	
	va_list ap;
	char buf[1024] = {0};
	
	if(!text) return;
				
	va_start(ap, text);
	    vsprintf(buf, text, ap);
	va_end(ap);
	
	if(logFile)
	{
		logFile->writeToLog(buf);
	}
}	

//--------------------------------------------------------------------------------------------
//  Function: void dmsConsoleMsg( COORD cursor, const char *text, ...)
//  Param1: Cursor position on a console
//  Param2: String to be written to the console
//  Param3: Printf-style parameters
//
//  Usage: Output text to log.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsConsoleMsg( int x, int y, const char *text, ...)
{
	va_list ap;
	char buf[1024] = {0};
	
	if(!text) return;
				
	va_start(ap, text);
	    vsprintf(buf, text, ap);
	va_end(ap);

	if( !standardOutput )
	{
		AllocConsole();
		standardOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	}

	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	
	SetConsoleCursorPosition( standardOutput, cursor );

	WriteConsole( standardOutput, buf, strlen( buf ), NULL, NULL );
}

extern "C" __declspec(dllexport) void dmsClearConsole()
{
	COORD cursor;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	if( !standardOutput )
	{
		AllocConsole();
		standardOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	}
	
	GetConsoleScreenBufferInfo( standardOutput, &consoleInfo );
	
	cursor.X = 0;
	cursor.Y = 0;

	FillConsoleOutputCharacter( standardOutput, ' ', consoleInfo.srWindow.Right * consoleInfo.srWindow.Bottom, cursor, NULL );
}

//--------------------------------------------------------------------------------------------
//  Function: void dmsSetLogging(bool f)
//  Param1: Enable or disable flag
//
//  Usage: Enable or disable logging.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsSetLogging(bool f)
{
	enableLogging = f;
}

//--------------------------------------------------------------------------------------------
//  Function: bool dmsSetupInstances()
//
//  Usage: Initialize system with default settings for software rendering
//  Return value: TRUE on success. FALSE on failure.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) bool dmsSetupInstances()
{
	if(enableLogging)
	{
		logFile = Log::create("loki.log");
		if(!logFile)
		{
			throw "One of the class instances didn't initialize";
		}
	}
	
	timer = Timer::create();
	sound = Sound::create();
	tManager = TextureManager::create();
	eManager = EffectManager::create();
	fManager = FontManager::create();
	oManager = ObjectManager::create();
	
	// Check for existing instances
	if(	!timer ||
		!sound ||
		!tManager ||
		!eManager ||
		!fManager ||
		!oManager
	) 
	{
		throw "One of the class instances didn't initialize";			
	}

	sound->setEnabled(true);
		
	// Init timer
	timer->init();

	if(sound)
	{		
	//		sound->setVolume(&music, 0);
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//  Function: bool dmsInit()
//
//  Usage: Initialize system with default settings. That is:
//		- Screen 640 * 480 * 32
//		- Windowed mode
//		- Sound enabled
//		- Read "setup.ini" for resource loading information 
//		  (this is rarely used function and lacks PAK-file support)
//  Return value: TRUE on success. FALSE on failure.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) bool dmsInit()
{
	if(enableLogging)
	{
		logFile = Log::create("loki.log");
		if(!logFile)
		{
			throw "One of the class instances didn't initialize";
		}
	}
	
	timer = Timer::create();
	sound = Sound::create();
	tManager = TextureManager::create();
	eManager = EffectManager::create();
	fManager = FontManager::create();
	oManager = ObjectManager::create();
	
	// Check for existing instances
	if(	!timer ||
		!sound ||
		!tManager ||
		!eManager ||
		!fManager ||
		!oManager
		) 
	{
		throw "One of the class instances didn't initialize";			
	}

	sound->setEnabled(true);

	// Create and setup opengl window/system
	if(!glWindow.createWindow(640, 480, 32, false, false, 0))
	{		
		throw "Error while creating window";			
	}

	// Init opengl system
	glSystem.init(640, 480);

	// Read setup file: ie. Textures and sounds are loaded here
	if(!dmsReadSetup("setup.ini"))
	{
		throw "dmsInit() error: \"setup.ini\" not found\n";
	}

	// Initialize 3D-objects
	if(!oManager->initObjects()) return false;
				
	// Init timer
	timer->init();

	if(sound)
	{		
			//sound->setVolume(&music, 0);
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//  Function: bool dmsInitEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync, bool onTop, int fsaa, float aspectratio, char *pakFile)
//
//  Param1: Screen width
//  Param2: Screen height
//  Param3: Bits per pixel
//  Param4: Create window in fullscreen mode or not
//  Param5: Enable or disable sound
//  Param6: Enable or disable WaitRetrace
//  Param7: If in windowed mode, always ontop toggle
//  Param8: Fullscreen Anti-Aliasing multisample count (0=disabled)
//  Param9: Aspect ratio 0=4/3 , 1=16/10 , 2=16/9
//  Param10: Path to PAK-file that holds all resources
//
//  Usage: Initialize system with given settings.
//  Return value: TRUE on success. FALSE on failure.
//--------------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) bool dmsInitEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync, bool onTop, int fsaa, int aspectratio, char *pakFile)
{
	if(enableLogging)
	{
		logFile = Log::create("loki.log");
		if(!logFile)
		{
			throw "One of the class instances didn't initialize";
		}
	}
	
	timer = Timer::create();
	sound = Sound::create();
	tManager = TextureManager::create();
	eManager = EffectManager::create();
	fManager = FontManager::create();
	oManager = ObjectManager::create();
	
	// Check for existing instances
	if(	!timer ||
		!sound ||
		!tManager ||
		!eManager ||
		!fManager ||
		!oManager
	) 
	{
		throw "One of the class instances didn't initialize";			
	}

	// Toggle sound on/off
	sound->setEnabled(soundFlag);

	// Create and setup opengl window/system
	if(!glWindow.createWindow(screenX, screenY, bpp, fullscreen, onTop, fsaa))
	{		
		throw "Error while creating window";			
	}

	// Init opengl system
	glSystem.init(screenX, screenY, aspectratio);

	dmsLoadBar(0.0f);
	
	if(!pakFile)
	{
		// Read setup file: ie. Textures and sounds are loaded here
		if(!dmsReadSetup("setup.ini"))
		{
			throw "dmsInitEx() error: \"setup.ini\" not found\n";
		}
	}
	else
	{
		if(!dmsReadPak(pakFile))
		{
			char buf[256] = {0};

			sprintf(buf, "dmsInitEx(): Error while loading %s\n", pakFile);
			throw buf;
		}
	}
	
	
	//dmsLoadPic("loadpic.jpg");

	// Initialize 3D-objects
	if(!oManager->initObjects()) return false;
	
	// Init timer
	timer->init();
	
	if(sound)
	{		
		if(!soundFlag)
		{
			sound->setVolume(&music, 0);
		}	
	}
	return true;
}

//--------------------------------------------------------------------------------------------
//  Function: bool dmsInitDummyEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync)
//
//  Param1: Screen width
//  Param2: Screen height
//  Param3: Bits per pixel
//  Param4: Create window in fullscreen mode or not
//  Param5: Enable or disable sound
//  Param6: Enable or disable WaitRetrace
//  Param7: If in windowed mode, always ontop toggle
//
//  Usage: Initialize system with given settings, but don't load any resources.
//  Return value: TRUE on success. FALSE on failure.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) bool dmsInitDummyEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync, bool onTop)
{
	if(enableLogging)
	{
		logFile = Log::create("loki.log");
		if(!logFile)
		{
			throw "One of the class instances didn't initialize";
		}
	}

	timer = Timer::create();
	sound = Sound::create();
	tManager = TextureManager::create();
	eManager = EffectManager::create();
	fManager = FontManager::create();
	oManager = ObjectManager::create();
	
	// Check for existing instances
	if(	!timer ||
		!sound ||
		!tManager ||
		!eManager ||
		!fManager ||
		!oManager 
		) 
	{
		throw "One of the class instances didn't initialize";
	}

	// Toggle sound on/off
	sound->setEnabled(soundFlag);

	// Create and setup opengl window/system
	if(!glWindow.createWindow(screenX, screenY, bpp, fullscreen, onTop, 0))
	{		
		throw "Error while creating window";			
	}

	// Init opengl system
	glSystem.init(screenX, screenY);

	return true;
}

//--------------------------------------------------------------------------------------------
//  Function: bool dmsOnFocus()
//
//  Usage: Get focus state of a demo window
//  Return value: TRUE on success. FALSE on failure.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) bool dmsOnFocus()
{
	return glWindow.getActive();
}

extern "C" __declspec(dllexport) void dmsSetGamma(int gamma)
{
	HDC hdc = dmsGetHDC();
	
	if(hdc)
	{
		struct ramp
		{
			unsigned short red[256];
			unsigned short green[256];
			unsigned short blue[256];
		} colorRamp;
		
		// float gamma valuen pit‰‰ olla 0..2f(??)
		if(GetDeviceGammaRamp(hdc, (LPVOID)&colorRamp))
		{
			int i;
			
			for(i = 0; i < 256; i++)
			{					

				//colorRamp.red[i] = (WORD)min(65535, max(0, pow((i+1) / 256.0, float(gamma) / 256.0f) * 65535 + 0.5));
				//colorRamp.green[i] = (WORD)min(65535, max(0, pow((i+1) / 256.0, float(gamma) / 256.0f) * 65535 + 0.5));
				//colorRamp.blue[i] = (WORD)min(65535, max(0, pow((i+1) / 256.0, float(gamma) / 256.0f) * 65535 + 0.5));
				
				if(gamma < 0)
				{
					//colorRamp.red[i] = unsigned short((255 - -gamma)*(i));
					//colorRamp.green[i] = unsigned short((255 - -gamma)*(i));
					//colorRamp.blue[i] = unsigned short((255 - -gamma)*(i));										

					//colorRamp.red[i] = (WORD)(pow((i+1) / 256.0, (float(-gamma) / 256.0f)) * 65535);
					//colorRamp.green[i] = (WORD)(pow((i+1) / 256.0, (float(-gamma) / 256.0f)) * 65535);
					//colorRamp.blue[i] = (WORD)(pow((i+1) / 256.0, (float(-gamma) / 256.0f)) * 65535);

					colorRamp.red[i] = (WORD)(pow(i, 1.0f + (float(gamma) / 256.0f)) * 255);
					colorRamp.green[i] = (WORD)(pow(i, 1.0f + (float(gamma) / 256.0f)) * 255);
					colorRamp.blue[i] = (WORD)(pow(i, 1.0f + (float(gamma) / 256.0f)) * 255);
				}
				else
				{
					//colorRamp.red[i] = 65535 - unsigned short((255 - gamma)*(255 - i));
					//colorRamp.green[i] = 65535 - unsigned short((255 - gamma)*(255 - i));
					//colorRamp.blue[i] = 65535 - unsigned short((255 - gamma)*(255 - i));

					colorRamp.red[i] = (WORD)(pow((i+1) / 256.0, 1.0f + (float(gamma) / 256.0f)) * 65535);
					colorRamp.green[i] = (WORD)(pow((i+1) / 256.0, 1.0f + (float(gamma) / 256.0f)) * 65535);
					colorRamp.blue[i] = (WORD)(pow((i+1) / 256.0, 1.0f + (float(gamma) / 256.0f)) * 65535);					
				}				
			}
			
			BOOL b = SetDeviceGammaRamp(hdc, (LPVOID)&colorRamp);
			if(!b)
			{
				dmsMsg("dmsSetGamma error: SetDeviceGammaRamp failed\n");
			}
		}
		else
		{
			dmsMsg("dmsSetGamma error: GetDeviceGammaRamp failed\n");
		}		
	}
}

//--------------------------------------------------------------------------------------------
//  Function: void dmsShutDown()
//
//  Usage: Frees up allocated memory and kills everything. End of demo
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsShutDown()
{	
	if( frameBuffer )
	{
		delete [] frameBuffer;
		frameBuffer = NULL;
	}

	glWindow.kill();

	syncs.freeList();
	music.stop();
	music.release();

	if(oManager)
	{
		oManager->release();
		oManager = NULL;
	}

	if(fManager)
	{
		fManager->release();
		fManager = NULL;
	}

	if(eManager)
	{
		eManager->release();
		eManager = NULL;
	}

	if(tManager)
	{
		tManager->release();
		tManager = NULL;
	}

	if(sound)
	{
		sound->close();
		sound = NULL;
	}

	if(timer)
	{
		timer->release();
		timer = NULL;
	}	

	if(logFile)
	{
		logFile->release();
		logFile = NULL;
	}

	if( standardOutput )
	{
		FreeConsole();
	}
}

//--------------------------------------------------------------------------------------------
//  Function: void dmsCheckControls(float jump)
//
//  Usage: Check for key presses. Used for rewinding and fastforwarding demo at the moment.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsCheckControls(float jump)
{
	// If LEFT ARROW was pressed -> ReWind small amount of time
	if(GetAsyncKeyState(VK_LEFT))
	{
		dmsAdjustTime(-jump);					
	}

	// If RIGHT ARROW was pressed -> FastForward small amount of time
	if(GetAsyncKeyState(VK_RIGHT))
	{
		dmsAdjustTime(jump);					
	}
}

//--------------------------------------------------------------------------------------------
//  Function: void dmsPerspective2D(int w, int h)
//
//  Param1: Screen width.
//  Param2: Screen height.
//
//  Usage: Set OpenGL matrices so that perspective is orthogonal => Allow 2D rendering.
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsPerspective2D(int w, int h)
{
	glWindow.setPerspective2D(w, h);
}

extern "C" __declspec(dllexport) void dmsPerspective3D()
{
	glWindow.setPerspective3D();
}

extern "C" __declspec(dllexport) void dmsSetFOV(float f)
{
	glSystem.setFov(f);
}

extern "C" __declspec(dllexport) void dmsSetPerspective(float fov, float zNear, float zFar)
{
	glSystem.setPerspective(fov, zNear, zFar);
}

extern "C" __declspec(dllexport) void dmsInitTimer()
{
	if(timer)
	{
		timer->init();
	}
	else
	{
		throw "Timer not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsAdjustTime(float f)
{
	if(sound)
	{
		if((music.getPosition()+f) >= 0)
		{
			music.setPosition((unsigned int)(music.getPosition()+f));
		}
		else
		{
			music.setPosition(0);
		}
	}
}

extern "C" __declspec(dllexport) void dmsInitSound()
{
	if(sound)
	{
		if(!sound->init())
		{
			throw "Sound initialization failed";
		}				
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsLoadSong(const char *fileName)
{
	if(sound)
	{
		if( strstr( fileName, ".it" ) ||
			strstr( fileName, ".xm" ) ||
			strstr( fileName, ".s3m" ) )
		{
/*
			if( !music.loadMod( ( char * ) fileName ) )
			{			
				char buf[256] = {0};

				sprintf(buf, "dmsLoadSong() error: Couldn't load song \"%s\"", fileName);
				throw buf;
			}								
*/
		}
		else
		{			
			if(!music.loadStream((char *)fileName))
			{			
				char buf[256] = {0};

				sprintf(buf, "dmsLoadSong() error: Couldn't load song \"%s\"", fileName);
				throw buf;
			}								
		}
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsLoadSongFromMemory(unsigned char *fileData, unsigned int fileSize)
{
	if(sound)
	{
		if(!music.loadStream2((char *)fileData, fileSize))
		{			
			char buf[256] = {0};

			sprintf(buf, "dmsLoadSong() error: Couldn't load song from data file");
			throw buf;
		}									
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsPlaySong(bool f)
{
	if(sound)
	{
		(f) ? music.start() : music.stop();		
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsSetVolume(float f)
{
	if(sound)
	{
		sound->setVolume(&music, f);
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsPauseSong(bool f)
{
	if(sound)
	{
		music.setPause(f);
	}
	else
	{
		throw "Sound not found\n";
	}
}

extern "C" __declspec(dllexport) bool dmsCheckSyncPoint()
{
	if(sound)
	{
		Node <int> *node = syncs.get(currentSync);
		if(node)
		{
			int *value = node->a;
			if(value)
			{
				if(music.getPosition() >= *value) 
				{
					sound->setSync(true);
					currentSync ++;
					return true;
				}
				else
				{
					sound->setSync(false);
					return false;
				}
			}		
		}
	}
	
	return false;
}

extern "C" __declspec(dllexport) void dmsSetMipmaps(const char *name, bool b)
{
	if(tManager)
	{
		Texture *t = NULL;
		t = tManager->getTextureName((char*)name);

		if(t == NULL)
		{
			t->setMipMaps(b);
		}
		else
		{
			dmsMsg("dmsSetMipmaps(): Could not find texture with name %s\n", name);
		}
	}
	else
	{
		throw "dmsUploadTextures() failed: No TextureManager found";
	}
}

extern "C" __declspec(dllexport) void dmsSetTextureParameters(const char *name, const int pname, float value)
{
	if(tManager)
	{
		Texture *t = NULL;
		t = tManager->getTextureName((char*)name);

		if(t == NULL)
		{
			t->setTextureParameters(pname, value);
		}
		else
		{
			dmsMsg("dmsSetTextureParameters(): Could not find texture with name %s\n", name);
		}
	}
	else
	{
		throw "dmsUploadTextures() failed: No TextureManager found";
	}
}

extern "C" __declspec(dllexport) void dmsUploadTextures()
{
	if(tManager)
	{
		// Upload textures to the OpenGL
		tManager->uploadTextures();
	}
	else
	{
		throw "dmsUploadTextures() failed: No TextureManager found";
	}
}

extern "C" __declspec(dllexport) void dmsAddTexture(const char *fileName, const char *name)
{
	if(tManager)
	{
		int type = -1;

		(strstr(fileName, ".pcx")) ? type = PCX : type = type;
		(strstr(fileName, ".tga")) ? type = TGA : type = type;
		(strstr(fileName, ".jpg")) ? type = JPG : type = type;
		(strstr(fileName, ".png")) ? type = PNG : type = type;

		if(!tManager->addTexture((char *)fileName, (char *)name, type))
		{
			char buf[256] = {0};

			sprintf(buf, "TextureManager::addTexture() failed with \"%s\"", fileName);
			throw buf;
		}
	}
	else
	{
		throw "TextureManager::addTexture() failed! No TextureManager found";
	}
}

extern "C" __declspec(dllexport) void dmsAddRenderToTexture(int width, int height, const char *name)
{
	if(tManager)
	{		
		if(!tManager->addRenderToTexture(width, height, (char *)name))
		{
			char buf[256] = {0};

			sprintf(buf, "TextureManager::addTexture() failed with \"%s\"", name);
			throw buf;
		}
	}
	else
	{
		throw "TextureManager::addTexture() failed! No TextureManager found";
	}

	//unsigned int fb;
	//glGenFramebuffersEXT( 1, &fb );

	//glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, &fb );
	// Render here
	//glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	//DeleteFramebuffersEXT();
}

extern "C" __declspec(dllexport) void dmsInitObjects()
{
	if(oManager)
	{
		if(!oManager->initObjects())
		{
			throw "Object initialization failed";
		}
	}
	else
	{
		throw "ObjectManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsAddObject(const char *fileName, const char *name)
{
	if(oManager)
	{
		if(!oManager->addObject((char *)fileName, (char *)name))
		{
			char buf[256] = {0};

			sprintf(buf, "ObjectManager::addObject() failed with \"%s\"", fileName);
			throw buf;
		}
	}
	else
	{
		throw "ObjectManager::addObject() failed! No ”bjectManager found";
	}
}

extern "C" __declspec(dllexport) void dmsDrawObject(const char *name)
{
    T3D *t3d = dmsGetObject(name);

	T3DVertex *vert = t3d->getVertexArray();
	T3DFace *face = t3d->getFaceArray();

	if(vert && face)
	{						
		for(int i = 0; i < t3d->getFaceCount(); i++)
		{
			T3DVertex v1, v2, v3;

			v1 = vert[face[i].a];
			v2 = vert[face[i].b];
			v3 = vert[face[i].c];
													
			glBegin(GL_TRIANGLES);
				glNormal3f(v1.normal.x, v1.normal.y, v1.normal.z); glTexCoord2f(v1.u, v1.v); glVertex3f(v1.position.x, v1.position.y, v1.position.z);
				glNormal3f(v2.normal.x, v2.normal.y, v2.normal.z); glTexCoord2f(v2.u, v2.v); glVertex3f(v2.position.x, v2.position.y, v2.position.z);
				glNormal3f(v3.normal.x, v3.normal.y, v3.normal.z); glTexCoord2f(v3.u, v3.v); glVertex3f(v3.position.x, v3.position.y, v3.position.z);					
			glEnd();
		}
	}
}

extern "C" __declspec(dllexport) void dmsInitEffects()
{
	if(eManager)
	{
		if(!eManager->initEffects())
		{
			throw "Effect initialization failed";
		}
	}
	else
	{
		throw "EffectManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsAddEffect(unsigned long st, unsigned long et, unsigned int prio, const char *name, Base *effect)
{
	if(eManager)
	{	
		if(!eManager->addEffect(st, et, prio, effect, (char *)name))		
		{
			char buf[256] = {0};

			sprintf(buf, "EffecteManager::addEffect() failed with \"%s\"", name);
			throw buf;
		}
	}
	else
	{
		throw "EffectManager::addEffect() failed! No EffectManager found";
	}
}

extern "C" __declspec(dllexport) void dmsSetEffectPriority(unsigned int prio, const char *name)
{
	if(eManager)
	{
		eManager->setPriority(prio, (char *)name);
	}
	else
	{
		throw "EffectManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsRun()
{
	if( eManager )
	{
		if( eManager->getEffectCount() > 0 )
		{
			Base *effect = NULL;
			float time;
			unsigned int i;

			eManager->sortEffects();

			time = ( float )dmsGetModulePosition();

			for( i = 0; i < eManager->getEffectCount(); i++ )
			{
				effect = eManager->getEffect(i);
				
				if( effect )
				{
					effect->update( time );

					if(effect->isActive() )
					{
						effect->draw();
					}
				}
			}

#ifndef _DMSSOFTWARE

			glFlush();

#endif
		}
	}
	else
	{
		throw "EffectManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsBindTexture(unsigned int mode, const char *name)
{
	Texture *texture = NULL;

	if(tManager)
	{
		texture = tManager->getTextureName((char *)name);
		if(!texture)
		{
			char buf[256] = {0};

			sprintf(buf, "TextureManager::getTextureName(): Texture \"%s\" not found\n", name);
			throw buf;
		}

		glBindTexture(GL_TEXTURE_2D, texture->getID());
	}
	else
	{
		throw "TextureManager::getTextureName() failed! No TextureManager found\n";
	}	
}

extern "C" __declspec(dllexport) void dmsAddFont(int x, int y, const char *name)
{
	if(fManager)
	{
		char buf[256] = {0};

		if(!fManager->addFont(x, y, (char *)name))
		{
			sprintf(buf, "dmsAddFont() error: %s\n", name);
			throw buf;
		}
	}
	else
	{
		throw "FontManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsUpdateTimer()
{
	if(timer)
	{
		timer->update();
	}
	else
	{
		throw "Timer not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsWrite2D(float x, float y, float a, float scale, char *fontName, char *msg)
{
	if(fManager)
	{	
		float width = glWindow.getWidth();
		float height = glWindow.getHeight(); 

		glWindow.setPerspective2D(width, height);

		fManager->write2D(x, y, a, scale, fontName, msg);

		glWindow.setPerspective3D();
	}
	else
	{
		throw "FontManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsWrite3D(float x, float y, float z, float a, char *fontName, char *msg)
{
	if(fManager)
	{		
		fManager->write3D(x, y, z, a, fontName, msg);
	}
	else
	{
		throw "FontManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsWrite3DEx(float x, float y, float z, float rx, float ry, float rz, float angle, float a, char *fontName, char *msg)
{
	if(fManager)
	{		
		fManager->write3DEx(x, y, z, rx, ry, rz, angle, a, fontName, msg);
	}
	else
	{
		throw "FontManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsSetWindowTitle(const char *msg)
{
	HWND handle = glWindow.getHandle();

	SetWindowText(handle, msg);
}

extern "C" __declspec(dllexport) float dmsGetTime()
{	
	if(timer)
	{
		// Jos biisi on streami palauttaa millisekunteja, mutta jos 
		// biisi on module palauttee order numeron
		//return (float)music.getPosition();

		// Vanha timeline
		return timer->getTime();
	}
	else
	{
		throw "Timer not found\n";
	}
}

extern "C" __declspec(dllexport) float dmsGetTimeMs()
{	
	if(timer)
	{
		// Jos biisi on streami palauttaa millisekunteja, mutta jos 
		// biisi on module palauttee order numeron
		//return (float)music.getPosition();

		// Vanha timeline
		return timer->getTimeMs();
	}
	else
	{
		throw "Timer not found\n";
	}
}

extern "C" __declspec(dllexport) float dmsGetDeltaTime()
{
	if(timer)
	{
		return timer->getDeltaTime();
	}
	else
	{
		throw "Timer not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsGetSpectrum( float *array, int size )
{
	if( sound )
	{
		sound->getSpectrum( &music, array, size );
	}
}

extern "C" __declspec(dllexport) void dmsGetWaveData( float *array, int size )
{
	if( sound )
	{
		sound->getWaveData( &music, array, size );
	}
}


extern "C" __declspec(dllexport) T3D *dmsGetObject(const char *name)
{
	if(oManager)
	{
		T3D *p = oManager->getObjectName((char *)name);
		 if(p==NULL) {
			dmsMsg("Error: T3D %s not found!\n", name);
			throw "T3D not found\n";					
		 }
		 return p;
	}
	else
	{
		throw "ObjectManager not found\n";
	}
}

extern "C" __declspec(dllexport) Texture *dmsGetTexture(const char *name)
{
	if(tManager)
	{
		Texture *p = tManager->getTextureName((char *)name);
		if(p==NULL) {
			dmsMsg("Error: Texture %s not found\n!", name);
			throw "Texture not found\n";
		}

		return p;
	}
	else
	{
		throw "TextureManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsSetTextureParameter(const char *name, unsigned int pname, float value)
{
	if(tManager)
	{
		Texture *p = tManager->getTextureName((char *)name);
		if(p==NULL) {
			dmsMsg("Error: Texture %s not found\n!", name);
			throw "Texture not found\n";
		}

		p->setTextureParameters(pname, value);
	}
	else
	{
		throw "TextureManager not found\n";
	}
}

extern "C" __declspec(dllexport) void dmsSetMipMaps(const char *name, bool b)
{
	if(tManager)
	{
		Texture *p = tManager->getTextureName((char *)name);
		if(p==NULL) {
			dmsMsg("Error: Texture %s not found\n!", name);
			throw "Texture not found\n";
		}

		p->setMipMaps(b);
	}
	else
	{
		throw "TextureManager not found\n";
	}
}


extern "C" __declspec(dllexport) Font *dmsGetFont(const char *name)
{
	if(fManager)
	{
		 Font *p = fManager->getFontName((char *)name);
		 if(p==NULL) {
			dmsMsg("Error: Font %s not found\n!", name);
			throw "Font not found\n";					
		 }
		 return p;
	}
	else
	{
		throw "TextureManager not found\n";
	}
}

extern "C" __declspec(dllexport) HDC dmsGetHDC()
{
	return glWindow.getHDC();
}

extern "C" __declspec(dllexport) HWND dmsGetHWND()
{
	return glWindow.getHandle();
}

extern "C" __declspec(dllexport) int dmsGetModulePosition()
{
	if( sound )
	{
		return music.getPosition();
	}

	return 0;
}

extern "C" __declspec(dllexport) int dmsGetWindowWidth()
{
	return glWindow.getWidth();
}

extern "C" __declspec(dllexport) int dmsGetWindowHeight()
{
	return glWindow.getHeight();
}

extern "C" __declspec(dllexport) float dmsGetFPS()
{
	if( timer )
	{
		return timer->getFPS();
	}

	return 0.0f;
}

extern "C" __declspec(dllexport) bool dmsMakePAK(const char *src, const char *dst)
{
	PAKFile pak;

	if(!pak.create((char *)src, (char *)dst))
	{
		return false;
	}

	return true;
}

extern "C" __declspec(dllexport) bool dmsReadSetup(char *name)
{	
	FILE *f;
	Parser parseri;	
	char buf[256] = {0};
	char dir[256] = {0};
	
	bool readMusic = false;
	bool readFonts = false;
	bool readTextures = false;	
	bool read3DObjects = false;

	f = fopen(name, "r");
	if(!f)
	{
		char buf[256] = {0};

		sprintf(buf, "dmsReadSetup(): Error opening file \"%s\"", name);
		throw buf;		
	}

	fseek(f, SEEK_SET, 0);

	while(parseri.readRow(f, buf))
	{		
		if(strstr(buf, "[Music]"))
		{
			readMusic = true;
			readFonts = false;
			readTextures = false;
			read3DObjects = false;
			
			memset(dir, 0, sizeof(dir));
		}

		if(strstr(buf, "[Font]"))
		{
			readMusic = false;
			readFonts = true;
			readTextures = false;
			read3DObjects = false;

			memset(dir, 0, sizeof(dir));
		}

		if(strstr(buf, "[Texture]"))
		{
			readMusic = false;
			readFonts = false;
			readTextures = true;
			read3DObjects = false;

			memset(dir, 0, sizeof(dir));
		}

		if(strstr(buf, "[Objects]"))
		{
			readMusic = false;
			readFonts = false;
			readTextures = false;
			read3DObjects = true;

			memset(dir, 0, sizeof(dir));
		}

		// Music block		
		if(readMusic)
		{				
			if(sound && !strstr(buf, "[Music]"))
			{			
/*
				PAKFile pak;

				if(!pak.read("data.pak")) return false;

				for(int i = 0; i < 20; i++)
				{
					FTEntry *e = pak.getFileTableEntry(i);
					if(e)
					{
						if(strstr(e->fileName, ".mp3"))
						{
							music.loadStream2(e->fileData, e->fileSize);
						}
					}
				}
*/				
				if(!sound->init()) return false;
				if(!music.loadStream(buf))
				{					
					return false;
				}
				
				readMusic = false;
			}			
		}

		if(readFonts && !strstr(buf, "[Font]"))
		{			
			char path[256] = {0};		// polku
			char name[256] = {0};		// nimiosa
			char filename[256] = {0};	// tiedostonimi
			char token1[256] = {0}, token2[256] = {0};
			char *ptr1, *ptr2;
				
			ptr1 = strtok(buf, "=");
			ptr2 = strtok(NULL, "=");
			sprintf(token1,"%s",ptr1);
			sprintf(token2,"%s",ptr2);
						
			if(strcmp(strlwr(token1),"dir") == 0)
			{			
				sprintf(dir, "%s", token2);
			}
			else
			{			
				sprintf(filename, "%s", token2);

				ptr1 = strtok(token2, ".");
				sprintf(name, "%s", token1);
			}
/*
			if(strlen(filename) > 4 && !strstr(filename, "(null)"))
			{
				sprintf(path, "%s\\%s", dir, filename);
				if(!fManager->addFont(32, 32, name, path)) return false;
			}
*/
		}

		// Texture block
		if(readTextures && !strstr(buf, "[Texture]"))
		{				
			char ext[3] = {0};			// tiedostop‰‰te			
			char path[256] = {0};		// polku
			char name[256] = {0};		// nimiosa
			char filename[256] = {0};	// tiedostonimi
			char token1[256] = {0}, token2[256] = {0};
			char *ptr1, *ptr2;
	
			// tarkistetaan kuvatiedoston formaatti
			ext[0] = buf[strlen(buf)-3];
			ext[1] = buf[strlen(buf)-2];
			ext[2] = buf[strlen(buf)-1];

			ptr1 = strtok(buf, "=");
			ptr2 = strtok(NULL, "=");
			sprintf(token1,"%s",ptr1);
			sprintf(token2,"%s",ptr2);
						
			if(strcmp(strlwr(token1),"dir") == 0)
			{			
				sprintf(dir, "%s", token2);
			}
			else
			{			
				sprintf(filename, "%s", token2);

				ptr1 = strtok(token2, ".");
				sprintf(name, "%s", token1);
			}

			sprintf(path, "%s\\%s", dir, filename);
			if(strstr(ext,"pcx") != NULL)
			{				
				if(!tManager->addTexture(path, name, PCX)) return false;
			}

			if(strstr(ext,"tga") != NULL)
			{
				if(!tManager->addTexture(path, name, TGA)) return false;
			}
		}

		// 3DObject block
		if(read3DObjects && !strstr(buf, "[Objects]"))
		{										
			char token1[256] = {0}, token2[256] = {0};
			char *ptr1, *ptr2;
				
			ptr1 = strtok(buf, "=");
			ptr2 = strtok(NULL, "=");
			sprintf(token1,"%s",ptr1);
			sprintf(token2,"%s",ptr2);

			if(ptr1 && ptr2)
			{					
				if(strcmp(strlwr(token1),"dir") == 0)
				{			
					sprintf(dir, "%s", token2);
				}
				else
				{					
					char path[256] = {0};
					char filename[256] = {0};
					char objectName[256] = {0};

					sprintf(filename, "%s", token2);		
					sprintf(objectName, "%s", token1);
					sprintf(path, "%s\\%s", dir, filename);

					if(!oManager->addObject(path, objectName)) return false;
				}
			}
		}
		
		memset(buf, 0, 256);
	}
	
	fclose(f);

	return true;
}

extern "C" __declspec(dllexport) bool dmsReadPak(char *name)
{
	int i;
	PAKFile pak;
	
	if(!pak.read(name)) return false;
	
	for(i = 0; i < pak.getFileCount(); i++)
	{				

		FTEntry *e = pak.getFileTableEntry(i);
		if(e)
		{						
			// Load PCX file as texture
			if(strstr(strlwr(e->fileName), ".pcx"))
			{						
			  if(!tManager->addTextureFromMemory(e->fileName, e->fileData, e->fileSize, e->fileName, PCX)) return false;
			}

			// Load TGA file as texture
			if(strstr(strlwr(e->fileName), ".tga"))
			{						
			  if(!tManager->addTextureFromMemory(e->fileName, e->fileData, e->fileSize, e->fileName, TGA)) return false;
			}

			// Load JPG file as texture
			if(strstr(strlwr(e->fileName), ".jpg"))
			{						
			  if(!tManager->addTextureFromMemory(e->fileName, e->fileData, e->fileSize, e->fileName, JPG)) return false;
			}

			// Load PNG file as texture
			if(strstr(strlwr(e->fileName), ".png"))
			{						
			  if(!tManager->addTextureFromMemory(e->fileName, e->fileData, e->fileSize, e->fileName, PNG)) return false;
			}

			// Load music
			if(strstr(strlwr(e->fileName), ".mp3") || strstr(strlwr(e->fileName), ".ogg"))
			{				
				if(sound)
				{
					if(!sound->init())
					{
						dmsMsg( "Sound init failed!\n" );
						return false;
					}					
				}
				
				if(!music.loadStream2((char *)e->fileData, e->fileSize))
				{
					dmsMsg( "Music load failed!\n" );
					return false;
				}
			}

			// Load T3D as 3D-objects
			if(strstr(strlwr(e->fileName), ".t3d"))
			{
				if(!oManager->addObjectFromMemory(e->fileName, e->fileData, e->fileSize)) return false;
			}
		}

		dmsLoadBar( 0.5f*(i / (float)pak.getFileCount()) );

	}

	return true;
}

extern "C" __declspec(dllexport) bool dmsReadDir(char *name)
{
   string target = name;
   WIN32_FIND_DATA fileData;
   HANDLE find = NULL;

   target += "\\*.*";
   find = FindFirstFile((char *)target.c_str(), &fileData);
   if(find == INVALID_HANDLE_VALUE) return false;

	while(find != INVALID_HANDLE_VALUE || GetLastError() == ERROR_NO_MORE_FILES)
   {
		   if(     strcmp(fileData.cFileName, ".") != 0 &&
				   strcmp(fileData.cFileName, "..") != 0 &&
				   !( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) &&
				   !( fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ) )
		   {

				   printf("Read file %s \n", fileData.cFileName);

				   char buffer[512] = {0};
				   memcpy(buffer, name, strlen(name));
				   lstrcat(buffer, "\\");
				   lstrcat(buffer, fileData.cFileName);

					// Load PCX file as texture
					if(strstr(strlwr(fileData.cFileName), ".pcx"))
					{						
					  if(!tManager->addTexture(buffer, fileData.cFileName, PCX)) return false;
					}

					// Load TGA file as texture
					if(strstr(strlwr(fileData.cFileName), ".tga"))
					{						
					  if(!tManager->addTexture(buffer, fileData.cFileName, TGA)) return false;
					}

					// Load JPG file as texture
					if(strstr(strlwr(fileData.cFileName), ".jpg"))
					{						
					  if(!tManager->addTexture(buffer, fileData.cFileName, JPG)) return false;
					}

					// Load PNG file as texture
					if(strstr(strlwr(fileData.cFileName), ".png"))
					{						
					  if(!tManager->addTexture(buffer, fileData.cFileName, PNG)) return false;
					}

				   // Load music
				   if(strstr(strlwr(fileData.cFileName), ".mp3") || strstr(strlwr(fileData.cFileName), ".ogg"))
				   {
						if(sound)
						{
							if(!sound->init())
							{
								dmsMsg( "Sound init failed!\n" );
								return false;
							}					
						}
						
						if(!music.loadStream(buffer))
						{
							dmsMsg( "Music load failed!\n" );
							return false;
						}
				   }

		   			// Load T3D as 3D-objects
					if(strstr(strlwr(fileData.cFileName), ".t3d"))
					{
						if(!oManager->addObject(buffer, fileData.cFileName)) return false;
					}

		   }

		   if(!FindNextFile(find, &fileData)) break;
	   }

	FindClose(find);

	return true;
}


extern "C" __declspec(dllexport) void dmsInitFrameBuffer(unsigned int width, unsigned int height)
{
	frameBuffer = new unsigned int[ width * height ];

	if( !frameBuffer )
	{
		throw "dmsInitFrameBuffer error: Couldn't allocate memory!";		
	}
}

extern "C" __declspec(dllexport) unsigned int *dmsGetFrameBuffer()
{
	return frameBuffer;
}


// draw 2d loadbar - status values [0.0f..1.0f]
extern "C" __declspec(dllexport) void dmsLoadBar(float status) {

	// Process messages while loading
	MSG msg = {0};
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	// k‰sittele msg t‰ss‰, jos halutaan ett‰ k‰ytt‰j‰ voi quitata kesken loaderin
	TranslateMessage(&msg);
	DispatchMessage(&msg);

	float i = status;
	if(status<0) status = 0.0f;
	if(status>1) status = 1.0f;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0, 800, 600, 0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glLoadIdentity();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
		/*
		const int sx = 150;
		const int sy = 285;
		const int ex = sx+500*i;
		const int maxx = 650;
		const int ey = 315;
		*/
		const int sx = 300;			// start x
		const int sy = 298;			// start y
		const int ex = sx+200*i;	// nyt - x
		const int maxx = 500;		// maksimi - x 
		const int ey = 302;			// end y

		float fade_out = 1-(float)(status-0.55f)/(1.0f-0.55f); 
		if(fade_out > 1.0f) fade_out = 1.0f;

		glColor3f(fade_out*0.3f,fade_out*0.3f,fade_out*0.3f);
		glDisable(GL_TEXTURE_2D);

		glColor3f(fade_out*0.6f,fade_out*0.6f,fade_out*0.6f);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINE_STRIP);
			glVertex3f( sx-5, sy-5 , 0);
			glVertex3f( maxx+5, sy-5 , 0);
			glVertex3f( maxx+5, ey+5 , 0);
			glVertex3f( sx-5, ey+5 , 0);
			glVertex3f( sx-5, sy-5 , 0);
		glEnd();
		glEnable(GL_TEXTURE_2D);

		glColor3f(fade_out*0.3f,fade_out*0.3f,fade_out*0.3f);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glVertex3f( sx, sy , 0);
			glVertex3f( ex, sy , 0);
			glVertex3f( ex, ey , 0);
			glVertex3f( sx, ey , 0);
		glEnd();
		glEnable(GL_TEXTURE_2D);

		glColor3f(1,1,1);
		
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	SwapBuffers(glWindow.getHDC());

}

extern "C" __declspec(dllexport) void dmsResetViewport() 
{
	glSystem.resetViewport();
}

extern "C" __declspec(dllexport) void dmsLogStateGL() 
{
	dmsMsg("*** dmsLogStateGL start ***\n");

	GLenum errCode;
	const GLubyte *errString;

	if ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		dmsMsg("OpenGL Error: %s\n", errString);
	} else 
		dmsMsg("glGetError()) returned GL_NO_ERROR \n");

	GLint r, g, b, a, depth, sten, aux, dbl;
	glGetIntegerv(GL_RED_BITS, &r);
	glGetIntegerv(GL_GREEN_BITS, &g);
	glGetIntegerv(GL_BLUE_BITS, &b);
	glGetIntegerv(GL_ALPHA_BITS, &a);
	glGetIntegerv(GL_DEPTH_BITS, &depth);
	glGetIntegerv(GL_STENCIL_BITS, &sten);
	glGetIntegerv(GL_AUX_BUFFERS, &aux);
	glGetIntegerv(GL_DOUBLEBUFFER, &dbl);
	dmsMsg("Framebuffer: rgba %d %d %d %d, depth %d, stencil %d, aux bfr %d, double bfr %d\n",
	r, g, b, a, depth, sten, aux, dbl);

	GLint a_test, a_func; float a_ref;
	glGetIntegerv(GL_ALPHA_TEST, &a_test);
	glGetIntegerv(GL_ALPHA_TEST_FUNC, &a_func);
	glGetFloatv(GL_ALPHA_TEST_REF, &a_ref);
	dmsMsg("GL_ALPHA_TEST, _FUNC, _REF: %d, func %04x ref %f\n", a_test, a_func, a_ref);

	GLint blend, b_src, b_equ, b_dst;
	GLfloat b_c[4];
	glGetIntegerv(GL_BLEND, &blend);
	glGetIntegerv(GL_BLEND_SRC, &b_src);
	glGetIntegerv(GL_BLEND_EQUATION, &b_equ);
	glGetIntegerv(GL_BLEND_DST, &b_dst);
	glGetFloatv(GL_BLEND_COLOR, b_c);
	dmsMsg("GL_BLEND: %d, SRC %04x EQUATION %04x DST %04x COLOR %.2f %.2f %.2f %.2f\n",
	blend, b_src, b_equ, b_dst, b_c[0], b_c[1], b_c[2], b_c[3]);

	GLint logic, logmode, mask[4], cull, cullmode, front, draw;
	glGetIntegerv(GL_COLOR_LOGIC_OP, &logic);
	glGetIntegerv(GL_LOGIC_OP_MODE, &logmode);
	glGetIntegerv(GL_COLOR_WRITEMASK, mask);
	glGetIntegerv(GL_CULL_FACE, &cull);
	glGetIntegerv(GL_CULL_FACE_MODE, &cullmode);
	glGetIntegerv(GL_FRONT_FACE, &front);
	glGetIntegerv(GL_DRAW_BUFFER, &draw);
	dmsMsg("GL_COLOR_LOGIC_OP %d GL_LOGIC_OP_MODE %04x, GL_COLOR_WRITEMASK %d %d %d %d, GL_CULL_FACE %d GL_CULL_FACE_MODE %04x GL_FRONT_FACE %04x, GL_DRAW_BUFFER %04x\n",
	logic, logmode, mask[0], mask[1], mask[2], mask[3], cull, cullmode, front, draw);

	dmsMsg("*** dmsLogStateGL end ***\n");
}

extern "C" __declspec(dllexport) int dmsGetMouseX() 
{
	return glWindow.mouseX;
}

extern "C" __declspec(dllexport) int dmsGetMouseY() 
{
	return glWindow.mouseY;
}

extern "C" __declspec(dllexport) bool dmsGetMouseLeft() 
{
	return glWindow.leftMouse;
}

extern "C" __declspec(dllexport) bool dmsGetMouseRight() 
{
	return glWindow.rightMouse;
}

extern "C" __declspec(dllexport) bool dmsGetKey(int i) 
{
	return glWindow.getKey(i);
}

extern "C" __declspec(dllexport) void dmsResetEffects() 
{
	eManager->resetEffects();
}

extern "C" __declspec(dllexport) void dmsResetEffect(const char *name) 
{
	Base *e = eManager->findEffect((char*)name);
	if(e==NULL)
	{
		dmsMsg("dmsResetEffect(): Could not find effect with name %s\n", name);
		return;
	}
	eManager->resetEffect(e);
}