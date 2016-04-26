//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIEditBox.h
///	@brief		Declare the Kudeet GUI element EditBox.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIEDITBOX_H_INCLUDED__
#define KUDEET_GUI_IGUIEDITBOX_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIEditBox : public IGUIElement
{
public:
	IGUIEditBox(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_EDIT, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIEditBox");
        #endif
	}

	virtual bool		IsReadOnly() const = 0;
	virtual void		SetReadOnly(bool bValue) = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIEDITBOX_H_INCLUDED__