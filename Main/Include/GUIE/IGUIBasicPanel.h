//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIBasicPanel.h
///	@brief		Declare the kudeet GUI element BasicPanel (Canvas).
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIBASICPANEL_H_INCLUDED__
#define KUDEET_GUI_IGUIBASICPANEL_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIBasicPanel : public IGUIElement
{
public:
	IGUIBasicPanel(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_LAYOUT_BASICPANEL, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIBasicPanel");
        #endif
	}
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIBASICPANEL_H_INCLUDED__