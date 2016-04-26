//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IEventHandler.h
///	@brief		Declare the event interface defination.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
///
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IEVENTHANDLER_H_INCLUDED__
#define KUDEET_GUI_IEVENTHANDLER_H_INCLUDED__

#pragma once

#include "KudKeyCodes.h"

KDNAMESTART

KDNAMEGUI

class IGUIElement;

enum KDE_MSGBOX_BUTTON
{
	EMB_MSGBOX_YES		= 0x01,
	EMB_MSGBOX_NO		= 0x02,
	EMB_MSGBOX_OK		= 0x04,
	EMB_MSGBOX_CANCEL	= 0x08,
};

//! Enumeration for all events which are sendable by the gui system
enum KDE_EVENT_GUI
{
	KGE_ELEMENT_LOSTFOCUS = 0,
	KGE_ELEMENT_FOCUSED,

	KGE_BUTTON_CLICKED,

	KGE_SCROLLBAR_CHANGED,

	KGE_CHECKBOX_CHECKED,
	KEG_CHECKBOX_UNCHECKED,

	KGE_RADIOBOX_CHECKED,

	KGE_LISTBOX_SELCHANGED,

	KGE_COMBOBOX_SELCHANGED,

	KGE_SPINBOX_CHANGED,

	KGE_MENUITEM_CLICKED,	//! Clicked one menu item.

	//! An element would like to close.
	/** Windows and context menus use this event when they would like to close,
	this can be cancelled by absorbing the event. */
	KGE_ELEMENT_CLOSED,

	KGE_EDITBOX_TEXTCHANGED,

	KGE_TABCTRL_SELCHANGED,

	KGE_TREEVIEW_NODE_DESELECT,
	KGE_TREEVIEW_NODE_SELECT,
	KGE_TREEVIEW_NODE_EXPAND,
	KGE_TREEVIEW_NODE_COLLAPS,

	KGE_EVENT_GUI_COUNT
};
	
KDNAMEGUIEND

//! Enumeration for all mouse input events
enum KDE_EVENT_MOUSE
{
	KME_LMOUSE_DOWN = 0,
	KME_RMOUSE_DOWN,
	KME_MMOUSE_DOWN,

	KME_LMOUSE_UP,
	KME_RMOUSE_UP,
	KME_MMOUSE_UP,

	KME_MOUSE_MOVED,
	KME_MOUSE_WHEEL,
	
	KME_MOUSE_ENTER,
	KME_MOUSE_LEAVE,

	KME_LMOUSE_DOUBLE_CLICK,
	KME_RMOUSE_DOUBLE_CLICK,
	KME_MMOUSE_DOUBLE_CLICK,
	
	KME_LMOUSE_TRIPLE_CLICK,
	KME_RMOUSE_TRIPLE_CLICK,
	KME_MMOUSE_TRIPLE_CLICK,

	KME_EVENT_MOUSE_COUNT
};

//! Masks for mouse button states
enum KDE_MOUSE_BUTTON_STATE_MASK
{
	EMBSM_LEFT			= 0x01,
	EMBSM_RIGHT			= 0x02,
	EMBSM_MIDDLE		= 0x04,
	EMBSM_EXTRA1		= 0x08,			//! currently only on windows
    EMBSM_EXTRA2		= 0x10,			//! currently only on windows	
	EMBSM_FORCE_32_BIT	= 0x7FFFFFFF
};

//! Enumeration for all event types there are.
enum KDE_EVENT_TYPE
{
	KET_GUI = 0,
	KET_MOUSE,
	KET_KEY,
	
	KET_EVENT_TYPE_COUNT,
	KET_32BIT = 0x7FFFFFFF
} ;

//! GUI event data structure.
struct KDS_EVENT_GUI
{
	//! IGUIElement who called the event
	GUI::IGUIElement*		Caller;

	//! If the event has something to do with another element, it will be held here.
	GUI::IGUIElement*		Element;

	//! Type of GUI Event
	GUI::KDE_EVENT_GUI		EventType;
};

//! Mouse event data structure.
struct KDS_EVENT_MOUSE
{
	SInt32	X;
	SInt32	Y;
	FInt32	Wheel;	//!Only valid if event was KME_MOUSE_WHEEL
    
	bool	Shift : 1;		//! True if shift was also pressed		
	bool	Control : 1;	//! True if ctrl was also pressed
	
	UInt32	ButtonStates;	//! Currently only valid if the event was KME_MOUSE_MOVED
	bool	IsLeftDown()	const	{ return 0 != (ButtonStates & EMBSM_LEFT );	}
	bool	IsRightDown()	const	{ return 0 != (ButtonStates & EMBSM_RIGHT);	}
	bool	IsMiddleDown()	const	{ return 0 != (ButtonStates & EMBSM_MIDDLE);}
	
	KDE_EVENT_MOUSE			Event;
};

//! Keyboard event data structure.
struct KDS_EVENT_KEY
{
	wchar_t			Char;
	KDE_KEY_CODE	Key;
	bool			PressedDown : 1;	//! If not true, then the key was left up
	bool			Shift : 1;			//! True if shift was also pressed
	bool			Control:1;			//! True if ctrl was also pressed		
};

//! KDS_EVENT hold information about an event.
struct KDS_EVENT
{
	KDE_EVENT_TYPE				EventType;
	union
	{
		struct KDS_EVENT_GUI	GUIEvent;
		struct KDS_EVENT_MOUSE	MouseEvent;
		struct KDS_EVENT_KEY	KeyEvent;
	};
} ;

class IEventHandler
{
public:
	virtual bool OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0) = 0;
};

KDNAMEEND

#endif // KUDEET_GUI_IEVENTHANDLER_H_INCLUDED__