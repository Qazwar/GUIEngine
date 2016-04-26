//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIHyperLink.cpp
///	@brief		Implements KGUIHyperLink methods to support HyperLink.
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
#include "IGUIHyperLink.h"
#include "KudGUIHyperLink.h"
#include "Shellapi.h"

KDNAMESTART

KDNAMEGUI

KGUIHyperLink::KGUIHyperLink(IGUIElement* parent, UInt32 ctrlID) : IGUIHyperLink(parent, ctrlID)
{
	SetHeight(RUI_DEF_EDIT_HEIGHG);
	SetWidth(200);
	m_bShowLine = true;
	m_bPressed	= false;
	m_bHover	= false;
	m_FontLine	= NULL;
}

KGUIHyperLink::~KGUIHyperLink(void)
{
	SAFE_DELOBJ(m_FontLine);
}

void KGUIHyperLink::SetURL(LPCWSTR lpszURL) 
{
	m_URL = lpszURL;
}

LPCWSTR	KGUIHyperLink::GetURL() const
{
	return m_URL.c_str();
}

KColor KGUIHyperLink::GetHoverColor() const
{
	return m_Color;
}

void KGUIHyperLink::SetHoverColor(const KColor & color)
{
	m_Color = color;
}

void KGUIHyperLink::SetShowUnderline(bool bValue) 
{
	m_bShowLine = bValue;
}

bool KGUIHyperLink::GetShowUnderline() const
{
	return m_bShowLine;
}

void KGUIHyperLink::Draw(HDC hDC, RECT rcPaint)
{
	LPCWSTR pText = this->ElementText();
	if (STR_NULLOREMPTY(pText))
			return;

	if (NULL == m_FontLine)
	{
		HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		LOGFONT font;
		GetObject(hFont, sizeof font, &font);
		font.lfUnderline = TRUE;
		m_FontLine = ::CreateFontIndirect(&font);
		RECT rcTxt = {0, 0, 0, 0};
		DrawText(hDC, pText, wcslen(pText), &rcTxt, DT_CALCRECT);
		SetWidth(rcTxt.right - rcTxt.left + 10);
		
		UpdateElementLayout();
	}
	KRect rc = this->ElementRect();

	COLORREF color = GetTextColor(hDC);
	HFONT hOld = NULL;
	if (m_bHover)
	{
		hOld = (HFONT)::SelectObject(hDC, m_FontLine);
		SetTextColor(hDC, RGB(GetRValue(color), GetGValue(color), 255));
	}

	rc.left += 5;
	DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	if (hOld != NULL)
	{
		::SetTextColor(hDC, color);
		::SelectObject(hDC, hOld);
	}
}

bool KGUIHyperLink::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	bool bHover = m_bHover;
	switch (event.EventType)
	{
	case KET_MOUSE:	// Mouse event.
		{
			if (event.MouseEvent.Event == KME_MOUSE_ENTER || event.MouseEvent.Event == KME_MOUSE_MOVED)
			{
				::SetCursor(LoadCursor(0, IDC_HAND));
				bHover = true;
			}
			else if (event.MouseEvent.Event == KME_MOUSE_LEAVE)
			{
				::SetCursor(LoadCursor(0, IDC_ARROW));
				bHover = false;
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_DOWN)
			{
				m_bPressed	= true;
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_UP)
			{
				if (m_bPressed)
				{
					m_bPressed	= false;
					if (wcslen(GetURL()) > 0)
                        ::ShellExecute(0, L"Open", GetURL(), 0, 0, SW_SHOWNORMAL);
				}
			}

			if (bHover != m_bHover)
			{
				m_bHover = bHover;
				::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
			}
			break;
		}
	}
	return false;
}

KDNAMEGUIEND

KDNAMEEND