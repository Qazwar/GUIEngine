//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudLayoutParser.cpp
///	@brief		Implement of XML layout Parser.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Mar. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "tinyxml.h"
#include "BaseDefines.h"
#include "KudInternalUIDefines.h"
#include "IReferencePtr.h"
#include "IEventHandler.h"
#include "KudUIDefines.h"
#include "KudUIEnums.h"
#include "IGUIElement.h"
#include "IGUITexture.h"
#include "IGUIButton.h"
#include "IGUIWindow.h"
#include "KudWin32Wnd.h"
#include "KudValueConverter.h"
#include "IGUIManagerImpl.h"
#include "KudLayoutParser.h"
#include "IGUIBasicPanel.h"
#include "KudElementParser.h"
#include "KudGUISkin.h"
#include "KudStringHelper.h"
#include "KudGUIBasicPanel.h"
#include "IMUIManager.h"
#include "KudMUIManager.h"

KDNAMESTART

KDNAMELOT

KString KXmlParser::m_strLayoutFile = L"";

//! Get all the user defined const value in XML node.
bool KXmlParser::ResolveConst(TiXmlElement *& pXmlElement)
{
	return true;
}

bool KXmlParser::ParseLayout(TiXmlElement *& pLayoutNode, GUI::IGUIElement * const pParent, KDE_ELEMENT_TYPE enType)
{
	if (NULL == pLayoutNode || NULL == pParent)
		return false;

	GUI::IGUIElement * pLayout = NULL;	

	// parse layout specified attributes,
	const char* pStrValue = NULL;
	if (enType == EET_LAYOUT_STACKPANEL)
	{
		pStrValue = pLayoutNode->Attribute(RUI_SUBATTR_LAYOUT_ORIENTATION);
		if (NULL != pStrValue && strlen(pStrValue) != 0)
		{
			//
		}
	}
	else if (enType == EET_LAYOUT_DOCKPANEL)
	{

		pStrValue = pLayoutNode->Attribute(RUI_SUBATTR_LAYOUT_DOCK);
		if (NULL != pStrValue && strlen(pStrValue) != 0)
		{
			//
		}
	}
	else
	{
		assert(enType == EET_LAYOUT_BASICPANEL);
		pLayout = new GUI::KGUIBasicPanel();
	}

	KElementParser::ParsePublicAttrs(pLayoutNode, pLayout);

	// Get layout, and add into window children.
	pParent->AddChildElement(pLayout);
	pLayout->SetWindow(m_pWindow);

#ifdef _DEBUG
	assert(m_pWindow->CheckControlID(pLayout->CtrlID()));
#endif

	// Get layout children
	TiXmlHandle handle(pLayoutNode);
	TiXmlElement * pItems = handle.FirstChild(RUI_NODE_HEADER_ITEMS).ToElement();	
	TiXmlElement * pChild = pItems->FirstChildElement();
	for ( ; pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		enType = GetTypeValue(pChild);
		if (enType == EET_INVALID)
			continue;

		// Nesting layout...
		if (enType == EET_LAYOUT_STACKPANEL || enType == EET_LAYOUT_DOCKPANEL || enType == EET_LAYOUT_BASICPANEL)
		{
			ParseLayout(pChild, pLayout, enType);
		}

		// Parse specified element attributes based on type.
		GUI::IGUIElement * pGUI = KElementParser::ParseElementNode(pChild, enType);
		if (NULL != pGUI)
		{
			pGUI->SetParent(pLayout);
			pGUI->SetWindow(m_pWindow);
			pLayout->AddChildElement(pGUI);
#ifdef _DEBUG
			// Check to make sure CtrlID is not repeated.
			assert(m_pWindow->CheckControlID(pGUI->CtrlID()));
#endif
		}
	}

	return true;
}

bool KXmlParser::CheckNodeValue(TiXmlElement *& pXmlElement,	const std::string & strValue)
{
	if (NULL == pXmlElement || strValue.length() <= 0)
		return false;

	std::string nodeValue = pXmlElement->Value();
	if (KSTRCMP(nodeValue.c_str(), strValue.c_str()) != 0)
		return false;

	return true;
}

bool KXmlParser::ParseWindowContent(TiXmlElement *& pXmlElement)
{
	if (NULL == pXmlElement)
		return false;

	TiXmlHandle handle(pXmlElement);
	TiXmlElement * pXmlLayout = handle.FirstChild(RUI_NODE_HEADER_LAYOUT).ToElement();
	
	// Currently, only support three types of layout
	KDE_ELEMENT_TYPE enType = GetTypeValue(pXmlLayout);
	if (enType != EET_LAYOUT_STACKPANEL && enType != EET_LAYOUT_DOCKPANEL && enType != EET_LAYOUT_BASICPANEL)
		return false;
	
	bool bRet = ParseLayout(pXmlLayout, m_pWindow, enType);
	if (!bRet)
		return false;

	return true;
}

bool KXmlParser::ParseWindowSelf(TiXmlElement *& pXmlElement, GUI::IGUIWindow* const pWindow)
{
	if (NULL == pXmlElement || NULL == pWindow)
		return false;

	m_pWindow = pWindow;

	// must set the name attribute of window.
	const char* pStrValue = pXmlElement->Attribute(RUI_ATTR_PUBLIC_NAME);
	if (NULL == pStrValue || strlen(pStrValue) == 0)
		return false;

	pStrValue = pXmlElement->Attribute(RUI_SUBATTR_WINDOW_MINIMIZE);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		bool bValue;
		KValueConverter::ToBool(pStrValue, bValue);
		m_pWindow->SetCanBeMinimized(bValue);
	}

	pStrValue = pXmlElement->Attribute(RUI_SUBATTR_WINDOW_ISMAIN);	// isMain
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		bool bValue;
		KValueConverter::ToBool(pStrValue, bValue);
		m_pWindow->SetIsMain(bValue);
	}

	KElementParser::ParsePublicAttrs(pXmlElement, m_pWindow);

	// Check the layout structure, it should be window/layout/items/
	TiXmlHandle handle(pXmlElement);
	TiXmlElement * pLayout = handle.FirstChild(RUI_NODE_HEADER_LAYOUT).ToElement();
	if (NULL == pLayout)
		return false;
	TiXmlElement * pItems = handle.FirstChild(RUI_NODE_HEADER_LAYOUT).FirstChild(RUI_NODE_HEADER_ITEMS).ToElement();
	if (NULL == pItems)
		return false;

	// parse window specified attributes,  title
	pStrValue = pXmlElement->Attribute(RUI_SUBATTR_WINDOW_TITLE);
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		UInt32 nResID = atoi(pStrValue);
		std::wstring strW = KMUIManager::GetInstance()->GetString(nResID);
		//KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);
		m_pWindow->SetElementText(strW.c_str());
	}

	return true;
}

KDE_ELEMENT_TYPE KXmlParser::GetTypeValue(TiXmlElement *& pXmlElement)
{
	const char * pTypeValue = NULL;
	pTypeValue = pXmlElement->Attribute(RUI_ATTR_PUBLIC_TYPE);	// Read type attribute.
	if (NULL == pTypeValue)
		return EET_INVALID;

	KDE_ELEMENT_TYPE eType = EET_INVALID;
	KValueConverter::ToElementType(pTypeValue, eType);
	return eType;
}

bool KXmlParser::ParseLanguages(TiXmlElement *& pXmlElement)
{
	// Get current path.
	KString szDir = m_strLayoutFile.substr(0, m_strLayoutFile.rfind(L"\\") + 1);

	IMUIManager* pMUI = KMUIManager::GetInstance();

	SInt32 nResID = 0;
	if (TIXML_SUCCESS == pXmlElement->QueryIntAttribute(RUI_SUBATTR_LANGUAGE_DEFAULT, &nResID))
	{
		pMUI->SetDefaultLangID(nResID);
	}

	TiXmlElement * pLanguage = pXmlElement->FirstChildElement();
	while(pLanguage != NULL)
	{
		const char* pIDValue = pLanguage->Attribute(RUI_SUBATTR_LANGUAGE_ID);
		if (NULL != pIDValue && strlen(pIDValue) != 0)
		{
			const char* pFileValue = pLanguage->Attribute(RUI_SUBATTR_LANGUAGE_RESFILE);
			if (NULL != pFileValue && strlen(pFileValue) != 0)
			{
				UInt32 nLang = atoi(pIDValue);
				std::wstring strW;
				KStringHelper::Win32_UTF8_UNICODE(pFileValue, strW);
				KString szResPath = szDir;
				szResPath.append(strW);
				pMUI->AddStringTable(szResPath.c_str(), nLang);
			}			
		}
		pLanguage = pLanguage->NextSiblingElement();
	}
	return true;
}

bool KXmlParser::ParseRootResource(TiXmlElement *& pXmlElement)
{
	TiXmlElement * pRes = pXmlElement->FirstChildElement();
	if (pRes == NULL)
		return false;

	const char* pStrValue = pRes->Attribute(RUI_SUBATTR_RESOURCES_ICON);	// icon
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		KString szDir = m_strLayoutFile.substr(0, m_strLayoutFile.rfind(L"\\"));
		KString szIconPath = szDir;
		szIconPath.append(L"\\");
		std::wstring strW;
		KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);
		szIconPath.append(strW);
		HICON hIcon = (HICON)::LoadImage(NULL, szIconPath.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hIcon != NULL)
		{
			GUI::KGUISkin::GetInstance()->SetIcon(hIcon);
		}
	}

	/*pStrValue = pRes->Attribute(RUI_SUBATTR_RESOURCES_BASECOLOR);	// Base color
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		KColor color;
		KValueConverter::ToColor(pStrValue, color);
		GUI::KGUISkin::GetInstance()->SetBaseColor(color);
	}

	pStrValue = pRes->Attribute(RUI_SUBATTR_RESOURCES_FONTCOLOR);	// font color
	if (NULL != pStrValue && strlen(pStrValue) != 0)
	{
		KColor color;
		KValueConverter::ToColor(pStrValue, color);
		GUI::KGUISkin::GetInstance()->SetTextColor(color);
	}*/	

	return true;
}

bool KXmlParser::ParseXMLLayout(const KString & strFile, std::map<KString, GUI::IGUIWindow* > & wndList)
{
	wndList.clear();

	KMUIManager::GetInstance()->SetUserLangID(2052);

	FILE * pFile = _wfopen(strFile.c_str(), L"rb");
	{
		if (pFile == NULL)
			return false;

		m_strLayoutFile = strFile;

		TiXmlDocument xmlDOC;
		bool bLoad = xmlDOC.LoadFile(pFile);
		if (!bLoad)
			return false;

		TiXmlElement * pRoot = xmlDOC.RootElement();
		if (NULL == pRoot)
			return false;

		// Check root node, should be "root".
		if (!KXmlParser::CheckNodeValue(pRoot, RUI_NODE_HEADER_ROOT))
			return false;

		TiXmlElement * pRootChild = pRoot->FirstChildElement();
		for (; pRootChild != NULL; pRootChild = pRootChild->NextSiblingElement())
		{
			if (KXmlParser::CheckNodeValue(pRootChild, RUI_NODE_HEADER_RESOURCES))
			{
				KXmlParser::ParseRootResource(pRootChild);
				continue;
			}

			if (KXmlParser::CheckNodeValue(pRootChild, RUI_NODE_HEADER_LANGS))
			{
				KXmlParser::ParseLanguages(pRootChild);
				continue;
			}

			if (!KXmlParser::CheckNodeValue(pRootChild, RUI_NODE_HEADER_WINDOW))
				continue;
			
			GUI::IGUIWindow * pWindow = new GUI::KGUIWin32Wnd();
			if (NULL != pWindow)
			{
				if (ParseWindow(pRootChild, pWindow))
				{
					wndList[pWindow->ElementName()] = pWindow;
				}
			}
		}
	}
	fclose(pFile);

	// If only one window, make this as main window
	if (wndList.size() == 1)
	{
		((*(wndList.begin())).second)->SetIsMain(true);
	}

	return true;
}

GUI::IGUIWindow* KXmlParser::ReloadWindow(const KString& strName)
{
	FILE * pFile = _wfopen(m_strLayoutFile.c_str(), L"rb");
	{
		if (pFile == NULL)
			return false;

		TiXmlDocument xmlDOC;
		bool bLoad = xmlDOC.LoadFile(pFile);
		if (!bLoad)
			return false;

		TiXmlElement * pRoot = xmlDOC.RootElement();
		if (NULL == pRoot)
			return false;

		// Check root node, should be "root".
		if (!KXmlParser::CheckNodeValue(pRoot, RUI_NODE_HEADER_ROOT))
			return false;

		TiXmlElement * pRootChild = pRoot->FirstChildElement();
		for (; pRootChild != NULL; pRootChild = pRootChild->NextSiblingElement())
		{
			if (!KXmlParser::CheckNodeValue(pRootChild, RUI_NODE_HEADER_WINDOW))
				continue;

			// Check name attribute of window.
			const char* pStrValue = pRootChild->Attribute(RUI_ATTR_PUBLIC_NAME);
			if (NULL != pStrValue && strlen(pStrValue) > 0)
			{
				std::wstring strW;
				KStringHelper::Win32_UTF8_UNICODE(pStrValue, strW);
				if (wcscmp(strW.c_str(), strName.c_str()) == 0)
				{
					GUI::IGUIWindow * pWindow = new GUI::KGUIWin32Wnd();
					if (NULL != pWindow)
					{
						if (ParseWindow(pRootChild, pWindow))
						{
							return pWindow;
						}
					}
					break;
				}
			}			
		}
	}
	fclose(pFile);

	return NULL;
}

bool KXmlParser::ParseWindow(TiXmlElement *& pXmlElement,	GUI::IGUIWindow* const pWindow)
{
	KXmlParser parser;
	if (!parser.ParseWindowSelf(pXmlElement, pWindow))
	{
		pWindow->Drop();
		return false;
	}

	bool bRet = pWindow->CreateKDWnd(NULL, GUI::KGUISkin::GetInstance()->GetIcon());
	if (!bRet)
	{
		pWindow->Drop();
		false;
	}

	bRet = parser.ParseWindowContent(pXmlElement);
	if (!bRet)
	{
		pWindow->Drop();
		false;
	}

	pWindow->UpdateElementLayout();
	return true;
}

KDNAMELOTEND

KDNAMEEND