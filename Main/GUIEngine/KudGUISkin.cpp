//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUISkin.cpp
///	@brief		Implements the basic color management.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudGUISkin.h"
#ifdef WIN32
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
#endif

KDNAMESTART

KDNAMEGUI

#define KUDEET_DEFAULT_BRUSH_SIZE	40

KGUISkin::KGUISkin()
{
	m_BmpHorHover	= NULL;
	m_BmpHor		= NULL;
	m_BmpVer		= NULL;
	m_BmpVerHover	= NULL;
	
	m_BaseBrush		= NULL;
	m_DecBrush		= NULL;
	m_IncBrush		= NULL;

	m_BmpBtnHoverV	= NULL;
	m_BmpBtnNormalV	= NULL;
	m_BmpBtnHover	= NULL;
	m_BmpBtnNormal	= NULL;
	m_BmpTitle		= NULL;
	m_BmpHighlight	= NULL;

	m_hICON			= NULL;	
	m_TextColor		= RGB(0, 0, 0);
	m_bColorDirty	= true;
	m_nWidth		= KUDEET_DEFAULT_BRUSH_SIZE;
	//SetBaseColor(220, 0.5f, 0.5f); // HSL
	SetBaseColor(KColor(0x22, 0x75, 0xA0));
	//SetBaseColor(0x22, 0x75, 0xA0);
}

KGUISkin::~KGUISkin()
{
	ReleaseAll();
}

void KGUISkin::SetBaseColor(FInt32 fH, FInt32 fS, FInt32 fL)
{
	H = fH; S = fS; L = fL;
	RGBQUAD rgb = KColor::HSL2RGB(H, S, L);		
	SetBaseColor(KColor(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
}

void KGUISkin::SetBaseColor(COLORREF clrValue)
{
	SetBaseColor(KColor(clrValue));
}

void KGUISkin::SetBaseColor(KColor & color)
{
	if (m_Color.ToColor() == color.ToColor())
		return;

	m_Color = color;
	RGBQUAD rgb = { color.m_B, color.m_G, color.m_R };	
	KColor::RGB2HSL(&rgb, &H, &S, &L);
	
	m_ReverseColor.m_B = 255 - m_Color.m_B;
	m_ReverseColor.m_G = 255 - m_Color.m_G;
	m_ReverseColor.m_R = 255 - m_Color.m_R;

	m_IncColor = KColor(ColorAdjustLuma(RGB(m_Color.m_R, m_Color.m_G, m_Color.m_B), 200, TRUE));	
	m_DecColor = KColor(ColorAdjustLuma(RGB(m_Color.m_R, m_Color.m_G, m_Color.m_B), -200, TRUE));

	InitialSkin();
}

void KGUISkin::ReleaseAll()
{
	SAFE_DELOBJ(m_BmpHorHover);
	SAFE_DELOBJ(m_BmpHor);
	SAFE_DELOBJ(m_BmpVer);
	SAFE_DELOBJ(m_BmpVerHover);

	SAFE_DELOBJ(m_BaseBrush);
	SAFE_DELOBJ(m_DecBrush);
	SAFE_DELOBJ(m_IncBrush);

	SAFE_DELOBJ(m_BmpBtnHoverV);
	SAFE_DELOBJ(m_BmpBtnNormalV);
	SAFE_DELOBJ(m_BmpBtnHover);
	SAFE_DELOBJ(m_BmpBtnNormal);
	SAFE_DELOBJ(m_BmpTitle);
	SAFE_DELOBJ(m_BmpHighlight);

	SAFE_DELOBJ(m_hICON);
}

void KGUISkin::InitialSkin()
{
	ReleaseAll();

	HDC hDC = ::GetDC(NULL);
	if (GetDeviceCaps (hDC, BITSPIXEL) <= 8)
	{
		assert(false);
		return ;
	}

	m_BaseBrush		= ::CreateSolidBrush(m_Color.ToColor());
	m_IncBrush		= ::CreateSolidBrush(m_IncColor.ToColor());
	m_DecBrush		= ::CreateSolidBrush(m_DecColor.ToColor());

	m_BmpTitle		= CreateTitleGradient(hDC);
	m_BmpHor		= CreateBitmap(hDC, 0.4f);
	m_BmpHorHover	= CreateBitmap(hDC, 0.2f);
	m_BmpVer		= CreateBitmap(hDC, 0.4f, true);
	m_BmpVerHover	= CreateBitmap(hDC, 0.2f, true);	

	// Create the system command button highlight color.
	m_BmpHighlight	= CreateGradient(hDC, RGB(0xf7, 0x1b, 0x10), RGB(0xd8, 0x54, 0x2d), RGB(0xd8, 0x54, 0x2d), true);

	// Create general button bitmap
	m_BmpBtnNormal	= CreateGradient(hDC, RGB(0xe0, 0xe0, 0xe0), RGB(0xe0, 0xe0, 0xe0), RGB(0xc6, 0xc6, 0xc6), true);
	m_BmpBtnHover	= CreateGradient(hDC, RGB(0xef, 0xef, 0xef), RGB(0xff, 0xff, 0xff), RGB(0xe0, 0xe0, 0xe0), true);
	m_BmpBtnNormalV	= CreateGradient(hDC, RGB(0xe0, 0xe0, 0xe0), RGB(0xe0, 0xe0, 0xe0), RGB(0xc6, 0xc6, 0xc6), false);
	m_BmpBtnHoverV	= CreateGradient(hDC, RGB(0xef, 0xef, 0xef), RGB(0xff, 0xff, 0xff), RGB(0xe0, 0xe0, 0xe0), false);

	ReleaseDC (NULL, hDC);
}

HBITMAP	KGUISkin::CreateGradient(HDC hDC, COLORREF clrBase, COLORREF clrHigh, COLORREF clrLow, bool bVert)
{
	HDC hMemDC = CreateCompatibleDC (hDC) ;
	HBITMAP hDDB = CreateCompatibleBitmap (hDC, m_nWidth, m_nWidth);
	if (hDDB == NULL)
	{
		::DeleteDC (hMemDC) ;
		assert(false);
		return NULL;
	}

	HGDIOBJ	hOldBmp = ::SelectObject (hMemDC, hDDB);	
	TRIVERTEX vertex[4];
	vertex[0].x     = 0;
	vertex[0].y     = 0;
	vertex[0].Red   = GetRValue(clrHigh) * 256;
	vertex[0].Green = GetGValue(clrHigh) * 256;
	vertex[0].Blue  = GetBValue(clrHigh) * 256;
	vertex[0].Alpha = 0x0000;

	vertex[1].Red   = GetRValue(clrBase) * 256;
	vertex[1].Green = GetGValue(clrBase) * 256;
	vertex[1].Blue  = GetBValue(clrBase) * 256;
	vertex[1].Alpha = 0x0000;

	if (bVert)
	{
		vertex[1].x = m_nWidth;
		vertex[1].y = m_nWidth / 2;
		vertex[3].x = 0;
		vertex[3].y = m_nWidth / 2; 
	}
	else
	{
		vertex[3].y = 0;
		vertex[3].x = m_nWidth / 2; 
		vertex[1].y = m_nWidth;
		vertex[1].x = m_nWidth / 2;
	}

	vertex[3].Red   = GetRValue(clrBase) * 256;
	vertex[3].Green = GetGValue(clrBase) * 256;
	vertex[3].Blue  = GetBValue(clrBase) * 256;
	vertex[3].Alpha = 0x0000;

	vertex[2].x     = m_nWidth;
	vertex[2].y     = m_nWidth;
	vertex[2].Red   = GetRValue(clrLow) * 256;
	vertex[2].Green = GetGValue(clrLow) * 256;
	vertex[2].Blue  = GetBValue(clrLow) * 256;
	vertex[2].Alpha = 0x0000;

	GRADIENT_RECT gRect;
	gRect.UpperLeft = 0;
	gRect.LowerRight= 1;

	GRADIENT_RECT gTriangle2;
	gTriangle2.UpperLeft  = 0;
	gTriangle2.LowerRight = 1;

	if (bVert)
	{
		GradientFill(hMemDC, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
		GradientFill(hMemDC, &vertex[2], 2, &gTriangle2, 1, GRADIENT_FILL_RECT_V);
	}
	else
	{
		GradientFill(hMemDC, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
		GradientFill(hMemDC, &vertex[2], 2, &gTriangle2, 1, GRADIENT_FILL_RECT_H);
	}

	BITMAPINFO info;
	UInt32 nPitch	= (m_nWidth * 24 + 31) / 32 * 4;
	UInt32 dibSize	= sizeof(BITMAPINFOHEADER) + (nPitch * m_nWidth);
	BYTE * pBuf		= new BYTE[dibSize];
	BYTE *pData		= (BYTE*)pBuf;
	
	memset(pBuf, 0, dibSize);	
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	info.bmiHeader.biBitCount	= 24;
	info.bmiHeader.biCompression= BI_RGB;
	info.bmiHeader.biClrUsed	= 0;
	info.bmiHeader.biHeight		= m_nWidth;
	info.bmiHeader.biPlanes		= 1;
	info.bmiHeader.biSizeImage	= 0;
	info.bmiHeader.biSize		= 40;
	info.bmiHeader.biWidth		= m_nWidth;
	pData += sizeof(BITMAPINFOHEADER);

	// Copy the bitmap
	::GetDIBits (hMemDC, hDDB, 0, m_nWidth, pData, &info, DIB_RGB_COLORS) ;	
	HBITMAP hBitmap = ::CreateDIBitmap(hDC, &info.bmiHeader, CBM_INIT, pData, &info, DIB_RGB_COLORS);

	delete[] pBuf;
	::SelectObject (hMemDC, hOldBmp);
	DeleteObject (hDDB) ;
	DeleteDC (hMemDC) ;

	return hBitmap;
}

HBITMAP KGUISkin::CreateTitleGradient(HDC hDC)
{
	return CreateGradient(hDC, m_Color.ToColor(), m_IncColor.ToColor(), m_DecColor.ToColor(), true);
}

HBITMAP KGUISkin::CreateBitmap(HDC hDC, FInt32 fFactor, bool bHor)
{
	FInt32 fLight = L + (1.f - L) * fFactor;
	RGBQUAD rgb = KColor::HSL2RGB(H, S, fLight);
	COLORREF clr = KColor(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue).ToColor();
	return CreateGradient(hDC, m_Color.ToColor(), clr, clr, bHor);
}

KDNAMEGUIEND

KDNAMEEND