//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIBasicPanel.cpp
///	@brief		Implements KGUIBasicPanel to support BasicPanel(Canvas).
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
#include "IGUIStatic.h"
#include "KudGUISkin.h"
#include "KudGUIBasicPanel.h"

KDNAMESTART

KDNAMEGUI

KGUIBasicPanel::KGUIBasicPanel(IGUIElement* parent, UInt32 ctrlID) : IGUIBasicPanel(parent, ctrlID)
{
	SetHeight(RUI_DEF_EDIT_HEIGHG);
	SetWidth(200);
}

KGUIBasicPanel::~KGUIBasicPanel(void)
{
}

KDNAMEGUIEND

KDNAMEEND