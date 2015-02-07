/*
	HulK - GUIPro Project ( http://obsidev.github.io/guipro/ )

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

#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include "iconize.h"

void InitMenuVars();

void ShowTrayMenu();
void ShowIconizeMenu(UINT id);
BOOL insertProg(HMENU hMenu, UINT uItemID, TrayIconElem *elem);

void OnMeasureItem(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif /* MENU_H */
