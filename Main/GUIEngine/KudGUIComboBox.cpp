//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIComboBox.cpp
///	@brief		Implements KGUIComboBox methods to support ComboBox.
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
#include "IGUITexture.h"
#include "IGUIButton.h"
#include "IGUIWindow.h"
#include "IGUIScrollBar.h"
#include "KudGUIEdit.h"
#include "KudGUIButton.h"
#include "KudGUIListBox.h"
#include "KudGUIComboBox.h"
#include "KudInternalUIDefines.h"

KDNAMESTART

KDNAMEGUI

KGUIComboBox::KGUIComboBox(IGUIElement* parent, UInt32 ctrlID) : IGUIComboBox(parent, ctrlID)
{
	SetHeight(RUI_DEF_EDIT_HEIGHG);
	SetWidth(200);
	m_hWndEdit	= NULL;
	m_pButton	= NULL;
}

KGUIComboBox::~KGUIComboBox(void)
{
}

void KGUIComboBox::FinishUpdateLayout()
{
	KRect rc = ElementRect();

	if (NULL == m_hWndEdit)
	{
		m_pButton	= new KGUIButton(this, COMBOBOX_BUTTON_ID);
		m_pButton->SetElementType(EET_CONTROL_RPTBUTTON);
		m_pButton->SetDirection(ORIENTATION_BOTTOM);
		m_pButton->SetWindow(Window());
		this->AddChildElement(m_pButton);		

		rc.right -= RUI_DEF_EDIT_HEIGHG;
		
		m_hWndEdit = ::CreateWindow(L"Edit", NULL, WS_CHILD | ES_AUTOHSCROLL, 
			rc.left + 3, rc.top + 4, rc.Width() - 6, rc.Height() - 6, Window()->GetHWND(), (HMENU)COMBOBOX_EDIT_ID, 0, 0);
		HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(m_hWndEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0));
		::SetWindowText(m_hWndEdit, this->ElementText());
	}
	else
	{
		::MoveWindow(m_hWndEdit, rc.left + 3, rc.top + 4, rc.Width() - 6, rc.Height(), TRUE);
	}

	::ShowWindow(m_hWndEdit, SW_SHOW);

	const UInt8 nMargin = 2;
	rc = ElementRect();
	rc.top += nMargin;
	rc.right -= nMargin;
	rc.left = rc.right - RUI_DEF_EDIT_HEIGHG + nMargin;
	rc.bottom -= nMargin;
	m_pButton->SetElementRect(rc);
}

void KGUIComboBox::Draw(HDC hDC, RECT rcPaint)
{
	KRect rc = this->ElementRect();
	::Rectangle(hDC, Left(), Top(), rc.right, rc.bottom);

	IGUIComboBox::Draw(hDC, rcPaint);
}

bool KGUIComboBox::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	return true;
}

KDNAMEGUIEND

KDNAMEEND