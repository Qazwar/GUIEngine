//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudTexture.cpp
///	@brief		Implements KTexture methods to support Direct3D texture.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include "KudTexture.h"

KDNAMESTART

KDNAMEGUI

KTexture::KTexture(LPDIRECT3DDEVICE9 pDevice) : m_pTexture(0), m_pDevice(pDevice)
{
}

KTexture::~KTexture(void)
{
	Clear();
}

void KTexture::Clear()
{
	SAFE_RELEASE(m_pTexture);
}

void KTexture::Init(const KString strFile)
{
	BYTE * pSource = NULL;

	m_pTexture = NULL;
	m_pDevice->CreateTexture(m_Width, m_Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture, 0);
	
	D3DLOCKED_RECT d3dDst;
	m_pTexture->LockRect( 0, &d3dDst, 0, 0 );
	
	DWORD * pDst = (DWORD *)d3dDst.pBits;
	SInt32  nPitchDst = d3dDst.Pitch;
	
	DWORD * pSrc = (DWORD *)pSource;
	SInt32  nPitchSrc = 0;
	
	for (SInt32 i=0; i < m_Height; ++i)
	{
		for (SInt32 j=0; j < m_Width; ++j)
		{
			pDst[i * nPitchDst + j] = pSrc[i * nPitchSrc + j];
		}
	}

	m_pTexture->UnlockRect(0);
}

KDNAMEEND

KDNAMEGUIEND
