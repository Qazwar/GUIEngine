//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIButton.cpp
///	@brief		Implements KGUIButton methods to support button.
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
#include "IGUITexture.h"
#include "IGUIElement.h"
#include "IGUIButton.h"
#include "IGUIWindow.h"
#include "KudGUIButton.h"
#include "KudGUISkin.h"

#include "KudRadioGroupsMgr.h"

KDNAMESTART

KDNAMEGUI

KGUIButton::KGUIButton(IGUIElement* parent, UInt32 ctrlID) : IGUIButton(parent, ctrlID)
{
	SetWidth(90);
	SetHeight(RUI_DEF_BUTTON_HEIGHT);
	m_bChecked	= false;
	m_BtnState	= EBS_BUTTON_NORMAL;
	m_RptBrush	= NULL;
	m_RptRGN	= NULL;
	memset(&m_nArrowPnts, 0, sizeof(POINT) * 3);
}

KGUIButton::~KGUIButton(void)
{
	SAFE_DELOBJ(m_RptRGN);
	SAFE_DELOBJ(m_RptBrush);
}

KDE_GUI_ORIENTATION	KGUIButton::GetOrientation() const
{
	assert(EET_CONTROL_RPTBUTTON == ElementType());
	return m_Orientation;
}

void KGUIButton::SetOrientation(KDE_GUI_ORIENTATION value)
{
	assert(EET_CONTROL_RPTBUTTON == ElementType());
	m_Orientation = value;
}

KDE_GUI_DIRECTION	KGUIButton::GetDirection() const
{
	assert(EET_CONTROL_RPTBUTTON == ElementType());
	return m_Direction;
}

void KGUIButton::SetDirection(KDE_GUI_DIRECTION value)
{
	assert(EET_CONTROL_RPTBUTTON == ElementType());
	m_Direction = value;
}

void KGUIButton::FinishUpdateLayout()
{
	if ( EET_CONTROL_RPTBUTTON == ElementType())
	{
		SAFE_DELOBJ(m_RptRGN);
		SAFE_DELOBJ(m_RptBrush);

		KRect	rc = ElementRect();
		SInt32	nDir = 3;

		switch (m_Direction)
		{
		case ORIENTATION_LEFT:
			m_nArrowPnts[0].x = rc.left + rc.Width() / 2 - nDir + 0;
			m_nArrowPnts[0].y = rc.top + rc.Height() / 2;
			m_nArrowPnts[1].x = rc.left + rc.Width() / 2 + nDir;
			m_nArrowPnts[1].y = rc.top + rc.Height() / 2 - nDir - 1;
			m_nArrowPnts[2].x = rc.left + rc.Width() / 2 + nDir;
			m_nArrowPnts[2].y = rc.top + rc.Height() / 2 + nDir + 1;
			break;

		case ORIENTATION_RIGHT:
			m_nArrowPnts[0].x = rc.left + rc.Width() / 2 + nDir;
			m_nArrowPnts[0].y = rc.top + rc.Height() / 2;
			m_nArrowPnts[1].x = rc.left + rc.Width() / 2 - nDir;
			m_nArrowPnts[1].y = rc.top + rc.Height() / 2 - nDir - 1;
			m_nArrowPnts[2].x = rc.left + rc.Width() / 2 - nDir;
			m_nArrowPnts[2].y = rc.top + rc.Height() / 2 + nDir + 1;
			break;
		
		case ORIENTATION_TOP:
			m_nArrowPnts[0].x = rc.left + rc.Width() / 2;
			m_nArrowPnts[0].y = rc.top + rc.Height() / 2 - nDir;
			m_nArrowPnts[1].x = rc.left + rc.Width() / 2 - nDir - 1;
			m_nArrowPnts[1].y = rc.top + rc.Height() / 2 + nDir;
			m_nArrowPnts[2].x = rc.left + rc.Width() / 2 + nDir + 1;
			m_nArrowPnts[2].y = rc.top + rc.Height() / 2 + nDir;
			break;

		case ORIENTATION_BOTTOM:
			m_nArrowPnts[0].x = rc.left + rc.Width() / 2;
			m_nArrowPnts[0].y = rc.top + rc.Height() / 2 + nDir;
			m_nArrowPnts[1].x = rc.left + rc.Width() / 2 - nDir - 1;
			m_nArrowPnts[1].y = rc.top + rc.Height() / 2 - nDir;
			m_nArrowPnts[2].x = rc.left + rc.Width() / 2 + nDir + 1;
			m_nArrowPnts[2].y = rc.top + rc.Height() / 2 - nDir;
			break;
		default:
			assert(false);
		}

		m_RptBrush	= ::CreateSolidBrush(RGB(40, 40, 40));
		m_RptRGN	= ::CreatePolygonRgn(m_nArrowPnts, 3, WINDING);
	}
}

void KGUIButton::Draw(HDC hDC, RECT rcPaint)
{
	LPCWSTR pText = this->ElementText();
	KRect	rc	  = this->ElementRect();

	KDE_ELEMENT_TYPE BtnType = ElementType();

	if (EET_CONTROL_BUTTON == BtnType || EET_CONTROL_RPTBUTTON == BtnType)
	{
		UInt32 nMode = SetStretchBltMode(hDC, HALFTONE);
		HDC hMemDC	 = CreateCompatibleDC(hDC);
		UInt32 nSize = KGUISkin::GetInstance()->Width();
		
		if (m_BtnState == EBS_BUTTON_HOVER || m_BtnState == EBS_BUTTON_PRESSED)
		{
			if (EET_CONTROL_RPTBUTTON == BtnType && m_Orientation == KGO_VERTICAL)
				SelectObject(hMemDC, KGUISkin::GetInstance()->GetButtonHoverBitmapV());
				//SelectObject(hMemDC, KGUISkin::GetInstance()->GetVerticalHoverBitmap());
			else
				//SelectObject(hMemDC, KGUISkin::GetInstance()->GetHorizontalHoverBitmap());
				SelectObject(hMemDC, KGUISkin::GetInstance()->GetButtonHoverBitmap());
		}
		else
		{
			if (EET_CONTROL_RPTBUTTON == BtnType && m_Orientation == KGO_VERTICAL)
				//SelectObject(hMemDC, KGUISkin::GetInstance()->GetVerticalBitmap());
				SelectObject(hMemDC, KGUISkin::GetInstance()->GetButtonNormalBitmapV());
			else
				//SelectObject(hMemDC, KGUISkin::GetInstance()->GetHorizontalBitmap());
				SelectObject(hMemDC, KGUISkin::GetInstance()->GetButtonNormalBitmap());
		}

        StretchBlt(hDC, rc.left, rc.top, rc.Width(), rc.Height(), hMemDC, 0, 0, nSize, nSize, SRCCOPY);

		DeleteDC(hMemDC);
		SetStretchBltMode(hDC, nMode);

		if (EET_CONTROL_BUTTON == BtnType)
		{
			if (STR_NULLOREMPTY(pText))
				return;

			if (m_BtnState == EBS_BUTTON_PRESSED)
			{
				rc.left += 2;
				rc.top	+= 2;
				DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			}
			else
			{
				DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			}
		}
		else	// Repeat button draw arrow...
		{
#ifdef USE_GDIPLUS
			Graphics graphics(hDC);
			SolidBrush blackBrush(Color::Black);
			Point pts[] =
			{
				Point(m_nArrowPnts[0].x, m_nArrowPnts[0].y),
				Point(m_nArrowPnts[1].x, m_nArrowPnts[1].y),
				Point(m_nArrowPnts[2].x, m_nArrowPnts[2].y)
			};
			GraphicsPath path;
			path.AddLines(pts, 3);
			graphics.SetInterpolationMode(InterpolationModeHighQuality);
			graphics.SetSmoothingMode(SmoothingModeHighQuality);
			graphics.FillPath(&blackBrush, &path);
			Pen pen(Color::Black, 1.0);
			graphics.DrawPath(&pen, &path);
#else
			::FillRgn(hDC, m_RptRGN, m_RptBrush);
#endif
		}
	}
	else if (EET_CONTROL_RADIOBOX == BtnType)
	{
		KRect rcSel;
		rcSel.left	= Left() + 5;
		rcSel.top	= Top() + Height() / 2 - 8;
		rcSel.right = rcSel.left + 15;
		rcSel.bottom= rcSel.top + 15;
#ifdef USE_GDIPLUS
		Graphics graphics(hDC);
		GraphicsPath path;
		path.AddEllipse(rcSel.left, rcSel.top, rcSel.right - rcSel.left, rcSel.bottom - rcSel.top);
		graphics.SetInterpolationMode(InterpolationModeHighQuality);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		SolidBrush wBrush(Color::White);
		graphics.FillPath(&wBrush, &path);
		KColor clr = GUI::KGUISkin::GetInstance()->GetDecreasedColor().ToColor();
		Pen pen(Color(255, clr.m_R, clr.m_G, clr.m_B), 1.0);
		graphics.DrawPath(&pen, &path);
#else
		Ellipse(hDC, rcSel.left, rcSel.top, rcSel.right, rcSel.bottom);
#endif
        
		rc.left = rcSel.right + 5;

		if (IsChecked())
		{
			const UInt8 scaleSize = 4;
			rcSel.left	+= scaleSize;
			rcSel.top	+= scaleSize;
			rcSel.right -= scaleSize;
			rcSel.bottom-= scaleSize;
#ifdef USE_GDIPLUS
			GraphicsPath pathInner;
			pathInner.AddEllipse(rcSel.left, rcSel.top, rcSel.right - rcSel.left, rcSel.bottom - rcSel.top);
			SolidBrush baseBrush(Color(255, clr.m_R, clr.m_G, clr.m_B));
			graphics.FillPath(&baseBrush, &pathInner);
			graphics.DrawPath(&pen, &pathInner);
#else
			HBRUSH	hBrush	= GUI::KGUISkin::GetInstance()->GetBasicBackgroundBrush();
			HBRUSH	hOld	= (HBRUSH)::SelectObject(hDC, hBrush);
			Ellipse(hDC, rcSel.left, rcSel.top, rcSel.right, rcSel.bottom);
			::SelectObject(hDC, hOld);
#endif
		}

		if (STR_NULLOREMPTY(pText))
			return;

		DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_LEFT);		
	}
	else // EET_CONTROL_CHECKBOX
	{
		assert(BtnType == EET_CONTROL_CHECKBOX);
		//cdc.RoundRect(rc.left, rc.top, rc.right, rc.bottom, 5, 5);
		KRect rcSel;
		rcSel.left	= Left() + 6;
		rcSel.top	= Top() + Height() / 2 - 8;
		rcSel.right = rcSel.left + 16;
		rcSel.bottom= rcSel.top + 16;
		Rectangle(hDC, rcSel.left, rcSel.top, rcSel.right, rcSel.bottom);
		
		rcSel.left	+= 2;
		rcSel.top	+= 2;
		rcSel.right -= 2;
		rcSel.bottom-= 2;
		Rectangle(hDC, rcSel.left, rcSel.top, rcSel.right, rcSel.bottom);
		
		if (IsChecked())
		{
			KColor clr = GUI::KGUISkin::GetInstance()->GetBasicBackground();
			HPEN hPen = CreatePen(PS_SOLID, 2, clr.ToColor());
			HPEN hOldDraw = (HPEN)SelectObject(hDC, hPen);
			
			::MoveToEx(hDC, rcSel.left + 1,  rcSel.top + 1, 0);
			::LineTo(hDC,   rcSel.right- 1, rcSel.bottom - 1);
			::MoveToEx(hDC, rcSel.right- 2, rcSel.top + 1, 0);
			::LineTo(hDC,   rcSel.left,  rcSel.bottom - 1);
			SelectObject(hDC, hOldDraw);
			DeleteObject(hPen);
		}		

		if (STR_NULLOREMPTY(pText))
			return;
		rc.left = rcSel.right + 5;
		DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	}
}

void KGUIButton::SetIsThreeState(bool bValue)
{
	m_bTreeState = bValue;
}

void KGUIButton::SetGroupName(LPCWSTR lpszName)
{
	m_GroupName = lpszName;	
	KRadioGroupMgr::GetInstance()->AddRadio(lpszName, this);
}

void KGUIButton::SetIsChecked(bool bValue)
{
	m_bChecked = bValue;
	KRadioGroupMgr::GetInstance()->UpdateRadioGroup(this);
	::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
}

bool KGUIButton::IsChecked() const
{
	return m_bChecked;
}

bool KGUIButton::IsThreeState() const
{
	return m_bTreeState;
}

LPCWSTR KGUIButton::GroupName() const
{
	return m_GroupName.c_str();
}

bool KGUIButton::OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID)
{
	KDE_BUTTON_STATE btnState = m_BtnState;
	switch (event.EventType)
	{
	case KET_MOUSE:	// Mouse event.
		{
			if (event.MouseEvent.Event == KME_MOUSE_ENTER /* || event.MouseEvent.Event == KME_MOUSE_MOVED*/)
			{
				btnState	= EBS_BUTTON_HOVER;
			}
			else if (event.MouseEvent.Event == KME_MOUSE_LEAVE)
			{
				btnState	= EBS_BUTTON_NORMAL;
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_DOWN)
			{
				btnState	= EBS_BUTTON_PRESSED;
			}
			else if (event.MouseEvent.Event == KME_LMOUSE_UP)
			{
				if (m_BtnState == EBS_BUTTON_PRESSED)
				{
					if (m_eType == EET_CONTROL_BUTTON || m_eType == EET_CONTROL_RPTBUTTON)
					{
						btnState				= EBS_BUTTON_NORMAL;
						// Fire KGE_BUTTON_CLICKED to parent.
						KDS_EVENT msg;
						memset(&msg, 0, sizeof(msg));
						msg.EventType			= KET_GUI;
						msg.GUIEvent.EventType	= KGE_BUTTON_CLICKED;
						msg.GUIEvent.Caller		= this;
						m_pParent->OnEvent(msg);
					}
					else if (m_eType == EET_CONTROL_RADIOBOX)
					{
						// If already checked radio, do nothing when mouse clicked.
						if (!m_bChecked)
						{
							// Fire KGE_RADIOBOX_CHECKED to parent.
							KDS_EVENT msg;
							memset(&msg, 0, sizeof(msg));
							msg.EventType			= KET_GUI;
							msg.GUIEvent.EventType	= KGE_RADIOBOX_CHECKED;
							msg.GUIEvent.Caller		= this;
							m_pParent->OnEvent(msg);
							m_bChecked = !m_bChecked;
							KRadioGroupMgr::GetInstance()->UpdateRadioGroup(this);
							::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
						}
						return true;
					}
					else
					{
						m_bChecked = !m_bChecked;
						::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
						return true;
					}
				}
			}
			if (btnState != m_BtnState)
			{
				m_BtnState	= btnState;
				::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
			}
			break;
		}
	}
	return false;
}

KDNAMEGUIEND

KDNAMEEND