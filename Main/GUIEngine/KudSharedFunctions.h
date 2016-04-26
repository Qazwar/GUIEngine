//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudSharedFunctions.h
///	@brief		Implement Kudeet GUI shared methods.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_SHARED_FUNCTIONS_H_INCLUDED__
#define KUDEET_GUI_SHARED_FUNCTIONS_H_INCLUDED__

#pragma once

#include "BaseDefines.h"

KDNAMESTART

class KSharedFunctions
{
public:
	static HFONT GetCtrlFont(HWND hWnd)
	{
		HFONT hFont;
		if ( (hFont = (HFONT)::SendMessage(hWnd,WM_GETFONT,0, 0)) == NULL)
			hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		return hFont;
	}
};

KDNAMEEND

#endif //KUDEET_GUI_SHARED_FUNCTIONS_H_INCLUDED__