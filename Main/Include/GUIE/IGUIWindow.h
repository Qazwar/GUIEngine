//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIWindow.h
///	@brief		Declare the Kudeet GUI element Window.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIWINDOW_H_INCLUDED__
#define KUDEET_GUI_IGUIWINDOW_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIButton;
class IGUIRender;

enum
{
	MOUSEDOWN_MIN,
	MOUSEDOWN_MAX,
	MOUSEDOWN_CLS,
	MOUSEDOWN_NONE
};

#define KUDEET_BORDER_SIZE			4
#define KUDEET_TITLE_SIZE			35
#define KUDEET_ICON_LEFT_MARGIN		7

#define KUDEET_SYS_BUTTON_SIZE		25
#define KUDEET_SYS_BUTTON_RIGHT		5	// System command button right margin
#define KUDEET_SYS_BUTTON_SPACE		2	// System command button space

class IGUIWindow : public IGUIElement
{
public:
	IGUIWindow(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_WINDOW, parent, ctrlID)
	{
	}

	virtual bool		CreateKDWnd(HINSTANCE hInstance, HICON hIcon) = 0;	

	virtual bool		ShowModal() = 0;
	virtual void		ShowWindow(SInt32 nCmd) = 0;

	virtual bool		OnIdle(int nIdleCount) = 0;
	virtual bool		MessageHandler(const KDS_EVENT& event) = 0;
	virtual LRESULT		KudeetMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual bool		PreTranslateMessage(MSG* pMsg) = 0;
	virtual void		SetEventHandler(IEventHandler * pHandler) = 0;
	virtual SInt32		Run() = 0;

	virtual bool		SetFocus(IGUIElement* pElement) = 0;
	virtual void		CenterWindow() = 0;
	virtual void		SetIcon(HICON hIcon, bool bSmall) = 0;
	virtual void		SetResized(bool bResize = true) = 0;

	virtual HWND		GetHWND() const = 0;
	virtual HICON		GetIcon() const = 0;
	virtual IGUIRender* GetRender() const = 0;
	virtual bool		GetCanBeMinimized() const = 0;
	virtual void		SetCanBeMinimized(bool bCanMin) = 0;

	virtual void		InitCapture(IGUIElement* pCaptured) = 0;
	virtual void		ReleaseCapture() = 0;

	virtual void		SetCorner(UInt32 nValue) = 0;
	virtual UInt32		GetCorner() const = 0;

	virtual void		SetIsMain(bool bValue) = 0;
	virtual bool		GetIsMain() const = 0;

	virtual void		SetOwner(IGUIWindow* pWindow) = 0;

	virtual RECT		GetCloseRect() const = 0;
	virtual RECT		GetMinRect() const = 0;

	virtual UINT32		GetCloseState() const = 0;
	virtual UINT32		GetMinState() const = 0;
	virtual UINT32		GetMouseNCState() const = 0;

	virtual bool		IsValid() const = 0;

#ifdef _DEBUG
	virtual bool		CheckControlID(UInt32 nCtrlID) = 0;
#endif
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIWINDOW_H_INCLUDED__