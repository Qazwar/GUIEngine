//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIScrollBar.h
///	@brief		Header file for KGUIComboBox class, implements IGUIScrollBar.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_SCROLLBAR_IMPL_H_INCLUDED__
#define KUDEET_GUI_SCROLLBAR_IMPL_H_INCLUDED__

#pragma once

#include "IGUIScrollBar.h"

KDNAMESTART

KDNAMEGUI

#define	SCROLLBAR_SIZE		18

#define THUMBMIN_SIZE		8

class KGUIScrollBar : public IGUIScrollBar
{
public:
	KGUIScrollBar(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIScrollBar(void);

	virtual void			Draw(HDC hDC, RECT rcPaint);
	virtual void			FinishUpdateLayout();
	virtual	bool			OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	KDE_GUI_ORIENTATION		GetOrientation() const;
	void					SetOrientation(KDE_GUI_ORIENTATION value);
	void					SetScrollSize(UInt32 nScrollsize, UInt32 nScrollSteps, UInt32 nScrollPage);

private:
	KDE_GUI_ORIENTATION		m_Orientation;
	KRect					m_Part1;
	KRect					m_Part2;
	KRect					m_ThumbMax;
	KRect					m_Thumb;
	IGUIButton	*			m_pBtn1;
	IGUIButton	*			m_pBtn2;

	UInt32					m_ScrollMaxSize;
	UInt32					m_ScrollStep;
	UInt32					m_ScrollPage;

	bool					m_bHover;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_SCROLLBAR_IMPL_H_INCLUDED__