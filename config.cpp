//-------------------------------------------------------
// Includes
//-------------------------------------------------------

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "resource.h"
#include "config.hpp"

//-------------------------------------------------------
//	Globals and static members
//-------------------------------------------------------

int Config::screenX;
int Config::screenY;
int Config::bpp;
int Config::gamma;
int Config::fsaa;
int Config::aspectratio;
bool Config::fullscreen;
bool Config::sound;
bool Config::vsync;
bool Config::runFlag;
bool Config::anaglyphic;
bool Config::alwaysOnTop;

//-------------------------------------------------------
//	Constructors and Destructor
//-------------------------------------------------------

Config::Config()
{
	screenX = 640;
	screenY = 480;
	bpp = 32;
	gamma = 0;
	fullscreen = false;
	sound = false;
	vsync = false;
	runFlag = false;
    anaglyphic = false;
	alwaysOnTop = false;
	fsaa = 2;
	aspectratio = 0;
}

Config::~Config()
{
}

//-------------------------------------------------------
//	Public functions
//-------------------------------------------------------

bool Config::run()
{	
	if(DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SETUPDLG), NULL, (DLGPROC)ConfigProc) == 1)
	{		
		return false;
	}

	if(!getRunFlag()) 
		return false;

	return true;
}

int Config::getScreenX()
{
	return screenX;
}

int Config::getScreenY()
{
	return screenY;
}

int Config::getBpp()
{
	return bpp;
}

int Config::getGamma()
{
	return gamma;
}
int Config::getFsaa() 
{
	return fsaa;
}
bool Config::getFullscreen()
{
	return fullscreen;
}

bool Config::getSound()
{
	return sound;
}

bool Config::getVsync()
{
	return vsync;
}
bool Config::getAnaglyphic()
{
	return anaglyphic;
}
bool Config::getOnTop()
{
	return alwaysOnTop;
}

bool Config::getRunFlag()
{
	return runFlag;
}

int Config::getAspectRatio()
{
	return aspectratio;
}

//-------------------------------------------------------
//	Dialog procedure - handles inputs
//-------------------------------------------------------

CALLBACK Config::ConfigProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch(uMsg)
	{				
		case WM_INITDIALOG:
		{				
			InitCommonControls();
			
			RECT rect, dlgRect;
			HWND dlg;
			
			// Center the dialog box
			dlg = GetDesktopWindow();			
			if(dlg)
			{				
				GetWindowRect(dlg, &rect);
				GetWindowRect(hwnd, &dlgRect);
				SetWindowPos(hwnd, HWND_TOPMOST, (rect.right/2) - ((dlgRect.right - dlgRect.left) / 2), (rect.bottom/2) - ((dlgRect.bottom - dlgRect.top) / 2), 0, 0, SWP_NOSIZE);
			}			


			HWND hwndList = GetDlgItem(hwnd, IDC_ASPECTRATIO);
			SendMessage(hwndList,CB_ADDSTRING,0,(LPARAM)(LPCSTR)"4:3");
			SendMessage(hwndList,CB_ADDSTRING,1,(LPARAM)(LPCSTR)"16:10");
			SendMessage(hwndList,CB_ADDSTRING,2,(LPARAM)(LPCSTR)"16:9");
			SendMessage(hwndList,CB_SETCURSEL,0,0); // LAST INDEX MUST BE ZERO
			aspectratio = 0;

			hwndList = GetDlgItem(hwnd, IDC_RESOLUTION);
			SendMessage(hwndList,CB_ADDSTRING,0,(LPARAM)(LPCSTR)"1280x1024");
			SendMessage(hwndList,CB_ADDSTRING,1,(LPARAM)(LPCSTR)"1024x768");
			SendMessage(hwndList,CB_ADDSTRING,2,(LPARAM)(LPCSTR)"800x600");
			SendMessage(hwndList,CB_ADDSTRING,3,(LPARAM)(LPCSTR)"640x480");
			SendMessage(hwndList,CB_SETCURSEL,1,0);	// LAST INDEX MUST BE ZERO
			screenX = 1024;
			screenY = 768;
			bpp = 32;

			hwndList = GetDlgItem(hwnd, IDC_FSAA);
			SendMessage(hwndList,CB_ADDSTRING,0,(LPARAM)(LPCSTR)"0");
			SendMessage(hwndList,CB_ADDSTRING,2,(LPARAM)(LPCSTR)"2");
			SendMessage(hwndList,CB_ADDSTRING,4,(LPARAM)(LPCSTR)"4");
			SendMessage(hwndList,CB_ADDSTRING,6,(LPARAM)(LPCSTR)"6");
			SendMessage(hwndList,CB_SETCURSEL,1,0); // LAST INDEX MUST BE ZERO
			fsaa = 2;

			// Initialize values
			/*
			//SendDlgItemMessage(hwnd, IDC_FSAA, WM_SETTEXT, 0, (LPARAM)"No FSAA"); 
//			SendMessage(GetDlgItem(hwnd, IDC_FSAA), (UINT) CB_SETMINVISIBLE, (WPARAM)2, 0); 

			SendMessage(GetDlgItem(hwnd, IDC_FSAA), CB_ADDSTRING, 0, (LPARAM)"No FSAA"); 
			SendMessage(GetDlgItem(hwnd, IDC_FSAA), CB_ADDSTRING, 0, (LPARAM)"FSAA 2"); 
			SendMessage(GetDlgItem(hwnd, IDC_FSAA), CB_ADDSTRING, 0, (LPARAM)"FSAA 4"); 
			SendMessage(GetDlgItem(hwnd, IDC_FSAA), CB_ADDSTRING, 0, (LPARAM)"FSAA 6"); 
			SendDlgItemMessage(hwnd, IDC_FSAA, CB_SETCURSEL, 1, 0); 	

			lResult = SendMessage(// returns LRESULT in lResult
			   (HWND) hWndControl,// handle to destination control
			   (UINT) WM_SETFONT,// message ID
			   (WPARAM) wParam,// = (WPARAM) () wParam;
			   (LPARAM) lParam// = (LPARAM) () lParam;
			);				
		*/
			// Show the dialog
			ShowWindow(hwnd, SW_SHOW);
			SetActiveWindow(hwnd);
			SetForegroundWindow(hwnd);
			SetFocus(hwnd);

			// Set icon
			SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

			// Check default values

			SendDlgItemMessage(hwnd, IDC_SOUND, BM_SETCHECK, wParam, 0);
			SendDlgItemMessage(hwnd, IDC_VSYNC, BM_SETCHECK, wParam, 0);
			SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_SETCHECK, wParam, 0);
			
			// Setup gamma slider values [-255..255]
			//SendDlgItemMessage(hwnd, IDC_GAMMA, TBM_SETRANGE, true, MAKELONG(-255,255));


			// Set ONTOP to disabled or enabled at startup
			if(IsDlgButtonChecked(hwnd, IDC_FULLSCREEN)==BST_CHECKED)
				EnableWindow(GetDlgItem(hwnd, IDC_ONTOP), FALSE); 
			 else 
				EnableWindow(GetDlgItem(hwnd, IDC_ONTOP), TRUE); 



		} break;

		case WM_COMMAND:
		{
			
			if(IsDlgButtonChecked(hwnd, IDC_FULLSCREEN)==BST_CHECKED)
				EnableWindow(GetDlgItem(hwnd, IDC_ONTOP), FALSE); 
			 else 
				EnableWindow(GetDlgItem(hwnd, IDC_ONTOP), TRUE); 
			
			
			switch(LOWORD(wParam))
			{
				case IDC_ASPECTRATIO:
				
					if(HIWORD(wParam) == CBN_SELCHANGE)
						aspectratio = SendMessage(GetDlgItem(hwnd, IDC_ASPECTRATIO), CB_GETCURSEL, 0, 0);
					break;

				case IDC_RESOLUTION:

					if(HIWORD(wParam) == CBN_SELCHANGE)
					{
						int selection = SendMessage(GetDlgItem(hwnd, IDC_RESOLUTION), CB_GETCURSEL, 0, 0);
							
							if(selection == 0) 
							{
								screenX = 1280;
								screenY = 1024;
								bpp = 32;

							} else if(selection == 1)
							{
								screenX = 1024;
								screenY = 768;
								bpp = 32;
							
							} else if(selection == 2)
							{

								screenX = 800;
								screenY = 600;
								bpp = 32;

							} else if(selection == 3)
							{

								screenX = 640;
								screenY = 480;
								bpp = 32;
							} 

					}
					break;

				case IDC_FSAA:

					if(HIWORD(wParam) == CBN_SELCHANGE)
					{
						fsaa = SendMessage(GetDlgItem(hwnd, IDC_FSAA), CB_GETCURSEL, 0, 0);
					}

					break;
				case IDOK:
				{					
/*
					if (SendDlgItemMessage(hwnd, IDC_FSAA0, BM_GETSTATE, 0, 0)==BST_CHECKED)
					{
						fsaa = 0;
					}
					if (SendDlgItemMessage(hwnd, IDC_FSAA2, BM_GETSTATE, 0, 0)==BST_CHECKED)
					{
						fsaa = 2;
					}
					if (SendDlgItemMessage(hwnd, IDC_FSAA4, BM_GETSTATE, 0, 0)==BST_CHECKED)
					{
						fsaa = 4;
					}
					if (SendDlgItemMessage(hwnd, IDC_FSAA6, BM_GETSTATE, 0, 0)==BST_CHECKED)
					{
						fsaa = 6;
					}
					if(SendDlgItemMessage(hwnd, IDC_1280, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						screenX = 1280;
						screenY = 1024;
						bpp = 32;
					}

					if(SendDlgItemMessage(hwnd, IDC_1024, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						screenX = 1024;
						screenY = 768;
						bpp = 32;
					}

					if(SendDlgItemMessage(hwnd, IDC_800, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						screenX = 800;
						screenY = 600;
						bpp = 32;
					}

					if(SendDlgItemMessage(hwnd, IDC_640, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						screenX = 640;
						screenY = 480;
						bpp = 32;
					}

					if(SendDlgItemMessage(hwnd, IDC_4_3, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						aspectratio = 0;
					}

					if(SendDlgItemMessage(hwnd, IDC_16_10, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						aspectratio = 1;
					}

					if(SendDlgItemMessage(hwnd, IDC_16_9, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						aspectratio = 2;
					}
*/


					
					if(SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						fullscreen = true;
					} 

					if(SendDlgItemMessage(hwnd, IDC_SOUND, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						sound = true;
					}

					if(SendDlgItemMessage(hwnd, IDC_VSYNC, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						vsync = true;
					}
					if(SendDlgItemMessage(hwnd, IDC_ANAGLYPHIC, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						anaglyphic = true;
					}
					
					if(SendDlgItemMessage(hwnd, IDC_ONTOP, BM_GETSTATE, 0, 0) == BST_CHECKED) 
					{
						alwaysOnTop= true;
					}
					
                    //fsaa = SendDlgItemMessage(hwnd, IDC_FSAA, LB_GETCURSEL, 0,0);
					//SendMessage(hwnd, LB_GETTEXT, SendMessage(hwnd, LB_GETCURSEL, 0, 0), (LPARAM) achTemp); 

					gamma = SendDlgItemMessage(hwnd, IDC_GAMMA, TBM_GETPOS, 0, 0);
					
					Config::runFlag = true;
					EndDialog(hwnd, 0);
				} break;
				
				case IDCANCEL:
				{
					Config::runFlag = false;
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				} break;

			} break;

		} break;

		case WM_DESTROY:
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		} break;
		
		case WM_CLOSE:
		{						
			EndDialog(hwnd, 0);
		} 
		break;		
	}

	

	return 0;
}
