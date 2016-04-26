//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudUIDefines.h
///	@brief		Declare the Kudeet GUI const strings.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_UIDEFINES_H_INCLUDED__
#define KUDEET_GUI_UIDEFINES_H_INCLUDED__

#pragma once

#include "KudUIConsts.h"

KDNAMESTART

KDNAMELOT

// all the xml layout node value.
#define		RUI_NODE_HEADER_ROOT				"root"
#define		RUI_NODE_HEADER_RESOURCES			"resources"
#define		RUI_NODE_HEADER_LANGS				"languages"
#define		RUI_NODE_HEADER_WINDOW				"window"
#define		RUI_NODE_HEADER_ITEMS				"items"
#define		RUI_NODE_HEADER_LAYOUT				"layout"
#define		RUI_NODE_HEADER_ELEMENT				"element"	// NOT USED

// control type.
#define		RUI_CONTROL_TYPE_LABEL				"label"
#define		RUI_CONTROL_TYPE_BUTTON				"button"
#define		RUI_CONTROL_TYPE_RPTBUTTON			"repeatbutton"
#define		RUI_CONTROL_TYPE_CHECKBOX			"checkbox"
#define		RUI_CONTROL_TYPE_RADIO				"radio"
#define		RUI_CONTROL_TYPE_IMAGE				"image"
#define		RUI_CONTROL_TYPE_EDIT				"edit"
#define		RUI_CONTROL_TYPE_GROUPBOX			"groupbox"
#define		RUI_CONTROL_TYPE_PROGRESS			"progress"
#define		RUI_CONTROL_TYPE_HYPERLINK			"hyperlink"
#define		RUI_CONTROL_TYPE_SLIDER				"slider"

#define		RUI_CONTROL_TYPE_LISTBOX			"listbox"
#define		RUI_CONTROL_TYPE_COMBOBOX			"combobox"
#define		RUI_CONTROL_TYPE_MENU				"menu"
#define		RUI_CONTROL_TYPE_CONTEXTMENU		"contextmenu"
#define		RUI_CONTROL_TYPE_TOOLBAR			"toolbar"
#define		RUI_CONTROL_TYPE_SCROLLBAR			"scrollbar"
#define		RUI_CONTROL_TYPE_TABCTRL			"tabctrl"
#define		RUI_CONTROL_TYPE_LISTVIEW			"listview"
#define		RUI_CONTROL_TYPE_TREEVIEW			"treeview"

// control layout container.
#define		RUI_CONTROL_LAYOUT_STACK			"stackpanel"
#define		RUI_CONTROL_LAYOUT_DOCK				"dockpanel"
#define		RUI_CONTROL_LAYOUT_BASIC			"basicpanel"	// Behavior like canvas


// Public control attributes.
#define		RUI_ATTR_PUBLIC_ISVISIBLE			"isVisible"
#define		RUI_ATTR_PUBLIC_ISENABLE			"isEnable"
#define		RUI_ATTR_PUBLIC_WIDTH				"width"
#define		RUI_ATTR_PUBLIC_HEIGHT				"height"
#define		RUI_ATTR_PUBLIC_MARGIN				"margin"
#define		RUI_ATTR_PUBLIC_LEFT				"left"
#define		RUI_ATTR_PUBLIC_TOP					"top"
#define		RUI_ATTR_PUBLIC_RIGHT				"right"
#define		RUI_ATTR_PUBLIC_BOTTOM				"bottom"
#define		RUI_ATTR_PUBLIC_MINWIDTH			"minimalWidth"
#define		RUI_ATTR_PUBLIC_MINHEIGHT			"minimalHeight"
#define		RUI_ATTR_PUBLIC_MAXWIDTH			"maximalWidth"
#define		RUI_ATTR_PUBLIC_MAXHEIGHT			"maximalHeight"
#define		RUI_ATTR_PUBLIC_TYPE				"type"
#define		RUI_ATTR_PUBLIC_ID					"ctrlid"
#define		RUI_ATTR_PUBLIC_NAME				"name"

#define		RUI_ATTR_PUBLIC_TEXT				"text"

#define		RUI_SUBATTR_EDIT_READONLY			"isReadOnly"
#define		RUI_SUBATTR_LINK_URL				"url"

// progress
#define		RUI_SUBATTR_PROGRESS_MIN			"minimize"
#define		RUI_SUBATTR_PROGRESS_MAX			"maximize"
#define		RUI_SUBATTR_PROGRESS_VALUE			"value"

// button...
#define		RUI_SUBATTR_BUTTON_CHECK			"isChecked"
#define		RUI_SUBATTR_BUTTON_GROUPNAME		"groupName"
#define		RUI_SUBATTR_BUTTON_THREESTATE		"isThreeState"

// special attributes for window
#define		RUI_SUBATTR_WINDOW_TITLE			"title"
#define		RUI_SUBATTR_WINDOW_MINIMIZE			"minimize"
#define		RUI_SUBATTR_WINDOW_CORNER			"corner"		// NOT USED
#define		RUI_SUBATTR_WINDOW_ISMAIN			"isMain"

// special attributes for resources
#define		RUI_SUBATTR_RESOURCES_ICON			"icon"
#define		RUI_SUBATTR_RESOURCES_FONTCOLOR		"fontColor"
#define		RUI_SUBATTR_RESOURCES_BASECOLOR		"baseColor"

// special attributes for resources
#define		RUI_SUBATTR_LANGUAGE_ID				"langID"
#define		RUI_SUBATTR_LANGUAGE_RESFILE		"resFile"
#define		RUI_SUBATTR_LANGUAGE_RESID			"resID"
#define		RUI_SUBATTR_LANGUAGE_DEFAULT		"defID"

// special attributes for layout
#define		RUI_SUBATTR_LAYOUT_ORIENTATION		"orientation"
#define		RUI_SUBATTR_LAYOUT_DOCK				"dock"

KDNAMELOTEND

KDNAMEEND

#endif //KUDEET_GUI_UIDEFINES_H_INCLUDED__