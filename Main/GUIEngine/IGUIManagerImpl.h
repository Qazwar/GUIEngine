//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIManagerImpl.h
///	@brief		Implement Kudeet GUI manager interface.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_MANAGERIMPL_IMPL_H_INCLUDED__
#define KUDEET_GUI_NANAGERIMPL_IMPL_H_INCLUDED__

#pragma once

#include "BaseDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "KudUIDefines.h"
#include "KudUIEnums.h"
#include "IGUIElement.h"
#include "IGUIWindow.h"
#include "IGUIManager.h"
#include "KudWin32Wnd.h"
#include "KudGUISkin.h"
#include "KudLayoutParser.h"

KDNAMESTART

typedef std::map<KString, GUI::IGUIWindow* >			WNDLIST;
typedef std::map<KString, GUI::IGUIWindow* >::iterator	WNDLISTIT;

class IGUIManagerImpl : public IGUIManager
{
public:
	IGUIManagerImpl()
	{
#ifdef USE_GDIPLUS
		m_gdiplusToken = NULL;
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
#endif
	}

	virtual ~IGUIManagerImpl()
	{
		WNDLISTIT it = m_WndList.begin();
		WNDLISTIT itend = m_WndList.end();
		for ( ; it != itend; it++)
		{
			((*it).second)->Drop();
		}
#ifdef USE_GDIPLUS
		GdiplusShutdown(m_gdiplusToken);
#endif
	}

public:
	virtual bool LoadLayout(const KString & strLayoutFile)
	{
		return LAYOUT::KXmlParser::ParseXMLLayout(strLayoutFile, m_WndList);
	}

	virtual void UpdateGUISkin(KColor & color)
	{
		GUI::KGUISkin::GetInstance()->SetBaseColor(color);
	}

	virtual GUI::IGUIWindow * GetLayoutWindow(const KString & strWndName)
	{
		WNDLISTIT it = m_WndList.find(strWndName);
		if (it != m_WndList.end())
		{
			GUI::IGUIWindow* pRetWnd = (*it).second;
			if (pRetWnd->IsValid())
			{
				return (*it).second;
			}
			else
			{
				pRetWnd =  LAYOUT::KXmlParser::ReloadWindow(strWndName);
				if (pRetWnd != NULL)
				{
					m_WndList[strWndName] = pRetWnd;
					return pRetWnd;
				}
			}
		}
		return NULL;
	}

protected:
	WNDLIST			m_WndList;	/*<! Window list in this layout file.	*/
	HINSTANCE		m_hInst;

#ifdef USE_GDIPLUS
	ULONG_PTR		m_gdiplusToken;
#endif	
};

KDNAMEEND

#endif //KUDEET_GUI_NANAGERIMPL_IMPL_H_INCLUDED__