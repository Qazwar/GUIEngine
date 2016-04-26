//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudUIEnums.h
///	@brief		Declare the Kudeet GUI Enum definition.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_ENUMS_H_INCLUDED__
#define KUDEET_GUI_ENUMS_H_INCLUDED__

#pragma once

KDNAMESTART

//! Definition for all elements type.
enum KDE_ELEMENT_TYPE
{
	EET_CONTROL_WINDOW = 0,
	
	EET_CONTROL_LABEL,
	EET_CONTROL_BUTTON,
	EET_CONTROL_IMAGE_BUTTON,
	EET_CONTROL_RPTBUTTON,
	EET_CONTROL_CHECKBOX,
	EET_CONTROL_RADIOBOX,
	EET_CONTROL_IMAGE,
	EET_CONTROL_EDIT,
	EET_CONTROL_GROUPBOX,
	EET_CONTROL_PROGRESS,

	EET_CONTROL_LISTBOX,
	EET_CONTROL_COMBOBOX,
	EET_CONTROL_MENU,
	EET_CONTROL_CONTEXTMENU,
	EET_CONTROL_TOOLBAR,
	EET_CONTROL_SCROLLBAR,
	EET_CONTROL_SLIDER,
	EET_CONTROL_TABCTRL,
	EET_CONTROL_LISTVIEW,
	EET_CONTROL_TREEVIEW,
	EET_CONTROL_HYPERLINK,

	EET_LAYOUT_STACKPANEL,
	EET_LAYOUT_DOCKPANEL,
	EET_LAYOUT_BASICPANEL,		/*!< BasicPanel will arrange sub-controls as declare order */

	EET_ELEMENT_COUNT,			/*!< This only is used to calculate elements count.	*/

	EET_INVALID					/*!< Invalid element type */
} ;

enum KDE_LAYOUT_ERROR
{
	ERROR_OK,
	ERROR_VALUE,
	ERROR_VALUE_FORMAT,
	ERROR_ELEMENT
} ;

enum KDE_GUI_DIRECTION
{
	ORIENTATION_LEFT,		/*!< Left		*/
	ORIENTATION_TOP,		/*!< Top		*/
	ORIENTATION_RIGHT,		/*!< Right		*/
	ORIENTATION_BOTTOM,		/*!< Bottom		*/
} ;

//! Definition for all orientation type.
enum KDE_GUI_ORIENTATION
{
	KGO_HORIZONTAL,			/*!< Horizontal	*/
	KGO_VERTICAL			/*!< Vertical	*/
} ;	


//! Definition for all alignment type.
enum KDE_GUI_ALIGNMENT
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT,
	ALIGN_TOP,
	ALIGN_BOTTOM
} ;	//! Enum type EGUI_ALIGNMENT

//! Enum of button state in different user operation.
enum KDE_BUTTON_STATE
{
	EBS_BUTTON_NORMAL	= 0X0001,
	EBS_BUTTON_PRESSED	= 0X0002,
	EBS_BUTTON_HOVER	= 0X0004,
	EBS_BUTTON_FOCUSED	= 0X0008,
	EBS_BUTTON_DISABLED = 0X0010,
} ;

//! Enum for all the image control scale type
enum KDE_IMAGE_SCALE
{
	EIS_SCALE_CENTER,
	EIS_SCALE_FITXY,
	EIS_SCALE_NORMAL
} ;

KDNAMEEND

#endif //KUDEET_GUI_ENUMS_H_INCLUDED__