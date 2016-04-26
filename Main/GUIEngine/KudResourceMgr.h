//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2009 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudResourceMgr.h
///	@brief		Declare the resource manager class
///	@version	0.1
///	@author		Yiling Lai
///	@date		March. 2009
///
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_RESOURCEMGR_H_INCLUDED__
#define KUDEET_RESOURCEMGR_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class KResourceMgr
{
public:
	~KResourceMgr(void);

	static KResourceMgr* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new KResourceMgr();
		return m_pInstance;
	}

	void		Initialize();
	void		Uninitialize();

public:
	Image*		GetResourceImage(UInt32 nResID);

private:
	void		InitializeStream(Image* & pImage, UINT nID);

	Image*		m_BmpButton;

private:
	KResourceMgr(void);
	KResourceMgr(const KResourceMgr& mgr);
	KResourceMgr& operator= (const KResourceMgr& mgr);
	static KResourceMgr * m_pInstance;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_RESOURCEMGR_H_INCLUDED__