//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIStatic.cpp
///	@brief		Implements KGUIStatic methods to support Static.
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
#include "IGUISlider.h"
#include "KudGUISkin.h"
#include "KudGUISlider.h"

KDNAMESTART

KDNAMEGUI

KGUISlider::KGUISlider(IGUIElement* parent, UInt32 ctrlID) : IGUISlider(parent, ctrlID)
{
	SetHeight(RUI_DEF_SLIDER_HEIGHT);
	SetWidth(200);

	m_CapturePnt.X	= 0;
	m_CapturePnt.Y	= 0;
	m_RangeBrush	= NULL;
	m_bHoverTrack	= false;
	m_bDraging		= false;
}

KGUISlider::~KGUISlider(void)
{
	SAFE_DELOBJ(m_RangeBrush)
}

void KGUISlider::FinishUpdateLayout()
{
	KRect rc	= this->ElementRect();

	rc.top		= rc.top + rc.Height() / 2 - SLIDER_RANGE_HEIGHT / 2;
	rc.bottom	= rc.top + SLIDER_RANGE_HEIGHT;
	m_RCRange	= rc;

	m_RangeBrush= KGUISkin::GetInstance()->GetBasicBackgroundBrush();
		
	rc.right	= rc.left + SLIDER_THUMB_WIDTH;
	rc.top		= m_RCClient.top;
	rc.bottom	= m_RCClient.bottom;
	m_RCTrack	= rc;
}

void KGUISlider::Draw(HDC hDC, RECT rcPaint)
{
	//Window()->GetRender()->RenderSlider(hDC, this);

	::FillRect(hDC, (LPRECT)&m_RCRange, m_RangeBrush);
	::FillRect(hDC, (LPRECT)&m_RCTrack, KGUISkin::GetInstance()->GetDecreasedBrush());

	/*UInt32 nMode = SetStretchBltMode(hDC, HALFTONE);
	HDC hMemDC	 = CreateCompatibleDC(hDC);
	UInt32 nSize = KGUISkin::GetInstance()->Width();
	if (m_bHoverTrack)
		SelectObject(hMemDC, KGUISkin::GetInstance()->GetHorizontalHoverBitmap());
	else
		SelectObject(hMemDC, KGUISkin::GetInstance()->GetHorizontalBitmap());
	StretchBlt(hDC, m_RCTrack.left, m_RCTrack.top, m_RCTrack.Width(), 
		m_RCTrack.Height(), hMemDC, 0, 0, nSize, nSize, SRCCOPY);
	DeleteDC(hMemDC);
	SetStretchBltMode(hDC, nMode);*/
}

bool KGUISlider::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	bool bHover = m_bHoverTrack;
	switch (event.EventType)
	{
	case KET_MOUSE:	// Mouse event.
		{
			if (event.MouseEvent.Event == KME_MOUSE_ENTER)
			{
				if (m_RCTrack.PtInRect(KPoint(event.MouseEvent.X, event.MouseEvent.Y)))
					bHover = true;
				else
					bHover = false;
			}
			else if (event.MouseEvent.Event == KME_MOUSE_LEAVE)
			{
				bHover = false;
			}

			if (bHover != m_bHoverTrack)
			{
				m_bHoverTrack = bHover;
				InvalidateRect(this->Window()->GetHWND(), (LPRECT)&m_RCTrack, TRUE);
				return true;
			}

			if (event.MouseEvent.Event == KME_MOUSE_MOVED)
			{
				if (m_bDraging)
				{
					if (m_RCTrack.PtInRect(KPoint(event.MouseEvent.X, event.MouseEvent.Y)))
					{
						return true;
					}

					KRect rc = ElementRect();
					m_RCTrack.left = event.MouseEvent.X - SLIDER_THUMB_WIDTH / 2;
					// right side
					if (m_RCTrack.left >= (rc.right - SLIDER_THUMB_WIDTH))
						m_RCTrack.left = rc.right - SLIDER_THUMB_WIDTH;
					// left side
					if (m_RCTrack.left < rc.left)
						m_RCTrack.left = rc.left;

					m_RCTrack.right	= m_RCTrack.left + SLIDER_THUMB_WIDTH;
					InvalidateRect(Window()->GetHWND(), (LPRECT)&rc, FALSE);
				}
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_DOWN)
			{
				if (m_RCTrack.PtInRect(KPoint(event.MouseEvent.X, event.MouseEvent.Y)))
				{
					m_bDraging = true;
					Window()->InitCapture(this);
					m_CapturePnt.X = event.MouseEvent.X;
					m_CapturePnt.Y = event.MouseEvent.Y;
				}
				else
				{
					KRect rc = ElementRect();
					m_RCTrack.left = event.MouseEvent.X - SLIDER_THUMB_WIDTH / 2;
					// right side
					if (m_RCTrack.left >= (rc.right - SLIDER_THUMB_WIDTH))
						m_RCTrack.left = rc.right - SLIDER_THUMB_WIDTH;
					// left side
					if (m_RCTrack.left < rc.left)
						m_RCTrack.left = rc.left;

					m_RCTrack.right	= m_RCTrack.left + SLIDER_THUMB_WIDTH;
					InvalidateRect(Window()->GetHWND(), (LPRECT)&rc, TRUE);
				}
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_UP)
			{
				if (m_bDraging)
				{
					m_bDraging = false;
					Window()->ReleaseCapture();
					m_CapturePnt.X = m_CapturePnt.Y = 0;
				}
			}			
		}
		break;
	case KET_KEY:
		{
			switch (event.KeyEvent.Key)
			{
			case KEY_DOWN:
			case KEY_RIGHT:
				SetValue(m_fValue + (m_fMax - m_fMin) / 10.f);
				return true;
			case KEY_UP:
			case KEY_LEFT:
				SetValue(m_fValue - (m_fMax - m_fMin) / 10.f);		// Every step is 1/10 of length.
				return true;
			}
		}
		break;
	}
	return true;
}

void KGUISlider::SetValue(FInt32 fV)
{
	m_fValue = fV;

	if (fV > m_fMax)
		m_fValue = m_fMax;

	if (fV < m_fMin)
		m_fValue = m_fMin;		

	if (Window())
	{
		KRect rc = ElementRect();
		m_RCTrack.left = (SInt32)(m_RCTrack.left + (m_fValue - m_fMin) / (m_fMax - m_fMin) * (rc.Width()));
		if (m_RCTrack.left > rc.right)
			m_RCTrack.left = rc.right;
		m_RCTrack.right	= m_RCTrack.left + SLIDER_THUMB_WIDTH;
		InvalidateRect(Window()->GetHWND(), (LPRECT)&rc, TRUE);
	}
}

void KGUISlider::SetRange(FInt32 fMin, FInt32 fMax)
{
	m_fMin	= fMin;
	m_fMax	= fMax;
}

FInt32 KGUISlider::GetValue() const
{
	return m_fValue;
}

KDNAMEGUIEND

KDNAMEEND