//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudRadioGroupMgr.h
///	@brief		Implement Kudeet radio button group logic manager.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_RADIO_GROUPMGR_H_INCLUDED__
#define KUDEET_GUI_RADIO_GROUPMGR_H_INCLUDED__

#pragma once

#include "BaseDefines.h"

KDNAMESTART

KDNAMEGUI

typedef std::map<KString, std::list<IGUIButton*> > RADIOGROUPS;

// If use don't set the group name, use this default one.
#define DEFAULT_RADIO_GROUPNAME		L"DefautlGroup"

class KRadioGroupMgr
{
public:
	static KRadioGroupMgr*	GetInstance()
	{
		static KRadioGroupMgr radioMgr;
		return &radioMgr;
	}

	void AddRadio(KString strName, IGUIButton* pBtn)
	{
		if (strName.c_str() == NULL || strName.length() == 0)
			strName = DEFAULT_RADIO_GROUPNAME;

		RADIOGROUPS::iterator it = m_RadioGroup.find(strName);
		if (it == m_RadioGroup.end())
		{
			std::list<IGUIButton*> resList;
			resList.push_back(pBtn);
			m_RadioGroup[strName] = resList;
		}
		else
		{
			std::list<IGUIButton*> btnList = (*it).second;
			std::list<IGUIButton*>::iterator it = btnList.begin();
			for ( ; it != btnList.end(); it++)
			{
				IGUIButton* pBtnIt = (*it);
				if (pBtnIt->CtrlID() == pBtn->CtrlID())
					return;				
			}
			btnList.push_back(pBtn);
			m_RadioGroup[strName] = btnList;
		}
	}

	//! When use selected one radio, make sure others all are unselected.
	void UpdateRadioGroup(IGUIButton* pBtn)
	{
		if (!pBtn->IsChecked())
			return;

		KString strGroup = pBtn->GroupName();
		if (strGroup.c_str() == NULL || strGroup.length() == 0)
			strGroup = DEFAULT_RADIO_GROUPNAME;

		std::list<IGUIButton*> btnList = m_RadioGroup[strGroup];
		std::list<IGUIButton*>::iterator it = btnList.begin();
		for ( ; it != btnList.end(); it++)
		{
			IGUIButton* pBtnIt = (*it);
			if (pBtnIt->CtrlID() == pBtn->CtrlID())
				continue;

			pBtnIt->SetIsChecked(false);
		}
	}

private:
	KRadioGroupMgr(){}

	RADIOGROUPS	m_RadioGroup;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_RADIO_GROUPMGR_H_INCLUDED__