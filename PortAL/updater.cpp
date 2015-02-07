/*
	PortAL - GUIPro Project ( http://obsidev.github.io/guipro/ )

	Author : Glatigny J�r�me <jerome@obsidev.com> - http://www.obsidev.com/

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

#include "updater.h"
#include "main.h"
#include "common.h"
#include "config.h"

/* ------------------------------------------------------------------------------------------------- */

void checkGuiproVersion() {
	// http://sourceforge.net/api/file/index/project-id/190801/mtime/desc/limit/20/rss?path=Portal
	ShellExecute(g_hwndMain, TEXT("open"), L"http://obsidev.github.io/guipro/", NULL, NULL, SW_SHOW);
}