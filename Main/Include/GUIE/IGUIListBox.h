//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIListBox.h
///	@brief		Declare the Kudeet GUI element ListBox.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUILISTBOX_H_INCLUDED__
#define KUDEET_GUI_IGUILISTBOX_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIListBox : public IGUIElement
{
public:
	IGUIListBox(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_LISTBOX, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIListBox");
        #endif
	}

	virtual void		AddItem(const KString & strItem) = 0;
	virtual void		InsertItem(UInt32 nIndex, const KString & strItem) = 0;
	virtual void		ResetContent() = 0;
	virtual UInt32		GetCount() const = 0;
	virtual void		SetSelectIndex(SInt32 nIndex) = 0;

	//virtual void		DisableHorizontalScrollBar() = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUILISTBOX_H_INCLUDED__