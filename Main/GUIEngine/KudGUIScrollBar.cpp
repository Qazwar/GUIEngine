//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIScrollBar.cpp
///	@brief		Implements KGUIScrollBar methods to support ScrollBar.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudInternalUIDefines.h"
#include "KudUIEnums.h"
#include "KudKeyCodes.h"
#include "KudUIDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "IGUIElement.h"
#include "IGUITexture.h"
#include "IGUIButton.h"
#include "IGUIScrollBar.h"
#include "KudGUIScrollBar.h"
#include "KudGUISkin.h"
#include "KudGUIButton.h"
#include "KudInternalUIDefines.h"

KDNAMESTART

KDNAMEGUI

KGUIScrollBar::KGUIScrollBar(IGUIElement* parent, UInt32 ctrlID) : IGUIScrollBar(parent, ctrlID)
{
	m_bHover		= false;
	m_Orientation	= KGO_VERTICAL;
	m_ScrollMaxSize	= 0;
	m_ScrollPage	= 0;
	m_ScrollStep	= 0;
	m_pBtn1			= NULL;
	m_pBtn2			= NULL;
	
	SetHeight(SCROLLBAR_SIZE * 10);
	SetWidth(SCROLLBAR_SIZE);
}

KGUIScrollBar::~KGUIScrollBar(void)
{
}

KDE_GUI_ORIENTATION	KGUIScrollBar::GetOrientation() const
{
	return m_Orientation;
}

void KGUIScrollBar::FinishUpdateLayout()
{
	if (NULL == m_pBtn1)
	{
		m_pBtn1		= new KGUIButton(this, SCROLLBAR_THUMB_ID_FST);
		m_pBtn2		= new KGUIButton(this, SCROLLBAR_THUMB_ID_SND);
		m_pBtn1->SetElementType(EET_CONTROL_RPTBUTTON);
		m_pBtn2->SetElementType(EET_CONTROL_RPTBUTTON);
		m_pBtn1->SetWindow(this->Window());
		m_pBtn2->SetWindow(this->Window());
		m_pBtn1->SetOrientation(m_Orientation);
		m_pBtn2->SetOrientation(m_Orientation);
		this->AddChildElement(m_pBtn1);
		this->AddChildElement(m_pBtn2);
		if (m_Orientation == KGO_VERTICAL)
		{
			m_pBtn1->SetDirection(ORIENTATION_TOP);
			m_pBtn2->SetDirection(ORIENTATION_BOTTOM);
		}
		else
		{
			m_pBtn1->SetDirection(ORIENTATION_LEFT);
			m_pBtn2->SetDirection(ORIENTATION_RIGHT);
		}
	}	

	//assert(m_ScrollMaxSize	!= 0);

	m_Part1		= ElementRect();
	m_Part2		= ElementRect();
	m_ThumbMax	= ElementRect();

	if (m_Orientation == KGO_VERTICAL)
	{
		m_Part1.bottom		= m_Part1.top + SCROLLBAR_SIZE;
		m_Part2.top			= m_Part2.bottom - SCROLLBAR_SIZE;		

		m_ThumbMax.top		= m_Part1.bottom;
		m_ThumbMax.bottom	= m_Part2.top;

		m_Thumb				= m_ThumbMax;
		//m_Thumb.bottom		= m_ScrollMaxSize / m_ScrollPage;
	}
	else
	{
		m_Part1.right		= m_Part1.left + SCROLLBAR_SIZE;
		m_Part2.left		= m_Part2.right - SCROLLBAR_SIZE;

		m_ThumbMax.left		= m_Part1.right;
		m_ThumbMax.right	= m_Part2.left;

		m_Thumb				= m_ThumbMax;
		//m_Thumb.right		= m_ScrollMaxSize / m_ScrollPage;
	}

	m_pBtn1->SetElementRect(m_Part1);
	m_pBtn2->SetElementRect(m_Part2);	
}

void KGUIScrollBar::SetScrollSize(UInt32 nScrollsize, UInt32 nScrollSteps, UInt32 nScrollPage)
{
	this->m_ScrollMaxSize	= nScrollsize;
	this->m_ScrollPage		= nScrollPage;
	this->m_ScrollStep		= nScrollSteps;

	UpdateElementLayout();
}

void KGUIScrollBar::SetOrientation(KDE_GUI_ORIENTATION value)
{
	m_Orientation = value;
	if (m_Orientation == KGO_VERTICAL)
	{
		SetWidth(SCROLLBAR_SIZE);
	}
	else
	{
		assert (m_Orientation == KGO_HORIZONTAL);
		SetHeight(SCROLLBAR_SIZE);
	}
}

void KGUIScrollBar::Draw(HDC hDC, RECT rcPaint)
{
	IGUIScrollBar::Draw(hDC, rcPaint);

	/*HBITMAP hNormal = NULL, hNormalHover = NULL;
	KRect rcThumb;
	if (m_Orientation == KGO_VERTICAL)
	{
		hNormal			= KGUISkin::GetInstance()->GetVerticalBitmap();
		hNormalHover	= KGUISkin::GetInstance()->GetVerticalHoverBrush();
		rcThumb.left	= m_Part1.left;
		rcThumb.top		= m_Part1.bottom;
		rcThumb.right	= m_Part1.right;
		rcThumb.bottom	= m_Part2.top;
	}
	else
	{
		hNormal			= KGUISkin::GetInstance()->GetHorizontalBitmap();
		hNormalHover	= KGUISkin::GetInstance()->GetHorizontalHoverBrush();
		rcThumb.left	= m_Part1.right;
		rcThumb.top		= m_Part1.top;
		rcThumb.right	= m_Part2.left;
		rcThumb.bottom	= m_Part1.bottom;
	}

	UInt32 nMode = SetStretchBltMode(hDC, HALFTONE);
	HDC hMemDC	 = CreateCompatibleDC(hDC);
	UInt32 nSize = KGUISkin::GetInstance()->Width();

	if (m_bHover)
		SelectObject(hMemDC, hNormalHover);
	else
		SelectObject(hMemDC, hNormal);
*/
	::FillRect(hDC, (LPRECT)&m_ThumbMax, KGUISkin::GetInstance()->GetDecreasedBrush());
	//StretchBlt(hDC, m_Part1.left, m_Part1.top, m_Part1.Width(), m_Part1.Height(), hMemDC, 0, 0, nSize, nSize, SRCCOPY);
	//StretchBlt(hDC, m_Part2.left, m_Part2.top, m_Part2.Width(), m_Part2.Height(), hMemDC, 0, 0, nSize, nSize, SRCCOPY);

	//DeleteDC(hMemDC);
	//SetStretchBltMode(hDC, nMode);
}

bool KGUIScrollBar::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	switch (event.EventType)
	{
	case KET_GUI:
		{
			if (event.GUIEvent.EventType == KGE_BUTTON_CLICKED)
			{
				KDS_EVENT msg;
				memset(&msg, 0, sizeof(msg));
				msg.EventType			= KET_GUI;
				msg.GUIEvent.EventType	= KGE_SCROLLBAR_CHANGED;
				msg.GUIEvent.Caller		= this;
				m_pParent->OnEvent(msg);
			}
		}
		break;
	case KET_MOUSE:
		{
			if (event.MouseEvent.Event == KME_MOUSE_ENTER || event.MouseEvent.Event == KME_MOUSE_MOVED)
			{
				m_bHover = true;
			}
			else if (event.MouseEvent.Event == KME_MOUSE_LEAVE)
			{
				m_bHover = false;
			}
		}
	case KET_KEY:
		{
			switch (event.KeyEvent.Key)
			{
			case KEY_DOWN:
				break;
			case KEY_UP:
				break;
			case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;
			case KEY_HOME:
				break;
			case KEY_END:
				break;
			case KEY_PRIOR:
				break;
			case KEY_NEXT:
				break;
			}
		}
		break;
	}
	return true;
}

KDNAMEGUIEND

KDNAMEEND