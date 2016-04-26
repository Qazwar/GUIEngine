//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudThemeManager.h
///	@brief		Header file for KThemeManager class, implements theme.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_LAYOUT_THEME_H_INCLUDED__
#define KUDEET_LAYOUT_THEME_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMELOT

class KThemeManager
{
private:
	KThemeManager(void);
	KThemeManager(const KThemeManager& Mgr);
	KThemeManager& operator=(const KThemeManager& Mgr);
public:
	~KThemeManager(void);

	static KThemeManager * GetInstance()
	{
		static KThemeManager Mgr;
		return &Mgr;
	}
};

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_LAYOUT_THEME_H_INCLUDED__