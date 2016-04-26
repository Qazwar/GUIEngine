//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGDIRender.h
///	@brief		Header file for KGDIRender class.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GDI_RENDER_H_INCLUDED__
#define KUDEET_GDI_RENDER_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class KGDIRender : public IGUIRender
{
public:
	KGDIRender(void);
	virtual ~KGDIRender(void);

public:
	virtual void	StartRender(HWND hWnd);
	virtual void	EndRender();
	virtual void	Finalize();

	// Draw specific GUI elements.
	virtual void	RenderStatic(HDC hDC, IGUIStatic * const pStatic);
	virtual void	RenderButton(HDC hDC, IGUIButton * const pButton);
	virtual void	RenderEdit(HDC hDC, IGUIEditBox * const pEdit);
	virtual void	RenderSlider(HDC hDC, IGUISlider * const pSlider);
	virtual void	RenderWindow(HDC hDC, IGUIWindow * const pWindow);

	//! Redo initialize for render object when window size or buffer changed.
	virtual void	ReInitialRender();

	static	void	RenderWindowFrame(HWND hWnd, IGUIWindow * const pWindow);

private:
	HWND			m_hWnd;
	RECT			m_ClientRC;
	HDC				m_MemDC;
	HBITMAP			m_MemBmp;
	HBITMAP			m_MemBmpOld;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GDI_RENDER_H_INCLUDED__