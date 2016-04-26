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
#include "KudSharedFunctions.h"

KDNAMESTART

KDNAMEGUI

void KGDIRender::RenderWindow(HDC hDC, IGUIWindow * const pWindow)
{
	::GetClientRect(m_hWnd, &m_ClientRC);
	if (m_MemDC == NULL)
	{
		m_MemDC		= ::CreateCompatibleDC(hDC);
		HFONT hFont = KSharedFunctions::GetCtrlFont(pWindow->GetHWND());;
		HFONT hOld	= (HFONT)::SelectObject(m_MemDC, hFont);
	}

	m_MemBmp	= ::CreateCompatibleBitmap(hDC,  m_ClientRC.right - m_ClientRC.left, m_ClientRC.bottom - m_ClientRC.top);
	m_MemBmpOld = (HBITMAP)::SelectObject(m_MemDC, m_MemBmp);
	int iSaveDC = ::SaveDC(m_MemDC);

	KColor color = KGUISkin::GetInstance()->GetBasicBackground();
	HPEN hPen = ::CreatePen(PS_SOLID, 1, color.ToColor());
	HPEN hOld = (HPEN)::SelectObject(m_MemDC, hPen);

	::FillRect(m_MemDC, &m_ClientRC, KGUISkin::GetInstance()->GetIncreasedBrush());
	::SetBkMode(m_MemDC, TRANSPARENT);
	SetTextColor(m_MemDC, KGUISkin::GetInstance()->GetTextColor());

	pWindow->IGUIElement::Draw(m_MemDC, m_ClientRC);

	::RestoreDC(m_MemDC, iSaveDC);
	BitBlt(hDC, 0, 0, m_ClientRC.right, m_ClientRC.bottom, m_MemDC, 0, 0, SRCCOPY);
	::SelectObject(m_MemDC, hOld);
	::SelectObject(m_MemDC, m_MemBmpOld);
	m_MemBmpOld = NULL;
	::DeleteObject(m_MemBmp);
	SAFE_DELOBJ(hPen);
}

void KGDIRender::RenderWindowFrame(HWND hWnd, IGUIWindow * const pWindow)
{
	if (IsIconic(hWnd))
		return ;

	HDC hWndDC = (HDC)::GetWindowDC(hWnd);
	RECT rcWnd = {0};
	GetWindowRect(hWnd, &rcWnd);
	OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);

	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
	OffsetRect(&rcClient, KUDEET_BORDER_SIZE, KUDEET_TITLE_SIZE);
	ExcludeClipRect(hWndDC, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

	HDC hMemDC = ::CreateCompatibleDC(hWndDC);
	HBITMAP hMemBmp = ::CreateCompatibleBitmap(hWndDC, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);
	HBITMAP hMemBmpOld = (HBITMAP)::SelectObject(hMemDC, hMemBmp);
	int iSaveDC = ::SaveDC(hMemDC);

	RECT rcFrame = rcWnd;
	rcFrame.right = rcFrame.left + KUDEET_BORDER_SIZE;	
	::FillRect(hMemDC, &rcFrame, KGUISkin::GetInstance()->GetDecreasedBrush());
	rcFrame = rcWnd;
	rcFrame.left = rcFrame.right - KUDEET_BORDER_SIZE;
	::FillRect(hMemDC, &rcFrame, KGUISkin::GetInstance()->GetDecreasedBrush());
	rcFrame = rcWnd;
	rcFrame.top = rcFrame.bottom - KUDEET_BORDER_SIZE;
	::FillRect(hMemDC, &rcFrame, KGUISkin::GetInstance()->GetDecreasedBrush());

	// Begin ---- draw self bitmap and fill...
	UInt32 nMode = SetStretchBltMode(hMemDC, HALFTONE);
	HDC hBitmapMemDC = CreateCompatibleDC(hMemDC);
	HBITMAP hBitmap22Old = (HBITMAP)SelectObject(hBitmapMemDC, KGUISkin::GetInstance()->GetTitleGradientBitmap());
	UInt32 nSize = KGUISkin::GetInstance()->Width();
	StretchBlt(hMemDC, rcWnd.left, rcWnd.top, rcWnd.right - rcWnd.left, KUDEET_TITLE_SIZE,
		hBitmapMemDC, 0, 0, nSize, nSize, SRCCOPY);
	SelectObject(hBitmapMemDC, hBitmap22Old);
	DeleteDC(hBitmapMemDC);
	SetStretchBltMode(hMemDC, nMode);
/*
	int size = GetSystemMetrics(SM_CXVSCROLL);
	RECT rcGrip = rcWnd;
	rcGrip.left = rcGrip.right - size;
	rcGrip.top = rcGrip.bottom - size;
	DrawFrameControl(hMemDC, &rcGrip, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
		*/
	// Draw system button
	{		
		// Close		
		RECT rcCls = pWindow->GetCloseRect();
		RECT rcMin = pWindow->GetMinRect();
		if (pWindow->GetMouseNCState() == MOUSEDOWN_CLS)
		{
			::OffsetRect(&rcCls, 1, 1);
		}
		else if (pWindow->GetMouseNCState() == MOUSEDOWN_MIN)
		{
			::OffsetRect(&rcMin, 1, 1);
		}

		const UInt32 nCornerSystemBtn = 4;		
		if (pWindow->GetCloseState() == EBS_BUTTON_HOVER ||
			pWindow->GetMinState() == EBS_BUTTON_HOVER)
		{
			HPEN hNULLPen = (HPEN)::GetStockObject(NULL_PEN);
			HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNULLPen);
			HBRUSH fillBrush = ::CreatePatternBrush(KGUISkin::GetInstance()->GetTitleGradientHighlight());			
			HBRUSH hOldB = (HBRUSH)SelectObject(hMemDC, fillBrush);
			if (pWindow->GetCloseState() == EBS_BUTTON_HOVER)
				::RoundRect(hMemDC, rcCls.left, rcCls.top, rcCls.right, rcCls.bottom, nCornerSystemBtn, nCornerSystemBtn);
			else
				::RoundRect(hMemDC, rcMin.left, rcMin.top, rcMin.right, rcMin.bottom, nCornerSystemBtn, nCornerSystemBtn);
			SelectObject(hMemDC, hOldB);
			SelectObject(hMemDC, hOldPen);
			SAFE_DELOBJ(hOldPen);
		}
#ifdef USE_GDIPLUS
		Graphics graphics(hMemDC);
		graphics.SetInterpolationMode(InterpolationModeHighQuality);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		Pen pen(Color::White, 3.0);
		Point pts[] =
		{
			Point(rcCls.left + 5, rcCls.top + 5),
			Point(rcCls.right - 6, rcCls.bottom - 6)
		};
		graphics.DrawLine(&pen, pts[0], pts[1]);
		Point pts2[] =
		{
			Point(rcCls.right - 6, rcCls.top + 5),
			Point(rcCls.left + 5, rcCls.bottom - 6)
		};
		graphics.DrawLine(&pen, pts2[0], pts2[1]);

		// Draw '-' minimize
		Point ptMins[] =
		{
			Point(rcMin.left + 4, rcMin.bottom - 10),
			Point(rcMin.right - 5, rcMin.bottom - 10)
		};	
		graphics.DrawLine(&pen, ptMins[0], ptMins[1]);
#else
		// Draw normal close flag 'X'
		POINT PT1 = {rcCls.left + 6, rcCls.top + 6},
			PT2 = {rcCls.right - 6, rcCls.bottom - 6};
		HPEN hPenLine = CreatePen(PS_INSIDEFRAME, 3, RGB(255, 255, 255));
		HPEN hPen = (HPEN)SelectObject(hMemDC, hPenLine);
		MoveToEx(hMemDC, PT1.x, PT1.y, NULL);
		LineTo(hMemDC, PT2.x, PT2.y);
		MoveToEx(hMemDC, rcCls.right - 6, rcCls.top + 6, NULL);
		LineTo(hMemDC, rcCls.left + 6, rcCls.bottom - 6);

		// Draw normal minimize flag '-'
		MoveToEx(hMemDC, rcMin.left + 4, rcMin.bottom - 10, NULL);
		LineTo(hMemDC, rcMin.right - 5, rcMin.bottom - 10);

		SelectObject(hMemDC, hPen);
		SAFE_DELOBJ(hPenLine);
#endif
	}

	// Draw Icon and Text
	DrawIconEx (hMemDC, KUDEET_ICON_LEFT_MARGIN, 3, pWindow->GetIcon(), 30, 30, 0, NULL, DI_NORMAL | DI_COMPAT);
	TCHAR szText[MAX_PATH] = {0};
	GetWindowText(pWindow->GetHWND(), szText, MAX_PATH);
	if (wcslen(szText) > 0)
	{
		RECT rcTitle =
		{
			KUDEET_ICON_LEFT_MARGIN + 35,
			0,
			rcWnd.right - rcWnd.left - 100 - KUDEET_ICON_LEFT_MARGIN,
			KUDEET_TITLE_SIZE
		};
		::SetBkMode(hMemDC, TRANSPARENT);
		HFONT hFont = KSharedFunctions::GetCtrlFont(pWindow->GetHWND());
		HFONT hOldFont = (HFONT)SelectObject(hMemDC, hFont);
		DrawText(hMemDC, szText, wcslen(szText), (LPRECT)&rcTitle, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		::SelectObject(hMemDC, hOldFont);
	}
	// End ---- draw self bitmap and fill...
	
	::RestoreDC(hMemDC, iSaveDC);
	BitBlt(hWndDC, 0, 0, rcWnd.right, rcWnd.bottom, hMemDC, 0, 0, SRCCOPY);
	::SelectObject(hMemDC, hMemBmpOld);
	::DeleteObject(hMemBmp);
	::ReleaseDC(hWnd, hWndDC);
}

KDNAMEGUIEND

KDNAMEEND