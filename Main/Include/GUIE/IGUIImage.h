//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIImage.h
///	@brief		Declare the Kudeet GUI element Image.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIIMAGE_H_INCLUDED__
#define KUDEET_GUI_IGUIIMAGE_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIImage : public IGUIElement
{
public:
	IGUIImage(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_IMAGE, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIImage");
        #endif
	}

	virtual void	SetScaleType(KDE_IMAGE_SCALE scaleType) = 0;
	virtual void	SetSource(UInt32 nResID) = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIIMAGE_H_INCLUDED__