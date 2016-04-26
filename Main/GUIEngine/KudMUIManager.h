//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KDMUIManager.h
///	@brief		Declare the kudeet MUI support header.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_MUI_MANAGER_IMPL_H_INCLUDED__
#define KUDEET_MUI_MANAGER_IMPL_H_INCLUDED__

#pragma once

KDNAMESTART

typedef std::map<UInt32, std::list<KString> >				ALLLANGMAPS;
typedef std::map<UInt32, std::list<KString> >::iterator		ALLLANGMAPSITR;

class KMUIManager : public IMUIManager
{
public:
	static KMUIManager *	GetInstance()
	{
		static KMUIManager muiMgr;
		return &muiMgr;
	}

	virtual	bool			AddStringTable(LPCWSTR strFile, const UInt32 & nLangID);

	virtual LPCWSTR			GetString(UInt32 nResID, LPCWSTR strFile = NULL);
	
	virtual void			SetUserLangID(const UInt32 & nLangID);
	virtual UInt32			GetUserLangID() const;

	virtual void			SetDefaultLangID(const UInt32 & nLangID);
	virtual UInt32			GetDefaultLangID() const;

	virtual	UInt32			GetActiveLangID() const;

	virtual void			GetAllSupportedLangs(UInt32* pOut) const;
	virtual UInt32			GetAllSupportedLangCount() const;

private:
	void					LoadStringContent();

	KMUIManager(void);
	virtual ~KMUIManager(void);

private:
	ALLLANGMAPS					m_AllStrings;
	std::map<UInt32, KString>	m_CurCached;
	UInt32						m_nUserLangID;
	UInt32						m_nDefLangID;
	UInt32						m_nSysLangID;
	UInt32						m_nActiveID;
	bool						m_bLoaded;
};

KDNAMEEND

#endif //KUDEET_MUI_MANAGER_IMPL_H_INCLUDED__