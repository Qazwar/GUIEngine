//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUISkin.h
///	@brief		Declare the basic color management.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUISKIN_H_INCLUDED__
#define KUDEET_GUI_IGUISKIN_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

//! Interface for GUI skin / color management.
class KGUISkin
{
public:
	static KGUISkin *	GetInstance()
	{
		static KGUISkin skin;
		return &skin;
	}

	void				SetBaseColor(FInt32 fH, FInt32 fS, FInt32 fL);
	void				SetBaseColor(KColor & color);	
	void				SetBaseColor(COLORREF clrValue);

	inline void			SetTextColor(KColor & color)			{ m_TextColor = color.ToColor();}
	inline COLORREF		GetTextColor()				const		{ return m_TextColor;			}
	inline void			SetIcon(HICON hICON)					{ m_hICON = hICON;				}
	inline HICON		GetIcon()					const		{ return m_hICON;				}
	
	inline KColor		GetRevreseColor()			const		{ return m_ReverseColor;		}

	inline HBITMAP		GetHorizontalBitmap()		const		{ return m_BmpHor;				}
	inline HBITMAP		GetHorizontalHoverBitmap()	const		{ return m_BmpHorHover;			}
	inline HBITMAP		GetVerticalBitmap()			const		{ return m_BmpVer;				}
	inline HBITMAP		GetVerticalHoverBitmap()	const		{ return m_BmpVerHover;			}

	inline HBITMAP		GetButtonNormalBitmap()		const		{ return m_BmpBtnNormal;		}
	inline HBITMAP		GetButtonHoverBitmap()		const		{ return m_BmpBtnHover;			}
	inline HBITMAP		GetButtonNormalBitmapV()	const		{ return m_BmpBtnNormalV;		}
	inline HBITMAP		GetButtonHoverBitmapV()		const		{ return m_BmpBtnHoverV;		}

	inline HBITMAP		GetTitleGradientBitmap()	const		{ return m_BmpTitle;			}
	inline HBITMAP		GetTitleGradientHighlight()	const		{ return m_BmpHighlight;		}

	inline KColor		GetBasicBackground()		const		{ return m_Color;				}
	inline KColor		GetDecreasedColor()			const		{ return m_DecColor;			}
	inline KColor		GetIncreasedColor()			const		{ return m_IncColor;			}
	
	inline UInt32		Width()						const		{ return m_nWidth;				}

	inline HBRUSH		GetBasicBackgroundBrush()	const		{ return m_BaseBrush;			}
	inline HBRUSH		GetDecreasedBrush()			const		{ return m_DecBrush;			}
	inline HBRUSH		GetIncreasedBrush()			const		{ return m_IncBrush;			}

private:
	// Create gradient fill brush.
	HBITMAP				CreateBitmap(HDC hDC, FInt32 fFactor, bool bHor = true);
	HBITMAP				CreateTitleGradient(HDC hDC);
	HBITMAP				CreateGradient(HDC hDC, COLORREF clrBase, COLORREF clrHigh, COLORREF clrLow, bool bHorv);
	void				InitialSkin();
	void				ReleaseAll();

private:
	FInt32				H, S, L;
	KColor				m_Color;
	KColor				m_IncColor;
	KColor				m_DecColor;
	KColor				m_ReverseColor;

	HBITMAP				m_BmpHorHover;	// Horizontal Hover
	HBITMAP				m_BmpHor;		// Horizontal

	HBITMAP				m_BmpVerHover;	// Vertical Hover
	HBITMAP				m_BmpVer;		// Vertical	
	
	HBITMAP				m_BmpHighlight;
	HBITMAP				m_BmpTitle;
	
	HBITMAP				m_BmpBtnNormal;
	HBITMAP				m_BmpBtnHover;
	HBITMAP				m_BmpBtnNormalV;
	HBITMAP				m_BmpBtnHoverV;

	HBRUSH				m_BaseBrush;
	HBRUSH				m_IncBrush;
	HBRUSH				m_DecBrush;
	
	COLORREF			m_TextColor;
	UInt32				m_nWidth;
	HICON				m_hICON;
	bool				m_bColorDirty;

private:
	KGUISkin();
	virtual ~KGUISkin();

	KGUISkin(const KGUISkin & skin);
	KGUISkin& operator = (const KGUISkin & skin);
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUISKIN_H_INCLUDED__