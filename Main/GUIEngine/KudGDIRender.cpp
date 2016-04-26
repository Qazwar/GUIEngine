//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGDIRender.cpp
///	@brief		Implements KGDIRender methods to support GDI render.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudInternalUIDefines.h"
#include "IGUIRender.h"
#include "KudGDIRender.h"
#include "KudGUISkin.h"

KDNAMESTART

KDNAMEGUI

KGDIRender::KGDIRender(void)
{
	m_MemDC		= NULL;
	m_MemBmp	= NULL;
	m_MemBmpOld	= NULL;
}

KGDIRender::~KGDIRender(void)
{
}

void KGDIRender::StartRender(HWND hWnd)
{
	m_hWnd = hWnd;
}

void KGDIRender::EndRender()
{
}

void KGDIRender::ReInitialRender()
{
}

void KGDIRender::Finalize()
{
	if (m_MemDC != NULL)
		DeleteDC(m_MemDC);
	SAFE_DELOBJ(m_MemBmp);
	SAFE_DELOBJ(m_MemBmpOld);
}

void KGDIRender::RenderButton(HDC hDC, IGUIButton * const pButton)
{
}

void KGDIRender::RenderEdit(HDC hDC, IGUIEditBox * const pEdit)
{
}

void KGDIRender::RenderSlider(HDC hDC, IGUISlider * const pSlider)
{	
}

void KGDIRender::RenderStatic(HDC hDC, IGUIStatic * const pStatic)
{
	LPCWSTR pText = pStatic->ElementText();
	KRect rc = pStatic->ElementRect();

	KDE_ELEMENT_TYPE enType = pStatic->ElementType();
	if (EET_CONTROL_LABEL == enType)
	{
		rc.left += 5;
		DrawText(hDC, pText, wcslen(pText), (LPRECT)&rc, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	}
	else if (EET_CONTROL_GROUPBOX == enType)
	{
		rc.top += 15;
		SIZE txtSize = {0};
		GetTextExtentPoint32(hDC, pText, wcslen(pText), &txtSize);
		POINT pnts[6] = {0};
		pnts[0].x = rc.left + 10;
		pnts[0].y = rc.top;
		pnts[1].x = rc.left;
		pnts[1].y = rc.top;
		pnts[2].x = rc.left;
		pnts[2].y = rc.bottom;
		pnts[3].x = rc.right;
		pnts[3].y = rc.bottom;
		pnts[4].x = rc.right;
		pnts[4].y = rc.top;
		pnts[5].x = pnts[0].x + txtSize.cx + 6;
		pnts[5].y = rc.top;
		::Polyline(hDC, pnts, 6);

		::TextOut(hDC, rc.left + 15, rc.top - 6, pText, wcslen(pText));

		/*HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		rc.top += 15;
		RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom, 5, 5);
		::SelectObject(hDC, hOldBrush);

		if (STR_NULLOREMPTY(pText))
			return;

		rc.left += 15;
		rc.top -= 7;
		// Calculate the text drawing width / height.
		RECT rcTxt = {0, 0, 0, 0};
		DrawText(hDC, pText, wcslen(pText), &rcTxt, DT_CALCRECT);
		rcTxt.bottom = rc.top + rcTxt.bottom - rcTxt.top;
		rcTxt.right = rc.left + rcTxt.right - rcTxt.left + 10;
		rcTxt.left = rc.left;
		rcTxt.top = rc.top;
		
		::FillRect(hDC, &rcTxt, GUI::KGUISkin::GetInstance()->GetBasicBackgroundBrush());

		::TextOut(hDC, rc.left + 5, rc.top, pText, wcslen(pText));*/
	}
	else
	{
		assert(enType == EET_CONTROL_IMAGE);
	}
}

KDNAMEGUIEND

KDNAMEEND