//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudElementParser.h
///	@brief		Declare basic control attributes parser
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_LAYOUT_ELEMENT_PARSER_H_INCLUDED__
#define KUDEET_LAYOUT_ELEMENT_PARSER_H_INCLUDED__

#pragma once

//! Forward declare
class TiXmlElement;

KDNAMESTART

KDNAMELOT

#define PARSE_START_DATA(pXmlElement, pElement)	\
	bool	bValue = false;	\
	SInt32	nValue = 0;		\
	const char *	pStrValue = NULL;			\
	TiXmlElement*	pXml = pXmlElement;			\
	GUI::IGUIElement*	pCtrl = pElement;

#define PARSE_BOOL_ATTRIBUTE(pszAttribute, funName)		\
	pStrValue = pXml->Attribute(pszAttribute);			\
	if (NULL != pStrValue && strlen(pStrValue) != 0)	\
	{	\
		KValueConverter::ToBool(pStrValue, bValue);		\
		pCtrl->Set##funName(bValue);		\
		bValue = false;		\
		pStrValue = 0;		\
	}

#define PARSE_INT_ATTRIBUTE(pAttribute, funName)		\
	pStrValue = pXml->Attribute(pAttribute);			\
	if (NULL != pStrValue && strlen(pStrValue) != 0)	\
	{	\
		KValueConverter::ToInt(pStrValue, nValue);		\
		pCtrl->Set##funName(nValue);		\
		nValue  = 0;		\
		pStrValue = 0;		\
	}

#define PARSE_STR_ATTRIBUTE(pAttribute, funName)		\
	pStrValue = pXml->Attribute(pAttribute);			\
	if (NULL != pStrValue && strlen(pStrValue) != 0)	\
	{	\
		std::wstring strW;	\
		KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);	\
		pCtrl->Set##funName(strW.c_str());	\
		pStrValue = 0;		\
	}

#define PARSE_RES_ATTRIBUTE(pAttribute, funName)		\
	pStrValue = pXml->Attribute(pAttribute);			\
	if (NULL != pStrValue && strlen(pStrValue) != 0)	\
	{	\
		UInt32 nResID = atoi(pStrValue);	\
		LPCWSTR lpRet = KMUIManager::GetInstance()->GetString(nResID);	\
		if (lpRet != NULL)	\
		{	\
			pCtrl->Set##funName(lpRet);	\
		}	\
		pStrValue = 0;	\
	}

class KElementParser
{
public:	
	static	GUI::IGUIElement *		ParseHyperLink		(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseComboBox		(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseEdit			(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseScrollBar		(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseSlider			(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseListBox		(TiXmlElement * & pXmlElement);
	static	GUI::IGUIElement *		ParseProgress		(TiXmlElement * & pXmlElement);

	static	GUI::IGUIElement *		ParseButton			(TiXmlElement * & pXmlElement, KDE_ELEMENT_TYPE btnType);
	static	GUI::IGUIElement *		ParseElementNode	(TiXmlElement * & pXmlElement, KDE_ELEMENT_TYPE enType);
	static	GUI::IGUIElement *		ParseStatic			(TiXmlElement * & pXmlElement, KDE_ELEMENT_TYPE enType);

	static	bool					ParsePublicAttrs	(TiXmlElement * & pXmlElement, GUI::IGUIElement * pElement, bool bHasText = false);
};

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_LAYOUT_ELEMENT_PARSER_H_INCLUDED__
