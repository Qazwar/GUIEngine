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

#ifndef KUDEET_GUI_IGUIBUTTON_H_INCLUDED__
#define KUDEET_GUI_IGUIBUTTON_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIButton : public IGUIElement
{
public:
	IGUIButton(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_BUTTON, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIButton");
        #endif
	}

	//virtual void		SetTexture(KDE_BUTTON_STATE state, IGUITexture* image = 0 ) = 0;
	//virtual void		SetTexture(IGUITexture* image = 0 ) = 0;

	virtual void		SetIsThreeState(bool bValue) = 0;
	virtual void		SetIsChecked(bool bValue) = 0;
	virtual void		SetGroupName(LPCWSTR lpszName) = 0;

	virtual bool		IsChecked() const = 0;
	virtual bool		IsThreeState() const = 0;
	virtual LPCWSTR		GroupName() const = 0;

	// Only for RepeatButton..
	virtual KDE_GUI_ORIENTATION	GetOrientation() const = 0;
	virtual void				SetOrientation(KDE_GUI_ORIENTATION value) = 0;
	virtual KDE_GUI_DIRECTION	GetDirection() const = 0;
	virtual void				SetDirection(KDE_GUI_DIRECTION value) = 0;
	
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIBUTTON_H_INCLUDED__