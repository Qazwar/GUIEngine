//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIListView.h
///	@brief		Declare the Kudeet GUI element ListView.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUILISTVIEW_H_INCLUDED__
#define KUDEET_GUI_IGUILISTVIEW_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIListView : public IGUIElement
{
public:
	IGUIListView(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_LISTVIEW, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIListView");
        #endif
	}
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUILISTVIEW_H_INCLUDED__