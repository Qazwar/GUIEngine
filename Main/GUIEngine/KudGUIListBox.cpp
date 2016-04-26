//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIListBox.cpp
///	@brief		Implements KGUIListBox methods to support ListBox.
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
#include "IGUIWindow.h"
#include "IGUIButton.h"
#include "KudGUIScrollBar.h"
#include "KudGUISkin.h"
#include "KudGUIListBox.h"

KDNAMESTART

KDNAMEGUI

KGUIListBox::KGUIListBox(IGUIElement* parent, UInt32 ctrlID) : IGUIListBox(parent, ctrlID)
{
	SetHeight(200);
	SetWidth(200);
	m_nSelItem		= -1;
	m_SelBrush		= KGUISkin::GetInstance()->GetBasicBackgroundBrush();
	m_SelHighBrush	= KGUISkin::GetInstance()->GetDecreasedBrush();
	
	AddItem(L"Item 1111");
	AddItem(L"Item 3333");
	AddItem(L"Item 2222");
	AddItem(L"Item 1111");
	AddItem(L"Item 3333");
	AddItem(L"Item 2222");
}

KGUIListBox::~KGUIListBox(void)
{
}

void KGUIListBox::Draw(HDC hDC, RECT rcPaint)
{
	KRect	rc	  = this->ElementRect();
	::Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
	if (m_ListItems.empty())
		return ;

	std::list<KString>::iterator it = m_ListItems.begin();
	std::list<KString>::iterator itend = m_ListItems.end();
	KRect rcItem = rc;
	rcItem.left += 2;
	rcItem.top += 2;
	rcItem.right -= 2;
	rcItem.bottom = rcItem.top + LISTBOXITEM_HEIGHT;
	for (UInt32 n = 0 ; it != itend; it++, n++)
	{
		if (n == m_nSelItem)
		{
			if (this->IsFocused())
				::FillRect(hDC, (LPRECT)&rcItem, m_SelHighBrush);
			else
				::FillRect(hDC, (LPRECT)&rcItem, m_SelBrush);
		}
		LPCWSTR lpszV = (*it).c_str();
		DrawText(hDC, lpszV, (*it).length(), (LPRECT)&rcItem, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		rcItem.top = rcItem.bottom;
		rcItem.bottom = rcItem.top + LISTBOXITEM_HEIGHT;
	}
}

bool KGUIListBox::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	switch (event.EventType)
	{
	case KET_MOUSE:
		{
			if (event.MouseEvent.Event == KME_LMOUSE_DOWN)
			{
				KPoint point(event.MouseEvent.X, event.MouseEvent.Y);
				UInt32 nIndex = (UInt32)((point.Y - this->ElementRect().top) / LISTBOXITEM_HEIGHT);

				// Click at the empty area of ListBox.
				if (nIndex >= GetCount())
					return true;

				if (m_nSelItem != -1)
				{
					KRect rc = ElementRect();
					rc.top += m_nSelItem * LISTBOXITEM_HEIGHT;
					rc.bottom = rc.top + LISTBOXITEM_HEIGHT + 5;
					::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&rc, TRUE);
				}
				
				KRect rc = ElementRect();
				rc.top += nIndex * LISTBOXITEM_HEIGHT;
				rc.bottom = rc.top + LISTBOXITEM_HEIGHT + 5;
				::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&rc, TRUE);

				m_nSelItem = nIndex;
			}
		}
	}
	return false;
}

void KGUIListBox::AddItem(const KString & strItem) 
{
	m_ListItems.push_back(strItem);

	UpdateItems();
}

void KGUIListBox::InsertItem(UInt32 nIndex, const KString & strItem) 
{
	m_ListItems.insert(m_ListItems.begin(), strItem);

	UpdateItems();
}

void KGUIListBox::UpdateItems()
{
	if (m_ListItems.size() * LISTBOXITEM_HEIGHT > Height())
	{
		// Display scrollbar
		if (NULL == m_pVerScroll)
		{
			m_pVerScroll = new KGUIScrollBar(this, 2001);
		}
	}
}

void KGUIListBox::ResetContent() 
{
	m_ListItems.clear();
	m_nSelItem	= -1;
}

UInt32 KGUIListBox::GetCount() const 
{
	return (UInt32)m_ListItems.size();
}

void KGUIListBox::SetSelectIndex(SInt32 nIndex)
{
	m_nSelItem	= nIndex;
}

KDNAMEGUIEND

KDNAMEEND