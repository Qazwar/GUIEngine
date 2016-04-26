//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIButton.h
///	@brief		Header file for KGUIButton class, implements IGUIButton.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_BUTTON_IMPL_H_INCLUDED__
#define KUDEET_GUI_BUTTON_IMPL_H_INCLUDED__

#pragma once

#include "KudInternalUIDefines.h"
#include "IGUIButton.h"

KDNAMESTART

KDNAMEGUI

//! General button class (Support push button, checkbox raidobutton).
class KGUIButton : public IGUIButton
{
public:
	KGUIButton(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIButton(void);

	//virtual void		SetTexture(KDE_BUTTON_STATE state, IGUITexture* image = 0 );
	//virtual void		SetTexture(IGUITexture* image = 0 ) { m_pTexture = image; }

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual void		FinishUpdateLayout();
	virtual bool		OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	virtual void		SetIsThreeState(bool bValue);
	virtual void		SetGroupName(LPCWSTR lpszName);
	virtual void		SetIsChecked(bool bValue);

	virtual bool		IsChecked() const;
	virtual bool		IsThreeState() const;
	virtual LPCWSTR		GroupName() const;

	virtual KDE_GUI_ORIENTATION	GetOrientation() const;
	virtual void				SetOrientation(KDE_GUI_ORIENTATION value);
	virtual KDE_GUI_DIRECTION	GetDirection() const;
	virtual void				SetDirection(KDE_GUI_DIRECTION value);

private:
	KDE_GUI_ORIENTATION	m_Orientation;
	KDE_GUI_DIRECTION	m_Direction;
	//IGUITexture	*		m_pTexture;
	bool				m_bPressed;
	KColor				m_FocusColor;

	HRGN				m_RptRGN;
	HBRUSH				m_RptBrush;

	KDE_BUTTON_STATE	m_BtnState;

	KString				m_GroupName;
	bool				m_bChecked;
	bool				m_bTreeState;

	POINT				m_nArrowPnts[3];
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_BUTTON_IMPL_H_INCLUDED__