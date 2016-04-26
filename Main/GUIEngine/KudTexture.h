//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudTexture.h
///	@brief		Header file for KTexture class, implements texture.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_D3D_TEXTURE_H_INCLUDED__
#define KUDEET_D3D_TEXTURE_H_INCLUDED__

#pragma once

#include "D3D9Types.h"
#include "D3D9.h"
#include "D3DX9.h"

KDNAMESTART

KDNAMEGUI

class KTexture
{
public:
	KTexture(LPDIRECT3DDEVICE9 pDevice);
	~KTexture();

	void Init (const KString strFile);
	void Clear();

	LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DDEVICE9	m_pDevice;
	SInt32				m_Width;
	SInt32				m_Height;
	SInt32				m_Pitch;
};

KDNAMEEND

KDNAMEGUIEND

#endif //KUDEET_D3D_TEXTURE_H_INCLUDED__
