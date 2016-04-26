//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIEdit.h
///	@brief		Header file for KGUIEditBox class, implements IGUIEditBox.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_EDITBOX_IMPL_H_INCLUDED__
#define KUDEET_GUI_EDITBOX_IMPL_H_INCLUDED__

#pragma once

#include "IGUIEditBox.h"

KDNAMESTART

KDNAMEGUI

class KGUIEditBox : public IGUIEditBox
{
public:
	KGUIEditBox(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIEditBox(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual bool		OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	virtual bool		IsReadOnly() const;
	virtual void		SetReadOnly(bool bValue);
	virtual void		FinishUpdateLayout();

private:
	HWND				m_hWndEdit;
	bool				m_bReadOnly;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_EDITBOX_IMPL_H_INCLUDED__