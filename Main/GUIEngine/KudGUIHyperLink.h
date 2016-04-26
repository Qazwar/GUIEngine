//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIHyperLink.h
///	@brief		Header file for KGUIHyperLink class.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_HYPERLINK_IMPL_H_INCLUDED__
#define KUDEET_GUI_HYPERLINK_IMPL_H_INCLUDED__

#pragma once

#include "IGUIHyperLink.h"

KDNAMESTART

KDNAMEGUI

class KGUIHyperLink : public IGUIHyperLink
{
public:
	KGUIHyperLink(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIHyperLink(void);

	virtual void		Draw(HDC hDC, RECT rcPaint);
	virtual bool		OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	virtual void		SetURL(LPCWSTR lpszURL) ;
	virtual LPCWSTR		GetURL() const ;
	
	virtual KColor		GetHoverColor() const ;
	virtual void		SetHoverColor(const KColor & color) ;

	virtual void		SetShowUnderline(bool bValue) ;
	virtual bool		GetShowUnderline() const ;

private:
	KColor				m_Color;
	KString				m_URL;
	bool				m_bShowLine;
	bool				m_bHover;
	bool				m_bPressed;

	HFONT				m_FontLine;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_HYPERLINK_IMPL_H_INCLUDED__