//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIStatic.h
///	@brief		Header file for KGUIStatic class, implements IGUIStatic.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_STATIC_IMPL_H_INCLUDED__
#define KUDEET_GUI_STATIC_IMPL_H_INCLUDED__

#pragma once

#include "IGUIStatic.h"

KDNAMESTART

KDNAMEGUI

class KGUIStatic : public IGUIStatic
{
public:
	KGUIStatic(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIStatic(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_STATIC_IMPL_H_INCLUDED__