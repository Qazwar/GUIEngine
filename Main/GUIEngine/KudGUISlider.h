//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUISlider.h
///	@brief		Header file for KGUISlider class, implements IGUISlider.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_SLIDER_IMPL_H_INCLUDED__
#define KUDEET_GUI_SLIDER_IMPL_H_INCLUDED__

#pragma once

#include "IGUISlider.h"

KDNAMESTART

KDNAMEGUI

#define		SLIDER_RANGE_HEIGHT		6
#define		SLIDER_THUMB_WIDTH		8		// Slider thumb standard width

class KGUISlider : public IGUISlider
{
public:
	KGUISlider(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUISlider(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual void		FinishUpdateLayout();
	virtual bool		OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	virtual void		SetRange(FInt32 fMin, FInt32 fMax);
	virtual FInt32		GetValue() const;
	virtual void		SetValue(FInt32 fV);

private:
	FInt32				m_fMin;
	FInt32				m_fMax;
	FInt32				m_fValue;
	KRect				m_RCTrack;
	KRect				m_RCRange;
	bool				m_bHoverTrack;

	bool				m_bDraging;
	HBRUSH				m_RangeBrush;

	KPoint				m_CapturePnt;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_SLIDER_IMPL_H_INCLUDED__