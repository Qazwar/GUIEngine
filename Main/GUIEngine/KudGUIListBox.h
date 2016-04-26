//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudGUIListBox.h
///	@brief		Header file for KGUIListBox class, implements IGUIListBox.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_LISTBOX_IMPL_H_INCLUDED__
#define KUDEET_GUI_LISTBOX_IMPL_H_INCLUDED__

#pragma once

#include "IGUIListBox.h"

KDNAMESTART

KDNAMEGUI

#define	LISTBOXITEM_HEIGHT	22

class KGUIListBox : public IGUIListBox
{
public:
	KGUIListBox(IGUIElement* parent = NULL, UInt32 ctrlID = 0);
	virtual ~KGUIListBox(void);

	virtual void			Draw(HDC hDC, RECT rcPaint);
	virtual bool			OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0);

	virtual void			AddItem(const KString & strItem) ;
	virtual void			InsertItem(UInt32 nIndex, const KString & strItem) ;
	virtual void			ResetContent() ;
	virtual UInt32			GetCount() const ;
	virtual void			SetSelectIndex(SInt32 nIndex) ;

private:

	void					UpdateItems();

	std::list<KString>		m_ListItems;
	UInt32					m_nSelItem;
	HBRUSH					m_SelBrush;
	HBRUSH					m_SelHighBrush;

	IGUIScrollBar	*		m_pHorScroll;
	IGUIScrollBar	*		m_pVerScroll;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_LISTBOX_IMPL_H_INCLUDED__