#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include "parser.hpp"
#include "opengl.hpp"
#include "log.hpp"
#include "timer.hpp"
#include "sound.hpp"
#include "texturemanager.hpp"
#include "effectmanager.hpp"
#include "fontmanager.hpp"
#include "objectmanager.hpp"
//#include "lista.hpp"
#include "path.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

extern "C" __declspec(dllexport) void dmsMsg(const char *text, ...);

namespace TRACTION_DEMOTRACTOR
{
	extern "C" __declspec(dllexport) void dmsResetViewport();
	
	
	extern "C" __declspec(dllexport) void dmsSetLogging(bool f);
	extern "C" __declspec(dllexport) bool dmsSetupInstances();
	extern "C" __declspec(dllexport) bool dmsInit();
	extern "C" __declspec(dllexport) bool dmsInitEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync, bool onTop, int fsaa, char *pakFile);
	extern "C" __declspec(dllexport) bool dmsInitDummyEx(int screenX, int screenY, int bpp, bool fullscreen, bool soundFlag, bool vsync, bool onTop, int fsaa);
	extern "C" __declspec(dllexport) bool dmsOnFocus();
	extern "C" __declspec(dllexport) void dmsSetGamma(int gamma);
	extern "C" __declspec(dllexport) void dmsShutDown();
	extern "C" __declspec(dllexport) void dmsCheckControls(float jump);
	extern "C" __declspec(dllexport) void dmsPerspective2D(int w, int h);
	extern "C" __declspec(dllexport) void dmsPerspective3D();
	extern "C" __declspec(dllexport) void dmsSetFOV(float f);

	extern "C" __declspec(dllexport) void dmsInitTimer();
	extern "C" __declspec(dllexport) void dmsUpdateTimer();
	extern "C" __declspec(dllexport) void dmsAdjustTime(float f);

	extern "C" __declspec(dllexport) void dmsInitSound();
	extern "C" __declspec(dllexport) void dmsLoadSong(const char *fileName);
	extern "C" __declspec(dllexport) void dmsLoadSongFromMemory(unsigned char *fileData, unsigned int fileSize);
	extern "C" __declspec(dllexport) void dmsPlaySong(bool f);
	extern "C" __declspec(dllexport) void dmsPauseSong(bool f);
	extern "C" __declspec(dllexport) bool dmsCheckSyncPoint();
	
	extern "C" __declspec(dllexport) void dmsAddTexture(const char *fileName, const char *name);
	extern "C" __declspec(dllexport) void dmsAddRenderToTexture(int width, int height, const char *name);
	extern "C" __declspec(dllexport) void dmsUploadTextures();	
	extern "C" __declspec(dllexport) void dmsBindTexture(unsigned int mode, const char *name);

	extern "C" __declspec(dllexport) void dmsAddFont(int x, int y, const char *name);

	extern "C" __declspec(dllexport) void dmsInitObjects();
	extern "C" __declspec(dllexport) void dmsAddObject(const char *fileName, const char *name);
	extern "C" __declspec(dllexport) void dmsDrawObject(const char *name);

	extern "C" __declspec(dllexport) void dmsInitEffects();
	extern "C" __declspec(dllexport) void dmsAddEffect(unsigned long st, unsigned long et, unsigned int prio, const char *name, Base *effect);
	extern "C" __declspec(dllexport) void dmsSetEffectPriority(unsigned int prio, const char *name);

	extern "C" __declspec(dllexport) void dmsRun();	
	
	extern "C" __declspec(dllexport) void dmsWrite2D(float x, float y, float a, float scale, char *fontName, char *msg);
	extern "C" __declspec(dllexport) void dmsWrite3D(float x, float y, float z, float a, char *fontName, char *msg);
	extern "C" __declspec(dllexport) void dmsWrite3DEx(float x, float y, float z, float rx, float ry, float rz, float angle, float a, char *fontName, char *msg);
	extern "C" __declspec(dllexport) void dmsSetWindowTitle(const char *msg);
	extern "C" __declspec(dllexport) void dmsDrawQuad2D();
	extern "C" __declspec(dllexport) void dmsDrawTexturedQuad2D();
	extern "C" __declspec(dllexport) void dmsDrawQuad2DEx(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
	extern "C" __declspec(dllexport) void dmsDrawTexturedQuad2DEx(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
	extern "C" __declspec(dllexport) void dmsBlending(bool blending, unsigned int src, unsigned int dst);

	extern "C" __declspec(dllexport) float dmsGetTime();
    extern "C" __declspec(dllexport) float dmsGetTimeMs();
	extern "C" __declspec(dllexport) float dmsGetDeltaTime();
	extern "C" __declspec(dllexport) void dmsGetSpectrum( float *array, int size );
	extern "C" __declspec(dllexport) void dmsGetWaveData( float *array, int size );
	extern "C" __declspec(dllexport) T3D *dmsGetObject(const char *name);
	extern "C" __declspec(dllexport) Texture *dmsGetTexture(const char *name);
	
	extern "C" __declspec(dllexport) void dmsSetTextureParameter(const char *name, unsigned int pname, float value);
	extern "C" __declspec(dllexport) void dmsSetMipMaps(const char *name, bool b);

	extern "C" __declspec(dllexport) Font *dmsGetFont(const char *name);
	extern "C" __declspec(dllexport) HDC dmsGetHDC();
	extern "C" __declspec(dllexport) HWND dmsGetHWND();
	extern "C" __declspec(dllexport) int dmsGetModulePosition();
	
	extern "C" __declspec(dllexport) int dmsGetWindowWidth();
	extern "C" __declspec(dllexport) int dmsGetWindowHeight();
	extern "C" __declspec(dllexport) float dmsGetFPS();
	
	extern "C" __declspec(dllexport) float dmsCalcPos(float value, float limit1, float limit2);
	extern "C" __declspec(dllexport) float dmsCalcSaturate(float value, float limit1, float limit2, float multiply);
	extern "C" __declspec(dllexport) float dmsRandFloat();

	extern "C" __declspec(dllexport) bool dmsMakePAK(const char *src, const char *dst);
	extern "C" __declspec(dllexport) void dmsLoadPic(char *name);
	extern "C" __declspec(dllexport) void dmsLoadBar(float status);

	extern "C" __declspec(dllexport) void dmsDrawMeter(int current, int max, float width, float height, float xpos, float ypos, float zpos);

	extern "C" __declspec(dllexport) int dmsGetWindowWidth();
	extern "C" __declspec(dllexport) int dmsGetWindowHeight();


	extern "C" __declspec(dllexport) HDC dmsGetHDC();
	extern "C" __declspec(dllexport) HWND dmsGetHWND();

    	extern "C" __declspec(dllexport) bool dmsReadSetup(char *name);
	extern "C" __declspec(dllexport) bool dmsReadPak(char *name);
	extern "C" __declspec(dllexport) bool dmsReadDir(const char *src);


	extern "C" __declspec(dllexport) void dmsInitFrameBuffer(unsigned int width, unsigned int height);
	extern "C" __declspec(dllexport) unsigned int *dmsGetFrameBuffer();


	extern "C" __declspec(dllexport) void dmsLogStateGL();
}

#endif