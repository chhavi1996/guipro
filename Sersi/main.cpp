/*  Sersi - GUIPro Project ( http://guipro.sourceforge.net/ )

    Author : DarkSage  aka  Glatigny Jerome <darksage@darksage.info>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "main.h"
#include "service.h"
#include "common.h"
#include "registry.h"
#include "process.h"
#include <stdio.h>

bool check_config = false;
std::list<struct SersiProg*> plist;

/* ------------------------------------------------------------------------------------------------- */

#ifdef WINDOWMODE

#include "gui.h"

const WCHAR g_szMainWnd[]		= L"_GUIPROSRV90_Services_MainWnd_";
const WCHAR g_szWindowName[]	= L"Sersi";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if( GuiProInServiceInstalled() && !GuiProInServiceStarted() )
	{
		SERVICE_TABLE_ENTRY Table[] = {{MY_SERVICE_NAME,ServiceMain},{NULL,NULL}};
		if( StartServiceCtrlDispatcher(Table) != 0 )
		{
			return 0;
		}
	}
#ifndef NDEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
flag |= _CRTDBG_LEAK_CHECK_DF;
_CrtSetDbgFlag(flag);
#endif

	// Keep the instance handle of the application
	g_hInst = hInstance;

	// Creation and registration of the application class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC) MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_BACKGROUND);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= g_szMainWnd;
	wcex.hIconSm		= NULL;

	if( !RegisterClassEx(&wcex) )
		return 1;

	if( !CreateWindowEx(WS_EX_WINDOWEDGE, g_szMainWnd, g_szWindowName, 
						WS_CAPTION /*| WS_THICKFRAME*/ | WS_MINIMIZEBOX | WS_SYSMENU | WS_OVERLAPPED, 
						CW_USEDEFAULT, CW_USEDEFAULT, 530, 300, NULL, NULL, g_hInst, NULL) )
		return 1;

	// Main loop.
	// Get and send messages for the application.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

/* ------------------------------------------------------------------------------------------------- */

#else

void showHelp()
{
	wprintf(L"\tOptions\n");
	wprintf(L"\t\t/i\tinstall\n");
	wprintf(L"\t\t/u\tuninstall\n");
	wprintf(L"\t\t/check\tcheck the configuration\n");
	wprintf(L"\t\t/run\ttest the configuration.\n");
	wprintf(L"\t\t/start\tstart the service\n");
	wprintf(L"\t\t/stop\tstop the service\n");
	wprintf(L"\t\t/help\tthis help");
}

void wmain(int argc, char* argv[])
{
	if( argc > 1 )
	{
		wprintf(GPS_HEADER);

		if( !strcmp( argv[1], "/i") )
		{
			if( InstallService() )
			{
				wprintf(GPS_INSTALL_SUCCESS);
			}
			else
			{
				wprintf(GPS_INSTALL_FAILURE);
			}
			return;
		}

		if( !strcmp( argv[1], "/u") )
		{
			if( UninstallService() )
			{
				wprintf(GPS_UNINSTALL_SUCCESS);
			}
			else
			{
				wprintf(GPS_UNINSTALL_FAILURE);
			}
			return;
		}

		if( !strcmp( argv[1], "/check") )
		{
			wprintf(L"Check Configuration\n");
			check_config = true;
			DoService();
			return;
		}

		if( !strcmp( argv[1], "/run") )
		{
			char c;

			check_config = false;
			DoService();

			// Create a pause
			wprintf(L"Press enter to stop applications and GUIPro Services...");
			scanf("%c", &c);
			
			endAllChildren();
			
			return;
		}

		if( !strcmp( argv[1], "/start") )
		{
			GuiProStartService();
			return;
		}

		if( !strcmp( argv[1], "/stop") )
		{
			GuiProStopService();
			return;
		}

		showHelp();
		return;
	}

	if( GuiProInServiceInstalled() && !GuiProInServiceStarted() )
	{
		SERVICE_TABLE_ENTRY Table[] = {{MY_SERVICE_NAME,ServiceMain},{NULL,NULL}};
		StartServiceCtrlDispatcher(Table);
	}
	else
	{
		wprintf(GPS_HEADER);
		showHelp();
	}
    return;
}

#endif

/* ------------------------------------------------------------------------------------------------- */

void DoService()
{
	plist.clear();
	std::list<wchar_t*> programs = listKeys();

	for( std::list<wchar_t*>::iterator i = programs.begin(); i != programs.end(); i++ )
	{
		process( (*i) );
		free( (*i) );
	}
	FlushMemory();
}

/* ------------------------------------------------------------------------------------------------- */
