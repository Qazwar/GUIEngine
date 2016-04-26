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

KDNAMESTART

KDNAMEGUI

KGUIWin32Wnd::KGUIWin32Wnd(void) : 
	IGUIWindow(0, 0),
	m_pHandlers(0), 
	m_pGUIFocus(0),
	m_pGUIHover(0),
	m_bResized(false),
	m_bActive(true),
	m_pOwner(0),
	m_nCorner(0)
{
#ifdef _DEBUG
	SetDebugName(L"KGUIWin32Wnd");
	m_AllCtrlIDs.clear();
#endif
	
	m_CloseState		= EBS_BUTTON_NORMAL;
	m_MinState			= EBS_BUTTON_NORMAL;
	m_MaxState			= EBS_BUTTON_NORMAL;
	m_MouseState		= MOUSEDOWN_NONE;
	m_bCapturing		= false;
	m_bIsMain			= false;
	m_CapturedElement	= NULL;
}

KGUIWin32Wnd::~KGUIWin32Wnd(void)
{
}

void KGUIWin32Wnd::SetEventHandler(IEventHandler * pHandler)
{
	m_pHandlers = pHandler;
}

bool KGUIWin32Wnd::ShowModal()
{
	HWND hWndParent = GetWindow(m_hWnd, GW_OWNER);
	if (hWndParent == NULL && m_pOwner != NULL)
	{
		hWndParent = m_pOwner->GetHWND();
	}

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::EnableWindow(hWndParent, FALSE);
	MSG msg = { 0 };
	while (::IsWindow(m_hWnd) && ::GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_CLOSE )
		{
			::EnableWindow(hWndParent, TRUE);
			::SetFocus(hWndParent);
		}
		if (!PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if( msg.message == WM_QUIT )
			break;
	}
	::EnableWindow(hWndParent, TRUE);
	::SetFocus(hWndParent);
	if (msg.message == WM_QUIT)
		::PostQuitMessage(msg.wParam);
	return true;
}

void KGUIWin32Wnd::UpdateHoveredElement(const KDS_EVENT& event)
{
	KPoint point(event.MouseEvent.X, event.MouseEvent.Y);

	if (GetChildCount() <= 0)
		return ;

	// Window element has only one child.
	IGUIElement * pGUIOver = this->GetChild(0)->HitTest(point);
	if (m_pGUIHover != pGUIOver)
	{
		if (m_pGUIHover != NULL)
		{
			KDS_EVENT msg;
			memset(&msg, 0, sizeof(msg));
			msg.EventType = KET_MOUSE;
			msg.MouseEvent = event.MouseEvent;
			msg.MouseEvent.Event = KME_MOUSE_LEAVE;			// Mouse leave message
			m_pGUIHover->OnEvent(msg);
		}
		if (pGUIOver != NULL)
		{
			KDS_EVENT msg;
			memset(&msg, 0, sizeof(msg));
			msg.EventType = KET_MOUSE;
			msg.MouseEvent = event.MouseEvent;
			msg.MouseEvent.Event	= KME_MOUSE_ENTER;		// Mouse enter message
			pGUIOver->OnEvent(msg);
		}
	}

	m_pGUIHover = pGUIOver;
}

bool KGUIWin32Wnd::SetFocus(IGUIElement * pElement)
{
	//TODO
	//Might fire focus last and focused GUI element.
	return true;
}

IGUIElement* KGUIWin32Wnd::GetNextElement(bool reverse, bool group)
{
	// TODO...
	// Support TAB order..
	return 0;
}

bool KGUIWin32Wnd::OnEvent(const KDS_EVENT & event, UInt32 dwMsgMapID)
{
	bool bHandled = false;

	// If event is GUI event, then past to system let the user handle it.
	if (m_pHandlers != NULL && event.EventType == KET_GUI)
		bHandled = m_pHandlers->OnEvent(event);

	if (!bHandled && NULL != m_pParent)
		return m_pParent->OnEvent(event);

	return bHandled;
}

bool KGUIWin32Wnd::MessageHandler(const KDS_EVENT& event)
{
	bool bHandled = false;

	if (!bHandled)
	{
		switch(event.EventType)
		{
		case KET_GUI:
			break;
		case KET_MOUSE:
			{
				if (event.MouseEvent.Event == KME_MOUSE_MOVED &&
					m_bCapturing &&	m_CapturedElement != NULL)
				{
					return m_CapturedElement->OnEvent(event);
				}

				if (event.MouseEvent.Event == KME_MOUSE_MOVED)
				{
					// Mouse enter/leave....
					UpdateHoveredElement(event);
				}

				/*if (event.MouseEvent.Event == KME_LMOUSE_DOWN)
				{
					if ( (m_pGUIHover && m_pGUIHover != m_pGUIFocus) || !m_pGUIFocus )
						SetFocus(m_pGUIHover);
				}*/

				// sending input to focus
				//if (m_pGUIFocus && m_pGUIFocus->OnEvent(event))
				//	return true;

				// focus could have died in last call
				if (NULL != m_pGUIHover)
				{
					return m_pGUIHover->OnEvent(event);
				}
				break;
			}
		case KET_KEY:
			{
				// send focus changing event
				if (event.KeyEvent.PressedDown &&
					event.KeyEvent.Key == KEY_TAB)
				{
					IGUIElement * pGUINext = GetNextElement(event.KeyEvent.Shift, event.KeyEvent.Control);
					if (pGUINext && pGUINext != m_pGUIFocus)
					{
						if (SetFocus(pGUINext))
							return true;
					}
				}

				if (m_pGUIFocus)
				{
					return m_pGUIFocus->OnEvent(event);
				}
			}
			break;
		default:
			break;
		} // end switch
		return false;
	}
	return false;
}

void KGUIWin32Wnd::SetResized(bool bResize)
{
	m_bResized = bResize;
}

void KGUIWin32Wnd::InitDraw_Internal()
{
	RECT rcTemp;
	::GetWindowRect(m_hWnd, &rcTemp);
	m_RcWnd = rcTemp;
	OffsetRect(&m_RcWnd, -m_RcWnd.left, -m_RcWnd.top);
	SetRectEmpty(&m_RcMin);
	SetRectEmpty(&m_RcMax);
	SetRectEmpty(&m_RcClose);

	m_RcClose = m_RcWnd;
	m_RcClose.right -= KUDEET_SYS_BUTTON_RIGHT;
	m_RcClose.left = m_RcClose.right - KUDEET_SYS_BUTTON_SIZE;
	m_RcClose.top = KUDEET_TITLE_SIZE / 2 - KUDEET_SYS_BUTTON_SIZE / 2;
	m_RcClose.bottom = m_RcClose.top + KUDEET_SYS_BUTTON_SIZE;
	if (m_bCanMin)
	{
		m_RcMin = m_RcClose;
		m_RcMin.right = m_RcMin.left - KUDEET_SYS_BUTTON_SPACE;
		m_RcMin.left = m_RcMin.right - KUDEET_SYS_BUTTON_SIZE;
	}
}

BOOL KGUIWin32Wnd::IsIdleMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
	case WM_PAINT:
	case 0x0118:	// WM_SYSTIMER
		return FALSE;
	}
	return TRUE;
}

void KGUIWin32Wnd::SetIcon(HICON hIcon, bool bSmall)
{
	if (bSmall)
		::SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	else
		::SendMessage(m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

void KGUIWin32Wnd::Draw(HDC hDC, RECT rcPaint)
{
	if (IsIconic(m_hWnd))
		return ;

	m_pRender->StartRender(m_hWnd);
	m_pRender->RenderWindow(hDC, this);
	m_pRender->EndRender();
}

void KGUIWin32Wnd::InitCapture(IGUIElement* pCaptured)
{
	::SetCapture(m_hWnd);
	m_bCapturing = true;
	m_CapturedElement = pCaptured;
}

void KGUIWin32Wnd::ReleaseCapture()
{
	::ReleaseCapture();
	m_bCapturing = false;
	m_CapturedElement = NULL;
}

void KGUIWin32Wnd::ShowWindow(SInt32 nCmd)
{
	::ShowWindow(m_hWnd, nCmd);
	UpdateWindow(m_hWnd);
	CenterWindow();
}

void KGUIWin32Wnd::SetOwner(IGUIWindow* pWindow)
{
	m_pOwner = pWindow;	
}

void KGUIWin32Wnd::CenterWindow()
{
	RECT rcDlg = { 0 };
	::GetWindowRect(m_hWnd, &rcDlg);
	RECT rcArea = { 0 };
	RECT rcCenter = { 0 };
	HWND hWndCenter = ::GetWindow(m_hWnd, GW_OWNER);
	if (hWndCenter == NULL && m_pOwner != NULL)
	{
		hWndCenter = m_pOwner->GetHWND();
	}

	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
	if (hWndCenter == NULL)
		rcCenter = rcArea;
	else
		::GetWindowRect(hWndCenter, &rcCenter);

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// Find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

	// The dialog is outside the screen, move it inside
	if (xLeft < rcArea.left )
		xLeft = rcArea.left;
	else if (xLeft + DlgWidth > rcArea.right)
		xLeft = rcArea.right - DlgWidth;

	if (yTop < rcArea.top )
		yTop = rcArea.top;
	else if (yTop + DlgHeight > rcArea.bottom)
		yTop = rcArea.bottom - DlgHeight;

	::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

LRESULT KGUIWin32Wnd::OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	::SetRectEmpty(&m_RcWnd);
	GetWindowRect(m_hWnd, &m_RcWnd);
	POINT PNT;
	PNT.x = GET_X_LPARAM(lParam);
	PNT.y = GET_Y_LPARAM(lParam);

	RECT rc = m_RcWnd;
	rc.top += KUDEET_TITLE_SIZE;
	rc.bottom -= KUDEET_BORDER_SIZE;
	rc.left += KUDEET_BORDER_SIZE;
	rc.right -= KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
	{
		return HTCLIENT;
	}

	if (PtInRect(&m_RcMin, PNT))		
		return HTMINBUTTON;
	else if (PtInRect(&m_RcMax, PNT))
		return HTMAXBUTTON;
	else if (PtInRect(&m_RcClose, PNT))
		return HTCLOSE;

	rc = m_RcWnd;
	rc.bottom = rc.top + KUDEET_TITLE_SIZE;
	if (PtInRect(&rc, PNT))
		return HTCAPTION;

	rc = m_RcWnd;
	rc.left= rc.right - KUDEET_BORDER_SIZE;
	rc.top = rc.bottom - KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
		return HTBOTTOMRIGHT;

	/*rc = m_RcWnd;
	rc.right = rc.left + KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
		return HTLEFT;*/

	rc = m_RcWnd;
	rc.left = rc.right - KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
		return HTRIGHT;

	rc = m_RcWnd;
	rc.top = rc.bottom - KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
		return HTBOTTOM;

	/*rc = m_RcWnd;
	rc.bottom = rc.top + KUDEET_BORDER_SIZE;
	if (PtInRect(&rc, PNT))
		return HTTOP;*/	

	return HTCLIENT;
}

LRESULT KGUIWin32Wnd::OnNCCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	NCCALCSIZE_PARAMS* pParams = NULL;
	RECT* pRect = NULL;
	BOOL bValue = static_cast<BOOL>(wParam);
	if (bValue)
		pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
	else
		pRect = reinterpret_cast<RECT*>(lParam);

	if (bValue)
	{
		pRect = &pParams->rgrc[0];
	}

	if (bValue)
	{
		pParams->rgrc[0].left += KUDEET_BORDER_SIZE;
		pParams->rgrc[0].top += KUDEET_TITLE_SIZE;
		pParams->rgrc[0].right -= (KUDEET_BORDER_SIZE + 0);
		pParams->rgrc[0].bottom -= (KUDEET_BORDER_SIZE + 0);
		pParams->rgrc[1] = pParams->rgrc[0];
	}
	else
	{
		DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT KGUIWin32Wnd::OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KDE_BUTTON_STATE bsClose = m_CloseState, bsMin = m_MinState, bsMax = m_MaxState;
	POINT PNT;
	RECT rcWnd;

	PNT.x = GET_X_LPARAM(lParam);
	PNT.y = GET_Y_LPARAM(lParam);
	GetWindowRect(m_hWnd, &rcWnd);
	PNT.x -= rcWnd.left;
	PNT.y -= rcWnd.top;

	if (PtInRect(&m_RcMin, PNT))
		m_MinState = EBS_BUTTON_HOVER;
	else
		m_MinState = EBS_BUTTON_NORMAL;

	if (PtInRect(&m_RcMax, PNT))
		m_MaxState = EBS_BUTTON_HOVER;
	else
		m_MaxState = EBS_BUTTON_NORMAL;

	if (PtInRect(&m_RcClose, PNT))
		m_CloseState = EBS_BUTTON_HOVER;
	else
		m_CloseState = EBS_BUTTON_NORMAL;

	if (bsMax != m_MaxState || 
		bsMin != m_MinState || 
		bsClose != m_CloseState)
	{
		SendMessage(m_hWnd, WM_NCPAINT, 0, 0);
	}

	return 0;
}

LRESULT KGUIWin32Wnd::OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT PNT;
	RECT rcWnd;
	
	PNT.x = GET_X_LPARAM(lParam);
	PNT.y = GET_Y_LPARAM(lParam);
	GetWindowRect(m_hWnd, &rcWnd);
	PNT.x -= rcWnd.left;
	PNT.y -= rcWnd.top;

	if (PtInRect(&m_RcMin, PNT) && m_MouseState == MOUSEDOWN_MIN)
	{
		SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else if (PtInRect(&m_RcMax, PNT) && m_MouseState == MOUSEDOWN_MAX)
	{
		if (IsZoomed(m_hWnd))
			SendMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		else
			SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}
	else if (PtInRect(&m_RcClose, PNT) && m_MouseState == MOUSEDOWN_CLS)
	{
		SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
	}

	m_MouseState = MOUSEDOWN_NONE;
	SendMessage(m_hWnd, WM_NCPAINT, 0, 0);

	return TRUE;
}

bool KGUIWin32Wnd::IsValid() const
{
	return ::IsWindow(m_hWnd) ? true : false;
}

#ifdef _DEBUG
bool KGUIWin32Wnd::CheckControlID(UInt32 nCtrlID)
{
	if (nCtrlID == 0)
		return true;

	assert(nCtrlID >= 2000 && nCtrlID < 5000);

	std::list<UInt32>::iterator it = m_AllCtrlIDs.begin();
	for ( ; it != m_AllCtrlIDs.end(); it++)
	{
		if ((*it) == nCtrlID)
			return false;
	}
	
	m_AllCtrlIDs.push_back(nCtrlID);
	return true;
}
#endif

LRESULT KGUIWin32Wnd::OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT PNT;
	RECT rcWnd;

	PNT.x = GET_X_LPARAM(lParam);
	PNT.y = GET_Y_LPARAM(lParam);
	GetWindowRect(m_hWnd, &rcWnd);	
	PNT.x -= rcWnd.left;
	PNT.y -= rcWnd.top;

	UInt32 nOldState = m_MouseState;
	if (PtInRect(&m_RcMin, PNT))
		m_MouseState = MOUSEDOWN_MIN;
	else if (PtInRect(&m_RcMax, PNT))
		m_MouseState = MOUSEDOWN_MAX;
	else if (PtInRect(&m_RcClose, PNT))
		m_MouseState = MOUSEDOWN_CLS;
	else
		m_MouseState = MOUSEDOWN_NONE;

	if (m_MouseState != nOldState)
		::SendMessage(m_hWnd, WM_NCPAINT, 0, 0);
	
	return TRUE;
}

KDNAMEGUIEND

KDNAMEEND