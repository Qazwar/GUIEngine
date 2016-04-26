//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIEdit.cpp
///	@brief		Implements KGUIEditBox methods to support Edit.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudUIEnums.h"
#include "KudKeyCodes.h"
#include "KudUIDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "IGUIElement.h"
#include "IGUIEditBox.h"
#include "IGUIWindow.h"
#include "KudGUIEdit.h"

KDNAMESTART

KDNAMEGUI

KGUIEditBox::KGUIEditBox(IGUIElement* parent, UInt32 ctrlID) : IGUIEditBox(parent, ctrlID)
{
	SetHeight(RUI_DEF_EDIT_HEIGHG);
	SetWidth(200);
	m_hWndEdit	= NULL;
}

void KGUIEditBox::FinishUpdateLayout()
{
	if (NULL == m_hWndEdit)
	{
		m_hWndEdit = ::CreateWindow(L"Edit", NULL, WS_CHILD | ES_AUTOHSCROLL, Left() + 3, Top() + 4, Width() - 6, Height() - 6, Window()->GetHWND(), 0, 0, 0);
		HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(m_hWndEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0));
		::SetWindowText(m_hWndEdit, this->ElementText());
	}
	else
	{
		::MoveWindow(m_hWndEdit, Left() + 3, Top() + 4, Width() - 6, Height() - 6, TRUE);
	}
	
	::ShowWindow(m_hWndEdit, SW_SHOW);
}

KGUIEditBox::~KGUIEditBox(void)
{
	::DestroyWindow(m_hWndEdit);
}

bool KGUIEditBox::IsReadOnly() const
{
	return m_bReadOnly;
}

void KGUIEditBox::SetReadOnly(bool bValue)
{
	m_bReadOnly = bValue;
}

void KGUIEditBox::Draw(HDC hDC, RECT rcPaint)
{
	KRect rc = this->ElementRect();
	::Rectangle(hDC, Left(), Top(), rc.right, rc.bottom);
}

bool KGUIEditBox::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	return true;
}

KDNAMEGUIEND

KDNAMEEND