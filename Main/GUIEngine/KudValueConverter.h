//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudValueConverter.h
///	@brief		Declare base methods to read XML layout value.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_LAYOUT_XML_VALUECONVERTER_H_INCLUDED__
#define KUDEET_LAYOUT_XML_VALUECONVERTER_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMELOT

#define		KSTRCMP		stricmp

//! Helper class to converter the string value from XML layout to target type.
class KValueConverter
{
public:
	static KDE_LAYOUT_ERROR			ToBool(const std::string & strValue, bool & bValue);
	static KDE_LAYOUT_ERROR			ToInt(const std::string & strValue, SInt32 & iValue);
	static KDE_LAYOUT_ERROR			ToMargin(const std::string & strValue, KRect & rcMargin);
	static KDE_LAYOUT_ERROR			ToColor(const std::string & strValue, KColor & color);
	static KDE_LAYOUT_ERROR			ToElementType(const std::string & strValue, KDE_ELEMENT_TYPE & eElementType);
	
	static KDE_LAYOUT_ERROR			ToDock(const std::string & strValue);
	static KDE_GUI_ORIENTATION		ToOrientation(const std::string & strValue);
};

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_LAYOUT_XML_VALUECONVERTER_H_INCLUDED__