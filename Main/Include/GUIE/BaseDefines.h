//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		BaseDefines.h
///	@brief		Standard internal defines for Kudeet GUI Engine.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_BASEDEFINES_H_INCLUDE__
#define KUDEET_GUI_BASEDEFINES_H_INCLUDE__

#pragma once

#ifdef GUIE_EXPORTS
	#define GUIE_API __declspec(dllexport)
#else
	#define GUIE_API __declspec(dllimport)
#endif // GUIE_EXPORTS

#define	 GDIPVER		0x0110

#include <map>
#include <string>
#include <list>
#include <vector>
#include "KudCommon.h"
#include "KudPoint.h"
#include "KudRect.h"
#include "KudColor.h"

//! If you don't want to use GDI+, please comment out this define
#define	 USE_GDIPLUS

#define	 KDNAMELOT					namespace LAYOUT {
#define  KDNAMELOTEND				} // end namespace LAYOUT
#define  KDNAMEGUI					namespace GUI {
#define  KDNAMEGUIEND				} // end namespace GUI
#define	 KString					std::wstring

#define	 SAFE_DELOBJ(GDIHandle)		if (NULL != GDIHandle) { ::DeleteObject(GDIHandle); GDIHandle = NULL; }
#define	 STR_NULLOREMPTY(StrValue)	(NULL == StrValue || wcslen(StrValue) == 0)

#ifdef USE_GDIPLUS
	#include <gdiplus.h>
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")
#endif

#endif //KUDEET_GUI_BASEDEFINES_H_INCLUDE__