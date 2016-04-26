//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIBasicPanel.h
///	@brief		Header file for KGUIStatic class, implements IGUIBasicPanel.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_BASICPANEL_IMPL_H_INCLUDED__
#define KUDEET_GUI_BASICPANEL_IMPL_H_INCLUDED__

#pragma once

#include "IGUIBasicPanel.h"

KDNAMESTART

KDNAMEGUI

class KGUIBasicPanel : public IGUIBasicPanel
{
public:
	KGUIBasicPanel(IGUIElement* parent = 0, UInt32 ctrlID = 0);
	virtual ~KGUIBasicPanel(void);
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_BASICPANEL_IMPL_H_INCLUDED__