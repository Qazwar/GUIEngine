//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIButton.h
///	@brief		Declare the Kudeet GUI element Button.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIIMAGEBUTTON_H_INCLUDED__
#define KUDEET_GUI_IGUIIMAGEBUTTON_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIImageButton : public IGUIElement
{
public:
	IGUIImageButton(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_IMAGE_BUTTON, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIImageButton");
        #endif
	}

    /*
	*	Set image button texture for all state, the image combined
	*	with the order of normal / hover / pressed / disabled.
	*/
	virtual void	SetTexture(UInt32 nResID) = 0;
	virtual void	SetTexture(KDE_BUTTON_STATE state, UInt32 nResID) = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIIMAGEBUTTON_H_INCLUDED__