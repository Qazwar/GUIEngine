//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIScrollbar.h
///	@brief		Declare the Kudeet GUI element Scrollbar.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUISCROLLBAR_H_INCLUDED__
#define KUDEET_GUI_IGUISCROLLBAR_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIScrollBar : public IGUIElement
{
public:
	IGUIScrollBar(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_SCROLLBAR, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIScrollBar");
        #endif
	}

	virtual	KDE_GUI_ORIENTATION		GetOrientation() const = 0;
	virtual	void					SetOrientation(KDE_GUI_ORIENTATION value) = 0;

	virtual void					SetScrollSize(UInt32 nScrollsize, UInt32 nScrollSteps, UInt32 nScrollPage) = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUISCROLLBAR_H_INCLUDED__