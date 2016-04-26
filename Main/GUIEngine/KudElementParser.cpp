//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudBasicElementParser.cpp
///	@brief		Implement of basic control attributes parser
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "tinyxml.h"
#include "BaseDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "KudUIDefines.h"
#include "KudUIEnums.h"
#include "IGUIElement.h"
#include "IGUITexture.h"
#include "IGUIWindow.h"
#include "IMUIManager.h"

#include "KudGUIProgress.h"
#include "KudElementParser.h"
#include "KudWin32Wnd.h"
#include "KudValueConverter.h"
#include "KudGUIStatic.h"
#include "KudGUIButton.h"
#include "KudGUIEdit.h"
#include "KudGUIHyperLink.h"
#include "KudGUIComboBox.h"
#include "KudGUIScrollBar.h"
#include "KudGUIListBox.h"
#include "KudGUISlider.h"
#include "KudStringHelper.h"
#include "KudMUIManager.h"
#include "KudRadioGroupsMgr.h"

KDNAMESTART

KDNAMELOT

bool KElementParser::ParsePublicAttrs(TiXmlElement *& pXmlElement, GUI::IGUIElement * pElement, bool bHasText)
{
	if (NULL == pXmlElement || NULL == pElement)
		return false;

	PARSE_START_DATA(pXmlElement, pElement);

	if (bHasText)
	{
		PARSE_RES_ATTRIBUTE(RUI_ATTR_PUBLIC_TEXT, ElementText);
	}

	PARSE_STR_ATTRIBUTE(RUI_ATTR_PUBLIC_NAME, ElementName);

	pStrValue = pXmlElement->Attribute(RUI_ATTR_PUBLIC_MARGIN);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		KRect rc;
		if (KValueConverter::ToMargin(pStrValue, rc))
			pElement->SetMargin(rc);
	}

	PARSE_BOOL_ATTRIBUTE(RUI_ATTR_PUBLIC_ISVISIBLE, IsVisible);
	PARSE_BOOL_ATTRIBUTE(RUI_ATTR_PUBLIC_ISENABLE,	IsEnable);

	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_LEFT,		Left);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_TOP,		Top);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_RIGHT,		Right);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_BOTTOM,		Bottom);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_WIDTH,		Width);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_HEIGHT,		Height);

	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_ID,			CtrlID);
	
	// User defined CtrlID must be bigger than 2000, 0 ~ 2000 is reserved by GUI system.
	assert(nValue != 0 || nValue < 2000);

	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_MAXWIDTH,	MaxWidth);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_MAXHEIGHT,	MaxHeight);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_MINWIDTH,	MinWidth);
	PARSE_INT_ATTRIBUTE(RUI_ATTR_PUBLIC_MINHEIGHT,	MinHeight);

	return true;
}

GUI::IGUIElement * KElementParser::ParseElementNode(TiXmlElement * & pXmlElement, KDE_ELEMENT_TYPE enType)
{
	switch (enType)
	{
	case EET_CONTROL_EDIT:
		return KElementParser::ParseEdit(pXmlElement);
		break;
	case EET_CONTROL_LABEL:
	case EET_CONTROL_IMAGE:
	case EET_CONTROL_GROUPBOX:
		return KElementParser::ParseStatic(pXmlElement, enType);
		break;

	case EET_CONTROL_PROGRESS:
		return KElementParser::ParseProgress(pXmlElement);
		break;

	case EET_CONTROL_RPTBUTTON:
	case EET_CONTROL_BUTTON:
	case EET_CONTROL_CHECKBOX:
	case EET_CONTROL_RADIOBOX:
		return KElementParser::ParseButton(pXmlElement, enType);
		break;
	
	case EET_CONTROL_LISTBOX:
		return KElementParser::ParseListBox(pXmlElement);
		break;
	case EET_CONTROL_COMBOBOX:
		return KElementParser::ParseComboBox(pXmlElement);
		break;
	case EET_CONTROL_MENU:
		break;
	case EET_CONTROL_TOOLBAR:
		break;
	case EET_CONTROL_SCROLLBAR:
		return KElementParser::ParseScrollBar(pXmlElement);
		break;
	case EET_CONTROL_SLIDER:
		return KElementParser::ParseSlider(pXmlElement);
		break;
	case EET_CONTROL_LISTVIEW:
		break;
	case EET_CONTROL_TREEVIEW:
		break;
	case EET_CONTROL_HYPERLINK:
		return KElementParser::ParseHyperLink(pXmlElement);
		break;
	default:
		return NULL;
	}
	return NULL;
}

GUI::IGUIElement *	KElementParser::ParseProgress(TiXmlElement * & pXmlElement)
{
	GUI::IGUIProgress * pBar = new GUI::KGUIProgress();
	KElementParser::ParsePublicAttrs(pXmlElement, pBar);

	const char *pStrValue = pXmlElement->Attribute(RUI_SUBATTR_PROGRESS_MIN);
	const char *pStrValue2 = pXmlElement->Attribute(RUI_SUBATTR_PROGRESS_MAX);
	if (NULL != pStrValue && strlen(pStrValue) != 0 && NULL != pStrValue2 && strlen(pStrValue2) != 0)
	{
		SInt32	nValue = 0, nValue2 = 0;	
		KValueConverter::ToInt(pStrValue, nValue);
		KValueConverter::ToInt(pStrValue2, nValue2);
		pBar->SetRange(nValue, nValue2);
		pStrValue = NULL;
	}

	pStrValue = pXmlElement->Attribute(RUI_SUBATTR_PROGRESS_VALUE);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		SInt32	nValue = 0;
		KValueConverter::ToInt(pStrValue, nValue);
		pBar->SetValue(nValue);
	}

	return pBar;
}

GUI::IGUIElement *	KElementParser::ParseScrollBar(TiXmlElement * & pXmlElement)
{
	GUI::IGUIScrollBar * pBar = new GUI::KGUIScrollBar();
	KElementParser::ParsePublicAttrs(pXmlElement, pBar);

	const char * pStrValue = pXmlElement->Attribute(RUI_SUBATTR_LAYOUT_ORIENTATION);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
		pBar->SetOrientation(KValueConverter::ToOrientation(pStrValue));
	return pBar;
}

GUI::IGUIElement *	KElementParser::ParseHyperLink(TiXmlElement * & pXmlElement)
{
	GUI::IGUIHyperLink * pLink = new GUI::KGUIHyperLink();
	KElementParser::ParsePublicAttrs(pXmlElement, pLink, true);

	const char * pStrValue = pXmlElement->Attribute(RUI_SUBATTR_LINK_URL);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		std::wstring strW;
		KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);
		pLink->SetURL(strW.c_str());
	}
	return pLink;
}

GUI::IGUIElement *	KElementParser::ParseComboBox(TiXmlElement * & pXmlElement)
{
	GUI::IGUIComboBox * pCombo = new GUI::KGUIComboBox();
	KElementParser::ParsePublicAttrs(pXmlElement, pCombo);
	return pCombo;
}

GUI::IGUIElement * KElementParser::ParseEdit(TiXmlElement * & pXmlElement)
{
	GUI::IGUIEditBox * pEdit = new GUI::KGUIEditBox();
	KElementParser::ParsePublicAttrs(pXmlElement, pEdit, true);

	const char * pStrValue = pXmlElement->Attribute(RUI_SUBATTR_EDIT_READONLY);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		bool bValue;
		KValueConverter::ToBool(pStrValue, bValue);
		pEdit->SetReadOnly(bValue);
	}
	return pEdit;
}

GUI::IGUIElement * KElementParser::ParseButton(TiXmlElement *& pXmlElement, KDE_ELEMENT_TYPE btnType)
{
	GUI::IGUIButton * pBtn = new GUI::KGUIButton();
	pBtn->SetElementType(btnType);
	KElementParser::ParsePublicAttrs(pXmlElement, pBtn, true);

	switch (btnType)
	{
	case EET_CONTROL_BUTTON:
		break;
	case EET_CONTROL_RPTBUTTON:
		break;
	case EET_CONTROL_CHECKBOX:
		{
			bool bValue;
			const char * pStrValue = pXmlElement->Attribute(RUI_SUBATTR_BUTTON_CHECK);
			if (NULL != pStrValue && strlen(pStrValue) != 0)
			{				
				KValueConverter::ToBool(pStrValue, bValue);
				pBtn->SetIsChecked(bValue);
			}
			pStrValue = pXmlElement->Attribute(RUI_SUBATTR_BUTTON_THREESTATE);
			if (NULL != pStrValue && strlen(pStrValue) != 0)
			{
				KValueConverter::ToBool(pStrValue, bValue);
				pBtn->SetIsThreeState(bValue);
			}
		}
		break;
	case EET_CONTROL_RADIOBOX:
		{
			bool bValue;
			const char * pStrValue = pXmlElement->Attribute(RUI_SUBATTR_BUTTON_CHECK);
			if (NULL != pStrValue && strlen(pStrValue) != 0)
			{
				KValueConverter::ToBool(pStrValue, bValue);
				pBtn->SetIsChecked(bValue);
			}
			pStrValue = pXmlElement->Attribute(RUI_SUBATTR_BUTTON_GROUPNAME);
			if (NULL != pStrValue && strlen(pStrValue) != 0)
			{
				std::wstring strW;
				KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);
				pBtn->SetGroupName(strW.c_str());				
			}
			GUI::KRadioGroupMgr::GetInstance()->AddRadio(pBtn->GroupName(), pBtn);
		}
		break;
	default:
		assert(false);
	}	
	return pBtn;
}

GUI::IGUIElement * KElementParser::ParseListBox(TiXmlElement * & pXmlElement)
{
	GUI::IGUIListBox * pList = new GUI::KGUIListBox();
	KElementParser::ParsePublicAttrs(pXmlElement, pList);
	return pList;
}

GUI::IGUIElement * KElementParser::ParseSlider(TiXmlElement * & pXmlElement)
{
	GUI::IGUISlider * pSlider = new GUI::KGUISlider();
	KElementParser::ParsePublicAttrs(pXmlElement, pSlider);
	return pSlider;
}

GUI::IGUIElement * KElementParser::ParseStatic(TiXmlElement *& pXmlElement, KDE_ELEMENT_TYPE enType)
{
	GUI::IGUIStatic * pStatic = new GUI::KGUIStatic();
	pStatic->SetElementType(enType);
	KElementParser::ParsePublicAttrs(pXmlElement, pStatic, true);

	switch (enType)
	{
	case EET_CONTROL_LABEL:
		break;
	case EET_CONTROL_GROUPBOX:		
		break;
	case EET_CONTROL_IMAGE:
		break;
	default:
		assert(false);
	}	
	return pStatic;
}

KDNAMELOTEND

KDNAMEEND
