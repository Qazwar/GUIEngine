//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IEventCracker.h
///	@brief		Declare the event handler crack methods.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
///
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_EVENTCRACKER_H_INCLUDED__
#define KUDEET_GUI_EVENTCRACKER_H_INCLUDED__

#pragma once

KDNAMESTART

#define KDE_BEGIN_MSG_MAP(theClass) \
public: \
	bool OnEvent(const KDS_EVENT & event, UInt32 dwMsgMapID = 0) \
	{ \
		(event); \
		if (event.EventType != KET_GUI)	\
		{ \
			assert(false);	\
			return false;	\
		} \
		switch(dwMsgMapID) \
		{ \
		case 0:

#define KDE_GUI_MSG_HANDLER(msg, func) \
	if (event.GUIEvent.EventType == msg) \
	{ \
		if (func(event)) \
			return true; \
	}

#define KDE_CHAIN_MSG_MAP(theChainClass) \
	{ \
		if (theChainClass::OnEvent(event, dwMsgMapID)) \
			return true; \
	}

#define KDE_END_MSG_MAP() \
			break; \
		default: \
			assert(false); \
			break; \
		} \
		return false; \
	}

KDNAMEEND

#endif //KUDEET_GUI_EVENTCRACKER_H_INCLUDED__