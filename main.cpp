//-------------------------------------------------------
//	Defines
//-------------------------------------------------------

// Changes title screen and adds fadeout
#define NOT_FINAL

// This extracts MFC stuff off
#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN           

//-------------------------------------------------------
//	Headers
//-------------------------------------------------------

#include <windows.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"

#include "effects/neonsade.hpp"
#include "effects/tanssilattia.hpp"
#include "effects/kuutio.hpp"
#include "effects/starfield.hpp"
#include "effects/siluetti.hpp"
#include "effects/rekursio.hpp"
#include "effects/kareet.hpp"
#include "effects/sade.hpp"
#include "effects/sauhu.hpp"
#include "effects/pikkuspiraalit.hpp"
#include "effects/nauhat.hpp"
#include "effects/psyko.hpp"
#include "effects/frustumtesti.hpp"
#include "effects/alku.hpp"
#include "effects/loppu.hpp"
#include "effects/laser.hpp"
#include "effects/miami.hpp"
#include "effects/noise1.hpp"

#include "externs.hpp"
#include "config.hpp"
#include "extension_functions.hpp"

#include "primitives.hpp"

//#define _DEBUG
#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif


using namespace TRACTION_DEMOTRACTOR;

Ext glExt;
PostProc filter;
ShaderHolder shaders;
BPM *beat;
BPM *beat2;
BPM *beat4;
FrustumCuller *cull;
Vector3 clearcol;
Writer *writer;

CameraHolder *cam;

Vector3 getKasariColor()
{
    Texture *colors;
    if (rand()%2)
        colors = dmsGetTexture("texture_11_orig.jpg");
    else
        colors = dmsGetTexture("texture_05.jpg");

    unsigned int *colordata = colors->getImgData();
    int texsize = colors->getWidth() * colors->getHeight();

    int c = colordata[rand()%texsize];
    const float div = 255.0f;
    float cb = (c&0xFF)/div;
    float cg = ((c>>8)&0xFF)/div;
    float cr = ((c>>16)&0xFF)/div;

    Vector3 color = Vector3(cb, cg, cr);//.normalize();
/*    float cl = color.length();
    const float minclen = 0.7f;
    if (cl < minclen)
        color *= 1.0f/cl;
*/
    return color;



}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{	

    int i = 0;
	int rewind_dir;
	rewind_dir = 0;	

	// Stores messages that windows sends to the application
	MSG msg = {0};			
	HDC hdc = NULL;
	bool done = false;

	clearcol = Vector3(0,0,0);
    
	try
	{
//	    dmsMakePAK("resources", "data.pak");
//		dmsSetLogging (true);

        Config cfg;
		cfg.run(); 
		if(cfg.getRunFlag())
        {

#define _LOAD_FROM_DIR
#ifdef _LOAD_FROM_DIR
			dmsInitDummyEx(cfg.getScreenX(), cfg.getScreenY(), cfg.getBpp(), cfg.getFullscreen(), 
				  cfg.getSound(), cfg.getVsync(), cfg.getOnTop(), cfg.getFsaa());
			dmsReadDir("resources");

#else
			dmsInitEx(cfg.getScreenX(), cfg.getScreenY(), cfg.getBpp(), cfg.getFullscreen(), 
					  cfg.getSound(), cfg.getVsync(), cfg.getOnTop(), cfg.getFsaa()/*, cfg.getAspectRatio()*/, "data.pak");
#endif

            // Asetetaan ikoni ikkunalle
			SendMessage(dmsGetHWND(),WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));


            dmsAddRenderToTexture(512, 512, "render512_0");
            dmsAddRenderToTexture(512, 512, "render512_1");

            dmsUploadTextures();
            Primitives::init();
						
			glExt.init();
			shaders.init();
        	cam = new CameraHolder(4);//kuinka monta kameraa

            const int campoints0 = 114;//16;
            const int campoints1 = 15;//16;
            const int campoints2 = 9;//16;
            const int campoints3 = 11;//16;
            cam->initCamera(0, 0, 300000); 
            cam->initCamera(1, 40000, 72000); 
            cam->initCamera(2, 168000, 200000); 
            cam->initCamera(3, 8000, 26000); 

            srand(60);
            for (i = 0; i < campoints0; i++)
            {
                //51 = neonsade
/*
                if (i == 100 )
                {
                    srand(15167);
                }
*/
                Vector3 campoint = Mathematics::randVectSphere()*(4+Mathematics::randFloat()*4.5f);
                Vector3 camtarget = Mathematics::randVectSphere()*2.0f;

                if (campoint.y < 1.5f)
                {
                    campoint.y = fabsf(campoint.y);

                }
                cam->addCameraPoint(0, campoint);
                cam->addCameraTargetPoint(0, camtarget);


            }
            cam->finalizeCamera(0);
            cam->arcLengthParametrizeCamera(0);
            cam->arcLengthParametrizeCameraTarget(0);

            srand(6661);
            for (i = 0; i < campoints1; i++)
            {
                Vector3 campoint = Mathematics::randVectSphere()*(1+Mathematics::randFloat()*1.5f);
                Vector3 camtarget = campoint + Vector3(4, 0, 0) + Mathematics::randVectSphere()*1.0f;

                if (campoint.y < 1.5f)
                {
                    campoint.y = fabsf(campoint.y);

                }
                cam->addCameraPoint(1, campoint);
                cam->addCameraTargetPoint(1, camtarget);
            }
            cam->finalizeCamera(1);
            cam->arcLengthParametrizeCamera(1);
            cam->arcLengthParametrizeCameraTarget(1);

            srand(611); //seed 5 is perfect!!
            for (i = 0; i < campoints2; i++)
            {
                Vector3 campoint = Mathematics::randVectSphere()*(3.7f+Mathematics::randFloat()*3.5f);
                Vector3 camtarget = Mathematics::randVectSphere()*1.0f;

                cam->addCameraPoint(2, campoint);
                cam->addCameraTargetPoint(2, camtarget);
            }
            cam->finalizeCamera(2);
            cam->arcLengthParametrizeCamera(2);
            cam->arcLengthParametrizeCameraTarget(2);


            srand(51); 
            for (i = 0; i < campoints3; i++)
            {
                Vector3 campoint = Mathematics::randVectSphere()*(3.7f+Mathematics::randFloat()*3.5f);
                Vector3 camtarget = Mathematics::randVectSphere()*1.0f;

                cam->addCameraPoint(3, campoint);
                cam->addCameraTargetPoint(3, camtarget);
            }
            cam->finalizeCamera(3);
            cam->arcLengthParametrizeCamera(3);
            cam->arcLengthParametrizeCameraTarget(3);


            //isompi piirretään ensin
            beat = new BPM(120, 0);
            beat2 = new BPM(60, 0);
            beat4 = new BPM(30, 0);


            cull = new FrustumCuller();
            writer = new Writer("broadway_outlined.png");


            // WAMMA GREETSIT - http://pouet.net/nfo.php?which=30755


            //starfieldiin pyrstötähtiä
            //tunneli jossa viivoja (?)
            //jutut, jotka leikkaavat vedenpintaa ja tekevät rinkuloita (vrt kareet)
            //tanssilattiasta nousevia juttuja
            //verkosto
            //kareisiin menemään maata pitkin hohtavia asioita
            //http://www.youtube.com/watch?v=8J_0tE1nYAk

            //käyttämättä - pikkuspiraalit
            
//            dmsAddEffect(24000, 40000, 100,"nauhat", new Nauhat());
//            dmsAddEffect(24000, 40000, 50, "lattia", new Pikkuspiraalit());
//            dmsAddEffect(38000, 74000, 50, "neonpisarat", new Starfield());

//            dmsAddEffect(0, 50000, 0, "frustumtesti", new FrustumTesti());


            //laserefekti!!

            dmsAddEffect(0, 14000, 160, "alku", new Alku());
            dmsAddEffect(8000, 25000, 50000, "sil", new Siluetti());
            dmsAddEffect(8000, 26000, 1000, "laser", new Laser());
            dmsAddEffect(7000, 26000, 100, "laser", new Noise1(0.0f, 0.1f, 0.07f));
            dmsAddEffect(24000, 40000, 100, "laser", new Noise1(0.0f, 0.1f, 0.05f));
            dmsAddEffect(24000, 40000, 4000, "lattia", new Tanssilattia());
            dmsAddEffect(40000, 72000, 6666, "miami vice", new Miami());
            dmsAddEffect(72000, 104000, 250, "neonpisarat", new Neonsade());
//            dmsAddEffect(72000, 104000, 0, "sade", new Sade(0));
            dmsAddEffect(104000, 136000, 550, "neonpisarat", new Kuutio());
            dmsAddEffect(134000, 168000, 80, "rekursio", new Kareet()); //rekursio
//            dmsAddEffect(136000, 168000, 0, "sade", new Sade(0));
//            dmsAddEffect(167000, 199800, 50000, "sil", new Siluetti());
            dmsAddEffect(163000, 199200, 50, "sauhu", new Sauhu());
            dmsAddEffect(165000, 200200, 150, "pikkuspiraalit", new Psyko());
            dmsAddEffect(168000, 200000, 100, "laser", new Noise1(0.0f, 0.1f, 0.07f));
            dmsAddEffect(164800, 205500, 0, "sauhu", new Loppu());

            //            dmsAddEffect(0, 168000, 1, "sade", new Sade());
            //dmsAddEffect(104000, 136000, 50, "neonpisarat", new Psyko());

			dmsInitEffects();
			
/*
  Engine:

*/
			// Tää bugaa
			//dmsSetGamma(cfg.getGamma());
			dmsInitTimer();
			dmsPlaySong(true);
		}

        else
		{
			done = true;
		}

		// Demo loop
		while(!done)
		{

			// Check for Windows messages in queue
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{

				//If app was closed send a note to the demo to stop the Demo loop
				if(msg.message == WM_QUIT)
				{
					//done = true;
				} else if(msg.message == WM_KEYDOWN) {
					const float jump = 1000.0f;
					if(msg.wParam == VK_ESCAPE)		
                    {
                        done = true;
                    }
					else if(msg.wParam == VK_LEFT)	rewind_dir = -1;
					else if(msg.wParam == VK_RIGHT) rewind_dir = 1;
				} else if(msg.message == WM_KEYUP) {
					if(msg.wParam == VK_LEFT || msg.wParam == VK_RIGHT) 
						rewind_dir = 0;

				} else {
					// Other messages are handled by Windows own handlers
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			// No messages left, we can do some own code now which means
			// actually running the demo :)
			else
			{	
				dmsUpdateTimer();
                cam->update();
				 
				if(rewind_dir!=0) {
					dmsAdjustTime(rewind_dir*1000.0f);
				}

				glClearColor(clearcol.x,clearcol.y,clearcol.z,0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				dmsRun();


                    char buf[256] = {0};
					sprintf(buf, "Time: %f s | FPS: %0.2f", dmsGetModulePosition() / 1000.0f, dmsGetFPS() );
					dmsSetWindowTitle(buf);

				if (dmsGetModulePosition() > 206000) 
					done = true;

				hdc = dmsGetHDC();
				SwapBuffers(hdc);		
			}
		}	
	}
	catch(const char *msg)
	{
		dmsMsg("Exception: %s\n", msg);
	}

	glExt.deinit();
	shaders.deinit();
	
    delete beat;
    delete beat2;
    delete beat4;
    delete cull;

	dmsSetGamma(0);
	dmsShutDown();

	// This application is done and we let the Windows know that
	return msg.wParam;
}

