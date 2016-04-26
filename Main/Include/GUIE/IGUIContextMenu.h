//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIContextMenu.h
///	@brief		Declare the Kudeet GUI element ContextMenu.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUICONTEXTMENU_H_INCLUDED__
#define KUDEET_GUI_IGUICONTEXTMENU_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIContextMenu : public IGUIElement
{
public:
	IGUIContextMenu(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_CONTEXTMENU, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIContextMenu");
        #endif
	}

	// Display context menu at specified point (X, Y)...
	virtual void		TrackPopupMenu(UInt32 X, UInt32 Y) = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUICONTEXTMENU_H_INCLUDED__