//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		GUIEngine.cpp
///	@brief		Implemented the export methods in this library.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
///
//////////////////////////////////////////////////////////////////////////

#include "IGUIManagerImpl.h"
#include "IMUIManager.h"
#include "KudMUIManager.h"

KDNAMESTART

GUIE_API IGUIManager * CreateGUIManager()
{
	return new IGUIManagerImpl();
}

GUIE_API void DestroyGUIManager(IGUIManager* pMgr)
{
	SAFE_DELETE(pMgr);
}

GUIE_API IMUIManager * GetMUIManager()
{
	return KMUIManager::GetInstance();
}

KDNAMEEND