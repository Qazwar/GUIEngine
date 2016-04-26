//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIStatic.cpp
///	@brief		Implements KGUIStatic methods to support Static.
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
#include "KudGUIStatic.h"
#include "IGUIWindow.h"
#include "IGUIRender.h"

KDNAMESTART

KDNAMEGUI

KGUIStatic::KGUIStatic(IGUIElement* parent, UInt32 ctrlID) : IGUIStatic(parent, ctrlID)
{
	SetHeight(25);
	SetWidth(200);
}

KGUIStatic::~KGUIStatic(void)
{
}

void KGUIStatic::Draw(HDC hDC, RECT rcPaint)
{
	this->Window()->GetRender()->RenderStatic(hDC, this);
}

KDNAMEGUIEND

KDNAMEEND