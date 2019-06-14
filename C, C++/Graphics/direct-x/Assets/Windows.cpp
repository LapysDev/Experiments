/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Windows.cpp																			  *
 *	Copyright 2011 PlanetChili.net														  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include <Windows.h>
#include <wchar.h>
#include "Game.h"
#include "resource.h"

static KeyboardServer kServ;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpPressed();
				break;
			case VK_DOWN:
				kServ.OnDownPressed();
				break;
			case VK_LEFT:
				kServ.OnLeftPressed();
				break;
			case VK_RIGHT:
				kServ.OnRightPressed();
				break;
			case VK_SPACE:
                kServ.OnSpacePressed();
				break;
			case VK_RETURN:
				kServ.OnEnterPressed();
				break;
			}
			break;
		case WM_KEYUP:
   			switch( wParam )
			{
			case VK_UP:
				kServ.OnUpReleased();
				break;
			case VK_DOWN:
				kServ.OnDownReleased();
				break;
			case VK_LEFT:
				kServ.OnLeftReleased();
				break;
			case VK_RIGHT:
				kServ.OnRightReleased();
				break;
			case VK_SPACE:
				kServ.OnSpaceReleased();
				break;
			case VK_RETURN:
				kServ.OnEnterReleased();
				break;
			}
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR,INT )
{
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ),CS_CLASSDC,MsgProc,0,0,
                      GetModuleHandle( NULL ),NULL,NULL,NULL,NULL,
                      L"Chili DirectX Framework Window",NULL };
    wc.hIconSm = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON16 ),IMAGE_ICON,16,16,0 );
	wc.hIcon   = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON32 ),IMAGE_ICON,32,32,0 );
    RegisterClassEx( &wc );
	
	RECT wr;
	wr.left = 100;
	wr.right = 800 + wr.left;
	wr.top = 100;
	wr.bottom = 600 + wr.top;
	AdjustWindowRect( &wr,WS_OVERLAPPEDWINDOW,FALSE );
    HWND hWnd = CreateWindowW( L"Chili DirectX Framework Window",L"Chili DirectX Framework",
                              WS_OVERLAPPEDWINDOW,wr.left,wr.top,wr.right-wr.left,wr.bottom-wr.top,
                              NULL,NULL,wc.hInstance,NULL );

    ShowWindow( hWnd,SW_SHOWDEFAULT );
    UpdateWindow( hWnd );

	Game theGame( hWnd,kServ );
	
    MSG msg;
    ZeroMemory( &msg,sizeof( msg ) );
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg,NULL,0,0,PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
		{
			theGame.Go();
		}
    }

    UnregisterClass( L"Chili DirectX Framework Window",wc.hInstance );
    return 0;
}