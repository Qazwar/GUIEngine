//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUISlider.h
///	@brief		Declare the Kudeet GUI displaying Slider.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUISLIDER_H_INCLUDED__
#define KUDEET_GUI_IGUISLIDER_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUISlider : public IGUIElement
{
public:
	IGUISlider(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_SLIDER, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUISlider");
        #endif
	}

	virtual void		SetRange(FInt32 nMin, FInt32 nMax) = 0;
	virtual FInt32		GetValue() const = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUISLIDER_H_INCLUDED__