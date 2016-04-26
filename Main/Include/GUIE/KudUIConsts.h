//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudUIDefines.h
///	@brief		Declare the Kudeet GUI const values.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_UICONSTS_H_INCLUDED__
#define KUDEET_GUI_UICONSTS_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMELOT

// Define the elements default layout properties, like width, height...

#define		RUI_DEF_BUTTON_HEIGHT			28		// Button default height
#define		RUI_DEF_SLIDER_HEIGHT			15		// Slider
#define		RUI_DEF_SCROLL_SIZE				20		// Scrollbar

#define		RUI_DEF_EDIT_HEIGHG				23		// EditBox default height

#define		RUI_DEF_COMBOEDIT_ID			1001

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)	((SInt32)(SInt16)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)	((SInt32)(SInt16)HIWORD(lParam))
#endif

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_GUI_UICONSTS_H_INCLUDED__