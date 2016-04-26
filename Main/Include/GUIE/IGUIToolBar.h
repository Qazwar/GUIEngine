//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIToolBar.h
///	@brief		Declare the Kudeet GUI ToolBar.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUITOOLBAR_H_INCLUDED__
#define KUDEET_GUI_IGUITOOLBAR_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIToolBar : public IGUIElement
{
public:
	IGUIToolBar(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_TOOLBAR, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIToolBar");
        #endif
	}
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUITOOLBAR_H_INCLUDED__