//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIComboBox.h
///	@brief		Header file for KGUIComboBox class, implements IGUIComboBox.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_COMBOBOX_IMPL_H_INCLUDED__
#define KUDEET_GUI_COMBOBOX_IMPL_H_INCLUDED__

#pragma once

#include "IGUIComboBox.h"

KDNAMESTART

KDNAMEGUI

class KGUIComboBox : public IGUIComboBox
{
public:
	KGUIComboBox(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIComboBox(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual void		FinishUpdateLayout();
	virtual bool		OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

private:
	IGUIButton	*		m_pButton;
	HWND				m_hWndEdit;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_COMBOBOX_IMPL_H_INCLUDED__