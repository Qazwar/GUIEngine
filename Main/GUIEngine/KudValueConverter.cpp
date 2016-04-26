//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudValueConverter.cpp
///	@brief		Implement of XML layout value converter.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "tinyxml.h"
#include "BaseDefines.h"
#include "IEventHandler.h"
#include "KudUIDefines.h"
#include "KudUIEnums.h"
#include "KudValueConverter.h"

KDNAMESTART

KDNAMELOT

KDE_LAYOUT_ERROR KValueConverter::ToBool(const std::string & strValue, bool & bValue)
{
	if (KSTRCMP(strValue.c_str(), "true") == 0 ||
		KSTRCMP(strValue.c_str(), "1") == 0 ||
		KSTRCMP(strValue.c_str(), "enabled") == 0)
	{
		bValue = true;
		return ERROR_OK;
	}
	else if (KSTRCMP(strValue.c_str(), "false") == 0 ||
		KSTRCMP(strValue.c_str(), "0") == 0 ||
		KSTRCMP(strValue.c_str(), "disabled") == 0)
	{
		bValue = false;
		return ERROR_OK;
	}
	else
	{
		return ERROR_VALUE_FORMAT;
	}
}

KDE_LAYOUT_ERROR KValueConverter::ToInt(const std::string & strValue, SInt32 & iValue)
{
	SInt32 nValue = atoi(strValue.c_str());
	iValue = nValue;
	return ERROR_OK;
}

KDE_LAYOUT_ERROR KValueConverter::ToMargin(const std::string & strValue, KRect & rcMargin)
{
	if (strstr(strValue.c_str(), ",") == NULL)
	{
		SInt32 nValue = atoi(strValue.c_str());
		rcMargin.left = rcMargin.right = rcMargin.top = rcMargin.bottom = nValue;
	}
	else
	{
		char * pStrValue = const_cast<char*>(strValue.c_str());
		char * pToken = strtok(pStrValue, ",");
		SInt32 nNumber[4] = {-1};
		SInt32 * pNO = nNumber;
		while (NULL != pToken)
		{
			*pNO = atoi(pToken);
			pNO++;
			pToken = strtok(NULL, ",");
		}
		if (nNumber[0] == -1 || nNumber[1] == -1 ||
			nNumber[2] == -1 || nNumber[3] == -1)
            return ERROR_VALUE_FORMAT;

		rcMargin.left	= nNumber[0];
		rcMargin.top	= nNumber[1];
		rcMargin.right	= nNumber[2];
		rcMargin.bottom	= nNumber[3];
	}
	return ERROR_OK;
}


KDE_LAYOUT_ERROR KValueConverter::ToColor(const std::string & strValue, KColor & color)
{
	if (strstr(strValue.c_str(), ",") == NULL)
	{
		SInt32 nValue = atoi(strValue.c_str());
		color.m_B = color.m_G = color.m_R = nValue;
	}
	else
	{
		char * pStrValue = const_cast<char*>(strValue.c_str());
		char * pToken = strtok(pStrValue, ",");
		SInt32 nNumber[3] = {-1};
		SInt32 * pNO = nNumber;
		while (NULL != pToken)
		{
			*pNO = atoi(pToken);
			pNO++;
			pToken = strtok(NULL, ",");
		}
		if (nNumber[0] == -1 || nNumber[1] == -1 ||	nNumber[2] == -1 )
            return ERROR_VALUE_FORMAT;

		color.m_R	= nNumber[0];
		color.m_G	= nNumber[1];
		color.m_B	= nNumber[2];
	}
	return ERROR_OK;
}

KDE_GUI_ORIENTATION	KValueConverter::ToOrientation(const std::string & strValue)
{
	if (KSTRCMP(strValue.c_str(), "vertical") == 0)
		return KGO_VERTICAL;
	else
		return KGO_HORIZONTAL;
}

KDE_LAYOUT_ERROR KValueConverter::ToElementType(const std::string & strValue, KDE_ELEMENT_TYPE & eElementType)
{
	typedef std::map<std::string, KDE_ELEMENT_TYPE> TYPEMAP;
	typedef std::map<std::string, KDE_ELEMENT_TYPE>::iterator TYPEMAPIT;
	static const TYPEMAP::value_type rawData[] =
	{
		TYPEMAP::value_type(RUI_CONTROL_LAYOUT_STACK	,	EET_LAYOUT_STACKPANEL),
		TYPEMAP::value_type(RUI_CONTROL_LAYOUT_DOCK		,	EET_LAYOUT_DOCKPANEL),
		TYPEMAP::value_type(RUI_CONTROL_LAYOUT_BASIC	,	EET_LAYOUT_BASICPANEL),

		TYPEMAP::value_type(RUI_CONTROL_TYPE_LABEL		,	EET_CONTROL_LABEL),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_BUTTON		,	EET_CONTROL_BUTTON),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_RPTBUTTON	,	EET_CONTROL_RPTBUTTON),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_CHECKBOX	,	EET_CONTROL_CHECKBOX),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_RADIO		,	EET_CONTROL_RADIOBOX),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_IMAGE		,	EET_CONTROL_IMAGE),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_EDIT		,	EET_CONTROL_EDIT),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_GROUPBOX	,	EET_CONTROL_GROUPBOX),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_PROGRESS	,	EET_CONTROL_PROGRESS),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_LISTBOX	,	EET_CONTROL_LISTBOX),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_COMBOBOX	,	EET_CONTROL_COMBOBOX),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_MENU		,	EET_CONTROL_MENU),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_CONTEXTMENU,	EET_CONTROL_CONTEXTMENU),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_TOOLBAR	,	EET_CONTROL_TOOLBAR),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_SCROLLBAR	,	EET_CONTROL_SCROLLBAR),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_SLIDER		,	EET_CONTROL_SLIDER),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_TABCTRL	,	EET_CONTROL_TABCTRL),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_LISTVIEW	,	EET_CONTROL_LISTVIEW),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_HYPERLINK	,	EET_CONTROL_HYPERLINK),
		TYPEMAP::value_type(RUI_CONTROL_TYPE_TREEVIEW	,	EET_CONTROL_TREEVIEW),
	};

	static const int numElems = sizeof(rawData) / sizeof(rawData[0]);
	static TYPEMAP typeMapData(rawData, rawData + numElems);

	TYPEMAPIT it = typeMapData.find(strValue.c_str());
	TYPEMAPIT itend = typeMapData.end();
	if (it != itend)
	{
		eElementType = (*it).second;
		return ERROR_OK;
	}
	
	eElementType = EET_INVALID;
	return ERROR_OK;
}

KDNAMELOTEND

KDNAMEEND