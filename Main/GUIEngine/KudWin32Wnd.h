//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudWin32Wnd.h
///	@brief		Header file for KGUIWin32Wnd class, implements IGUIWindow.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_WIN32WND_IMPL_H_INCLUDED__
#define KUDEET_GUI_WIN32WND_IMPL_H_INCLUDED__

#pragma once

#include "KudInternalUIDefines.h"
#include "IGUIWindow.h"
#include "IGUIButton.h"

KDNAMESTART

KDNAMEGUI

#define STANDARDWND	L"KUDEETWND"

class IGUIRender;

class KGUIWin32Wnd : public IGUIWindow
{
public:
	KGUIWin32Wnd(void);
	virtual ~KGUIWin32Wnd(void);
	
	virtual bool		CreateKDWnd(HINSTANCE hInstance, HICON hIcon = 0);

	virtual bool		PreTranslateMessage(MSG* pMsg)	{ return false;			}
	virtual bool		OnIdle(int nIdleCount)			{ return false;			}
	virtual HWND		GetHWND() const					{ return m_hWnd;		}
	virtual HICON		GetIcon() const					{ return m_hICON;		}
	virtual void		SetCorner(UInt32 nValue)		{ m_nCorner = nValue;	}
	virtual IGUIRender* GetRender() const				{ return m_pRender;		}
	virtual UInt32		GetCorner() const				{ return m_nCorner;		}
	virtual bool		GetCanBeMinimized() const		{ return m_bCanMin;		}
	virtual void		SetCanBeMinimized(bool bCanMin)	{ m_bCanMin = bCanMin;	}
	virtual RECT		GetCloseRect() const			{ return m_RcClose;	}
	virtual RECT		GetMinRect() const				{ return m_RcMin;		}
	virtual UINT32		GetCloseState() const			{ return m_CloseState;	}
	virtual UINT32		GetMinState() const				{ return m_MinState;	}
	virtual UINT32		GetMouseNCState() const			{ return m_MouseState;	}
	virtual void		SetIsMain(bool bValue)			{ m_bIsMain = bValue;	}
	virtual bool		GetIsMain() const				{ return m_bIsMain;		}

	virtual LRESULT		KudeetMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void		SetIcon(HICON hIcon, bool bSmall);
	virtual bool		OnEvent(const KDS_EVENT & event, UInt32 dwMsgMapID = 0);
	virtual void		ShowWindow(SInt32 nCmd);
	virtual bool		ShowModal();

	virtual SInt32		Run();
	virtual void		SetEventHandler(IEventHandler * pHandler);
	virtual void		CenterWindow();
	virtual bool		MessageHandler(const KDS_EVENT& event);
	virtual bool		SetFocus(IGUIElement * pElement);

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual void		SetResized(bool bResize = true);

	virtual void		InitCapture(IGUIElement* pCaptured);
	virtual void		ReleaseCapture();	

	virtual void		SetOwner(IGUIWindow* pWindow);
	virtual bool		IsValid() const;

#ifdef _DEBUG
	virtual bool		CheckControlID(UInt32 nCtrlID);
#endif
    
private:
	LRESULT				OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam);	
	LRESULT				OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT				OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam);	
	LRESULT				OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT				OnNCCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void				InitDraw_Internal();

	static BOOL			IsIdleMessage(MSG* pMsg);

	// Handle TAB key to switch control focus.
	IGUIElement*		GetNextElement(bool reverse = false, bool group = false);

	// Generally we use this for MOUSEMOVE message to update element state.
	void				UpdateHoveredElement(const KDS_EVENT& event);

	HWND				m_hWnd;
	IEventHandler *		m_pHandlers;
	IGUIElement *		m_pGUIFocus;		// Currently focused GUI element, might be NULL.
	IGUIElement *		m_pGUIHover;		// Currently hovered GUI element
	bool				m_bResized;

	IGUIElement	*		m_CapturedElement;	// Element captured mouse event, if exist.
	IGUIWindow*			m_pOwner;
	bool				m_bCapturing;

	bool				m_bActive;			// Help to control D3D render.
	bool				m_bIsMain;

	IGUIRender	*		m_pRender;
	UInt32				m_nCorner;

	UINT				m_MouseState;
	HRGN				m_hRGN;
	HICON				m_hICON;
	bool				m_bCanMin;

	RECT				m_RcWnd;
	RECT				m_RcMin;	
	RECT				m_RcMax;
	RECT				m_RcClose;
	KDE_BUTTON_STATE	m_CloseState;
	KDE_BUTTON_STATE	m_MinState;
	KDE_BUTTON_STATE	m_MaxState;
#ifdef _DEBUG
	std::list<UInt32>	m_AllCtrlIDs;
#endif 
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_WIN32WND_IMPL_H_INCLUDED__