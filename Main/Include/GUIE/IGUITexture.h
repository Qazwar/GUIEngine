//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUITexture.h
///	@brief		Declare the Kudeet GUI texture to draw.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUITEXTURE_H_INCLUDED__
#define KUDEET_GUI_IGUITEXTURE_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

//! Texture represent one control sprit.
class IGUITexture
{
public:	
	IGUITexture() { }

	IGUITexture(const wchar_t * pszFile) : m_Name(pszFile) { }

	virtual bool		LoadTexture(const char * pszFile = 0) = 0;
	virtual KPoint		GetTextureSize() const { return m_Size; }

private:
	KString				m_Name;
	KPoint				m_Size;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUITEXTURE_H_INCLUDED__