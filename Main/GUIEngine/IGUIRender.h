//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIRender.h
///	@brief		Declare IGUIRender interface.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_IGUIRENDER_H_INCLUDED__
#define KUDEET_IGUIRENDER_H_INCLUDED__

#pragma once

#include "KudUIEnums.h"
#include "KudKeyCodes.h"
#include "KudUIDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"

#include "IGUIElement.h"
#include "IGUIWindow.h"
#include "IGUIButton.h"
#include "IGUIEditBox.h"
#include "IGUIStatic.h"
#include "IGUISlider.h"

KDNAMESTART

KDNAMEGUI

class IGUIElement;

class IGUIRender
{
public:
	virtual void	StartRender(HWND hWnd) = 0;
	virtual void	EndRender() = 0;
	virtual void	Finalize() = 0;

	// Draw specific GUI elements.
	virtual void	RenderWindow(HDC hDC, IGUIWindow * const pWindow) = 0;
	virtual void	RenderButton(HDC hDC, IGUIButton * const pButton) = 0;
	virtual void	RenderEdit(HDC hDC, IGUIEditBox * const pEdit) = 0;
	virtual void	RenderStatic(HDC hDC, IGUIStatic * const pStatic) = 0;
	virtual void	RenderSlider(HDC hDC, IGUISlider * const pSlider) = 0;

	//! Redo initialize for render object when window size or buffer changed.
	virtual void	ReInitialRender() = 0;
};

KDNAMEEND

KDNAMEGUIEND

#endif //KUDEET_IGUIRENDER_H_INCLUDED__