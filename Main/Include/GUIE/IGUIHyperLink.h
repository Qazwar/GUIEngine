//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIHyperLink.h
///	@brief		Declare the Kudeet GUI element HyperLink.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIHYPERLINK_H_INCLUDED__
#define KUDEET_GUI_IGUIHYPERLINK_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

class IGUIHyperLink : public IGUIElement
{
public:
	IGUIHyperLink(IGUIElement* parent, UInt32 ctrlID) : IGUIElement(EET_CONTROL_HYPERLINK, parent, ctrlID)
	{
		#ifdef _DEBUG
			SetDebugName(L"IGUIHyperLink");
        #endif
	}

	virtual void		SetURL(LPCWSTR lpszURL) = 0;
	virtual LPCWSTR		GetURL() const = 0;
	
	virtual KColor		GetHoverColor() const = 0;
	virtual void		SetHoverColor(const KColor & color) = 0;

	virtual void		SetShowUnderline(bool bValue) = 0;
	virtual bool		GetShowUnderline() const = 0;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIHYPERLINK_H_INCLUDED__