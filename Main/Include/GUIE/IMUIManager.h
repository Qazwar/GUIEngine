//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IMUIManager.h
///	@brief		Declare the Kudeet MUI support interface.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	@resource sample.
///
/// The priority of different language ID. UserLangID > SystemID > DefaultID
///
///	<languages default="1033">
///		<language id="1033" resfile=""/>
///		<language id="2055" resfile=""/>
///	</languages>
///
///	<?xml version="1.0" encoding="utf-8"?>
///	<rootMUI>
///		<string resID="2000">OK</string>
///	</rootMUI>
///
///	Notice:	resID should be larger than 5000.
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_IMUIMANAGER_H_INCLUDED__
#define KUDEET_IMUIMANAGER_H_INCLUDED__

#pragma once

KDNAMESTART

class IMUIManager
{
public:
	//! Add one string table to initialize MUI strings library.
	/*! Generally, we can add one XML string file to this MUI.
		\param strFile:	XML string file will be add to MUI.
		\param nLangID: specify the strings language ID.
		\return Returns true if adding success, otherwise return false. */
	virtual	bool			AddStringTable(LPCWSTR strFile, const UInt32 & nLangID) = 0;

	//! Get one localized string with specified string ID.
	/*! With this initialized MUI strings table, get one localized string with specified string ID.
		\param strID:	string ID to look for.
		\param strFile:	search ID at specified file, search all files otherwise.
		\return Returns the localized string content. */
	virtual LPCWSTR			GetString(UInt32 nResID, LPCWSTR strFile = 0) = 0;

	virtual void			SetUserLangID(const UInt32 & nLangID) = 0;
	virtual UInt32			GetUserLangID() const = 0;

	virtual void			SetDefaultLangID(const UInt32 & nLangID) = 0;
	virtual UInt32			GetDefaultLangID() const = 0;

	virtual	UInt32			GetActiveLangID() const = 0;
	
	virtual void			GetAllSupportedLangs(UInt32* pOut) const = 0;
	virtual UInt32			GetAllSupportedLangCount() const = 0;
};

KDNAMEEND

#endif // KUDEET_IMUIMANAGER_H_INCLUDED__