//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudWin32Wnd.cpp
///	@brief		Implements KWin32Wnd methods to support Window.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudInternalUIDefines.h"
#include "KudUIEnums.h"
#include "KudKeyCodes.h"
#include "KudUIDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "IGUIElement.h"
#include "IGUIRender.h"
//#include "KudD3DRender.h"
#include "KudGDIRender.h"
#include "IGUIWindow.h"
#include "KudWin32Wnd.h"
#include "KudGUISkin.h"
#include "KudLangHelper.h"

KDNAMESTART

KDNAMEGUI

//! Use global variable to save the map of HWND and window proc.
static std::map<HWND, IGUIWindow *> hWndMap;
IGUIWindow* GetWindowFromHWND(HWND hWnd)
{
	std::map<HWND, IGUIWindow *>::iterator it = hWndMap.find(hWnd);
	if (it == hWndMap.end())
		return NULL;
	return (*it).second;
}

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL	0x020A
#endif
#ifndef WHEEL_DELTA
#define WHEEL_DELTA		120
#endif

LRESULT CALLBACK KudeetWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IGUIWindow * pActive = GetWindowFromHWND(hWnd);
	if (pActive != NULL)
		return pActive->KudeetMessageProc(hWnd, message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT	KGUIWin32Wnd::KudeetMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	KDS_EVENT event;
	static SInt32 ClickCount = 0;
	if (GetCapture() != hWnd && ClickCount > 0)
		ClickCount = 0;

	struct messageMap
	{
		SInt32 group;
		UINT winMessage;
		SInt32 kdMessage;
	};

	static messageMap mouseMap[] =
	{
		{0, WM_LBUTTONDOWN, KME_LMOUSE_DOWN},
		{1, WM_LBUTTONUP,   KME_LMOUSE_UP},
		{0, WM_RBUTTONDOWN, KME_RMOUSE_DOWN},
		{1, WM_RBUTTONUP,   KME_RMOUSE_UP},
		{0, WM_MBUTTONDOWN, KME_MMOUSE_DOWN},
		{1, WM_MBUTTONUP,   KME_MMOUSE_UP},
		{2, WM_MOUSEMOVE,   KME_MOUSE_MOVED},
		{3, WM_MOUSEWHEEL,  KME_MOUSE_WHEEL},
		{-1, 0, 0}
	};

	// handle grouped events
	messageMap * m = mouseMap;
	while (m->group >=0 && m->winMessage != message )
		m += 1;

	if ( m->group >= 0 )
	{
		if ( m->group == 0 )	// down
		{
			ClickCount++;
			SetCapture(hWnd);
		}
		else if ( m->group == 1 )	// up
		{
			ClickCount--;
			if (ClickCount<1)
			{
				ClickCount=0;
				ReleaseCapture();
			}
		}

		event.EventType = KET_MOUSE;
		event.MouseEvent.Event = (KDE_EVENT_MOUSE) m->kdMessage;
		event.MouseEvent.X = (short)LOWORD(lParam);
		event.MouseEvent.Y = (short)HIWORD(lParam);
		event.MouseEvent.Shift = ((LOWORD(wParam) & MK_SHIFT) != 0);
		event.MouseEvent.Control = ((LOWORD(wParam) & MK_CONTROL) != 0);
		// left and right mouse buttons
		event.MouseEvent.ButtonStates = wParam & ( MK_LBUTTON | MK_RBUTTON);
		// middle and extra buttons
		if (wParam & MK_MBUTTON)
			event.MouseEvent.ButtonStates |= EMBSM_MIDDLE;
#if(_WIN32_WINNT >= 0x0500)
		if (wParam & MK_XBUTTON1)
			event.MouseEvent.ButtonStates |= EMBSM_EXTRA1;
		if (wParam & MK_XBUTTON2)
			event.MouseEvent.ButtonStates |= EMBSM_EXTRA2;
#endif
		event.MouseEvent.Wheel = 0.f;

		// wheel
		if ( m->group == 3 )
		{
			POINT p;
			p.x = 0; p.y = 0;
			ClientToScreen(hWnd, &p);
			event.MouseEvent.X -= p.x;
			event.MouseEvent.Y -= p.y;
			event.MouseEvent.Wheel = ((FInt32)((SInt16)HIWORD(wParam))) / (FInt32)WHEEL_DELTA;
		}

		{
			MessageHandler(event);

			// TODO
			// Need to check mouse double click message.
/*
			if ( event.MouseInput.Event >= irr::KME_LMOUSE_PRESSED_DOWN && event.MouseInput.Event <= irr::KME_MMOUSE_PRESSED_DOWN )
			{
				irr::u32 clicks = dev->checkSuccessiveClicks(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.Event);
				if ( clicks == 2 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::KME_LMOUSE_DOUBLE_CLICK + event.MouseInput.Event-irr::KME_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
				else if ( clicks == 3 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::KME_LMOUSE_TRIPLE_CLICK + event.MouseInput.Event-irr::KME_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
			}*/
		}
		return 0;
	}

	switch (message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			Draw(ps.hdc, ps.rcPaint);
			EndPaint(hWnd, &ps);
			return 0;
		}
		break;

	case WM_CLOSE:
		SAFE_DELETE(m_pRender);
		break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
		{
			if ((KDE_KEY_CODE)wParam == KEY_ESCAPE)
			{
				SendMessage(m_hWnd, WM_CLOSE, 0, 0);
			}
		}
	case WM_KEYUP:
		{
			BYTE allKeys[256];

			event.EventType = KET_KEY;
			event.KeyEvent.Key = (KDE_KEY_CODE)wParam;
			event.KeyEvent.PressedDown = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);

			const UINT MY_MAPVK_VSC_TO_VK_EX = 3; // MAPVK_VSC_TO_VK_EX should be in SDK according to MSDN, but isn't in mine.
			if ( event.KeyEvent.Key == KEY_SHIFT )
			{
				// this will fail on systems before windows NT/2000/XP, not sure _what_ will return there instead.
				event.KeyEvent.Key = (KDE_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
			}
			if ( event.KeyEvent.Key == KEY_CONTROL )
			{
				event.KeyEvent.Key = (KDE_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
				// some keyboards will just return LEFT for both - left and right keys. So also check extend bit.
				if (lParam & 0x1000000)
					event.KeyEvent.Key = KEY_RCONTROL;
			}
			if ( event.KeyEvent.Key == KEY_MENU )
			{
				event.KeyEvent.Key = (KDE_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
				if (lParam & 0x1000000)
					event.KeyEvent.Key = KEY_RMENU;
			}

			GetKeyboardState(allKeys);

			event.KeyEvent.Shift = ((allKeys[VK_SHIFT] & 0x80)!=0);
			event.KeyEvent.Control = ((allKeys[VK_CONTROL] & 0x80)!=0);

			// Handle UNICODE and dead keys in a way that works since Windows 95 and nt4.0
			// Using ToUnicode instead would be shorter, but would to my knowledge not run on 95 and 98.
			WORD keyChars[2];
			UINT scanCode = HIWORD(lParam);
			int conversionResult = ToAsciiEx(wParam,scanCode,allKeys,keyChars,0, KLangHelper::KEYBOARD_INPUT_HKL);
			if (conversionResult == 1)
			{
				WORD unicodeChar;
				MultiByteToWideChar(
						KLangHelper::KEYBOARD_INPUT_CODEPAGE,
						MB_PRECOMPOSED, // default
						(LPCSTR)keyChars,
						sizeof(keyChars),
						(WCHAR*)&unicodeChar,
						1 );
				event.KeyEvent.Char = unicodeChar; 
			}
			else
				event.KeyEvent.Char = 0;

			// allow composing characters like '@' with Alt Gr on non-US keyboards
			if ((allKeys[VK_MENU] & 0x80) != 0)
				event.KeyEvent.Control = 0;

			MessageHandler(event);

			if (message == WM_SYSKEYDOWN || message == WM_SYSKEYUP)
				return DefWindowProc(hWnd, message, wParam, lParam);
			else
				return 0;
		}

	case WM_SIZE:
		InitDraw_Internal();
		SetResized();
		break;
	case WM_SHOWWINDOW:
		if (wParam)
		{
			SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_FRAMECHANGED );
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_DESTROY:
		if (m_bIsMain)
		{
			PostQuitMessage(0);
		}
		break;
	case WM_WINDOWPOSCHANGED:
		break;
	case WM_SYSCOMMAND:
		// prevent screen saver or monitor power save mode from starting
		if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
			(wParam & 0xFFF0) == SC_MONITORPOWER)
			return 0;
		break;

	case WM_ACTIVATE:
		m_MouseState = MOUSEDOWN_NONE;
		m_MinState = EBS_BUTTON_NORMAL;
		m_CloseState = EBS_BUTTON_NORMAL;
		KGDIRender::RenderWindowFrame(m_hWnd, this);
		return TRUE;
	case WM_NCACTIVATE:
		m_MouseState = MOUSEDOWN_NONE;
		m_MinState = EBS_BUTTON_NORMAL;
		m_CloseState = EBS_BUTTON_NORMAL;
		KGDIRender::RenderWindowFrame(m_hWnd, this);
		return TRUE;
	case WM_NCPAINT:
		KGDIRender::RenderWindowFrame(m_hWnd, this);
		return TRUE;

	case WM_NCHITTEST:
		return OnNCHitTest(message, wParam, lParam);
	case WM_NCCALCSIZE:
		return OnNCCalcSize(message, wParam, lParam);
	case WM_NCMOUSEMOVE:
		return OnNCMouseMove(message, wParam, lParam);
		break;
	case WM_NCLBUTTONDOWN:
		OnNCLButtonDown(message, wParam, lParam);
		if (m_MouseState != MOUSEDOWN_NONE)
			return 0;
		break;
	case WM_NCLBUTTONUP:
		OnNCLButtonUp(message, wParam, lParam);
		break;
	case WM_USER:
		break;
	case WM_SETCURSOR:
		break;
	case WM_INPUTLANGCHANGE:
        // get the new codepage used for keyboard input
        KLangHelper::KEYBOARD_INPUT_HKL = GetKeyboardLayout(0);
        KLangHelper::KEYBOARD_INPUT_CODEPAGE = KLangHelper::LocaleIdToCodepage( LOWORD(KLangHelper::KEYBOARD_INPUT_HKL) );
        return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

SInt32 KGUIWin32Wnd::Run()
{
	MSG msg;

	BOOL bDoIdle = TRUE;
	int nIdleCount = 0;
	BOOL bRet;

	for ( ;; )
	{
		while (bDoIdle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!OnIdle(nIdleCount++))
				bDoIdle = FALSE;
		}

		bRet = ::GetMessage(&msg, NULL, 0, 0);
		if (bRet == -1)
			continue;	// error, don't process
		else if (!bRet)
			break;		// WM_QUIT, exit message loop

		if (!PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (IsIdleMessage(&msg))
		{
			bDoIdle = TRUE;
			nIdleCount = 0;
		}
	}

	return (int)msg.wParam;
}

bool KGUIWin32Wnd::CreateKDWnd(HINSTANCE hInstance, HICON hIcon)
{
	static bool bReg = false;
	if (!bReg)
	{
		bReg				= true;
		WNDCLASSEX	wcex	= { 0 };
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= KudeetWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= hIcon;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= 0;//(HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= STANDARDWND;
		wcex.hIconSm		= hIcon;
		RegisterClassEx(&wcex);
	}

	m_hICON = hIcon;
	DWORD style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	//WS_EX_TOOLWINDOW
	m_hWnd = CreateWindowEx(0, STANDARDWND, L"", style, 0, 0, Width(), Height(), NULL, NULL, hInstance, NULL);
	if (m_hWnd == NULL)
		return false;

	//m_hRGN = ::CreateRoundRectRgn(0, 0, Width(), Height(), m_nCorner, m_nCorner);
	//SetWindowRgn(m_hWnd, m_hRGN, TRUE);

	::SetWindowText(m_hWnd, ElementText());
	m_pRender = new KGDIRender();	
	hWndMap[m_hWnd] = this;

	return true;
}

KDNAMEGUIEND

KDNAMEEND