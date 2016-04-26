//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudLayoutParser.h
///	@brief		Declare parser to read XML layout.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_LAYOUT_XML_PARSER_H_INCLUDED__
#define KUDEET_LAYOUT_XML_PARSER_H_INCLUDED__

#pragma once

//! External class forward declare
class TiXmlElement;

KDNAMESTART

KDNAMELOT

//! Parse XML layout file to construct window tree.
class KXmlParser
{
private:
	static	KDE_ELEMENT_TYPE	GetTypeValue		(TiXmlElement *& pXmlElement);
	static	bool				ResolveConst		(TiXmlElement *& pXmlElement);
	bool						ParseWindowContent	(TiXmlElement *& pXmlElement);
	bool						ParseLayout			(TiXmlElement *& pLayoutNode,	GUI::IGUIElement *const pParent, KDE_ELEMENT_TYPE enType);
	bool						ParseWindowSelf		(TiXmlElement *& pXmlElement,	GUI::IGUIWindow* const pWindow);
	static	bool				ParseWindow			(TiXmlElement *& pXmlElement,	GUI::IGUIWindow* const pWindow);
	static	bool				CheckNodeValue		(TiXmlElement *& pXmlElement,	const std::string & strType);
	static	bool				ParseRootResource	(TiXmlElement *& pXmlElement);
	static	bool				ParseLanguages		(TiXmlElement *& pXmlElement);

public:	
	static	bool				ParseXMLLayout		(const KString & strFile,		std::map<KString, GUI::IGUIWindow* > & wndList);
	static	GUI::IGUIWindow*	ReloadWindow		(const KString& strName);	

private:
	GUI::IGUIWindow *			m_pWindow;
	static	KString				m_strLayoutFile;
};

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_LAYOUT_XML_PARSER_H_INCLUDED__