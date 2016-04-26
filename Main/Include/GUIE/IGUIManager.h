//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIManager.h
///	@brief		Declare Kudeet GUI manager interface.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIMANAGER_H_INCLUDED__
#define KUDEET_GUI_IGUIMANAGER_H_INCLUDED__

#pragma once

#include "BaseDefines.h"
#include "IGUIElement.h"
#include "IGUIWindow.h"
#include "IMUIManager.h"

KDNAMESTART

class IGUIManager
{
public:
	//! Load GUI configuration XML file.
	virtual bool				LoadLayout(const KString & strFile)	= 0;

	//! Update the GUI skin with specified color
	virtual void				UpdateGUISkin(KColor & color) = 0;

	//! Get one Window GUI from XML layout with name.
	virtual GUI::IGUIWindow *	GetLayoutWindow(const KString & strWndName) = 0;
};

GUIE_API	IGUIManager *		CreateGUIManager();
GUIE_API	void				DestroyGUIManager(IGUIManager* pMgr);

GUIE_API	IMUIManager *		GetMUIManager();

KDNAMEEND

#endif //KUDEET_GUI_IGUIMANAGER_H_INCLUDED__