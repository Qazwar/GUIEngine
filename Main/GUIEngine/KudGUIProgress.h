//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIProgress.h
///	@brief		Header file for KGUIProgress class, implements IGUIProgress.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_PROGRESS_IMPL_H_INCLUDED__
#define KUDEET_GUI_PROGRESS_IMPL_H_INCLUDED__

#pragma once

#include "IGUIProgress.h"

KDNAMESTART

KDNAMEGUI

class KGUIProgress : public IGUIProgress
{
public:
	KGUIProgress(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIProgress(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);

	virtual SInt32		GetValue() const { return m_nValue;	}
	virtual void		SetValue(SInt32 nValue);

	virtual void		GetRange(SInt32& nMin, SInt32& nMax) const	{ nMin = m_nMin; nMax = m_nMax;	}
	virtual void		SetRange(SInt32  nMin, SInt32  nMax)		{ m_nMin = nMin; m_nMax = nMax;	}

private:
	SInt32				m_nValue;
	SInt32				m_nMin;
	SInt32				m_nMax;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_PROGRESS_IMPL_H_INCLUDED__