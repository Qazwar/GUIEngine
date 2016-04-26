//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIProgress.h
///	@brief		Declare the Kudeet GUI element progress.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIPROGRESS_H_INCLUDED__
#define KUDEET_GUI_IGUIPROGRESS_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIProgress : public IGUIElement
{
public:
	IGUIProgress(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_PROGRESS, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIProgress");
        #endif
	}

	virtual SInt32		GetValue() const		= 0;	
	virtual void		SetValue(SInt32 nValue) = 0;

	virtual void		GetRange(SInt32& nMin, SInt32& nMax) const	= 0;
	virtual void		SetRange(SInt32  nMin, SInt32  nMax)		= 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIPROGRESS_H_INCLUDED__