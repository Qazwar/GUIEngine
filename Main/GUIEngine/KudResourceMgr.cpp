//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2009 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet SkinX" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudResourceMgr.cpp
///	@brief		Implement the resource manager class
///	@version	0.1
///	@author		Yiling Lai
///	@date		March. 2009
///
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudResourceMgr.h"

KDNAMESTART

KDNAMEGUI

KResourceMgr* KResourceMgr::m_pInstance = NULL;

KResourceMgr::KResourceMgr(void)
{
	m_BmpButton = NULL;
}

void KResourceMgr::Initialize()
{
}

void KResourceMgr::Uninitialize()
{
	SAFE_DELETE(m_pInstance);
}

KResourceMgr::~KResourceMgr(void)
{
	SAFE_DELETE(m_BmpButton);
}

Image* KResourceMgr::GetResourceImage(UInt32 nResID)
{
	return m_BmpButton;
}

void KResourceMgr::InitializeStream(Image* & pImage, UINT nID)
{
	pImage = NULL;

	// Load resource into memory
	DWORD dwResLen = 0;
	BYTE* lpRsrc = 0;
	if (lpRsrc == NULL)
	{
		return ;
	}

	// Allocate global memory to create stream
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, dwResLen);
	BYTE* pData = (BYTE*)GlobalLock(hMem);
	memcpy(pData, lpRsrc, dwResLen);
	IStream * pStream = NULL;
	CreateStreamOnHGlobal(hMem, FALSE, &pStream);

	pImage = Image::FromStream(pStream, FALSE);
	
	// Free/Release Stuff
	GlobalUnlock(hMem);
	GlobalFree(hMem);
	pStream->Release();
	FreeResource(lpRsrc);
}

KDNAMEGUIEND

KDNAMEEND