//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUITabControl.h
///	@brief		Declare the Kudeet GUI TabControl.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUITABCTRL_H_INCLUDED__
#define KUDEET_GUI_IGUITABCTRL_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUITabControl : public IGUIElement
{
public:
	IGUITabControl(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_TABCTRL, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUITabControl");
        #endif
	}
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUITABCTRL_H_INCLUDED__