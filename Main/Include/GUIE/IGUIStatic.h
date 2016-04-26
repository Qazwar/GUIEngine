//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIStatic.h
///	@brief		Declare the Kudeet GUI element Static.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUISTATIC_H_INCLUDED__
#define KUDEET_GUI_IGUISTATIC_H_INCLUDED__

KDNAMESTART

KDNAMEGUI

class IGUIStatic : public IGUIElement
{
public:
	IGUIStatic(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_LABEL, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIStatic");
        #endif
	}
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUISTATIC_H_INCLUDED__