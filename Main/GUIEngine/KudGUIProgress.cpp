//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIProgress.cpp
///	@brief		Implements KGUIProgress methods to support Progress.
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
#include "IGUIEditBox.h"
#include "IGUIWindow.h"
#include "KudGUIProgress.h"
#include "KudGUISkin.h"

KDNAMESTART

KDNAMEGUI

KGUIProgress::KGUIProgress(IGUIElement* parent, UInt32 ctrlID) : IGUIProgress(parent, ctrlID)
{
	SetHeight(18);
	SetWidth(200);
	m_nValue	= 0;
	m_nMax		= 100;
	m_nMin		= 0;
}

KGUIProgress::~KGUIProgress()
{
}

void KGUIProgress::Draw(HDC hDC, RECT rcPaint)
{
	KRect rc = this->ElementRect();
	::Rectangle(hDC, Left(), Top(), rc.right, rc.bottom);

	FInt32 fRate = (m_nValue - m_nMin) / (FInt32)(m_nMax - m_nMin);
	rc.right = rc.left + (SInt32)(rc.Width() * fRate);
	::FillRect(hDC, (LPRECT)&rc, KGUISkin::GetInstance()->GetDecreasedBrush());
}
void  KGUIProgress::SetValue(SInt32 nValue)
{
	if (nValue != m_nValue)
	{
		m_nValue = nValue;
		if (this->Window())
			::InvalidateRect(this->Window()->GetHWND(), (LPRECT)&this->ElementRect(), TRUE);
	}
}

KDNAMEGUIEND

KDNAMEEND