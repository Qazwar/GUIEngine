//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KDMUIManager.h
///	@brief		Implement the kudeet MUI support header.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "Tinyxml.h"
#include "BaseDefines.h"
#include "KudUIDefines.h"
#include "IMUIManager.h"
#include "KudMUIManager.h"
#include "KudStringHelper.h"

KDNAMESTART

KMUIManager::KMUIManager(void)
{
	m_nUserLangID= 0;
	m_nSysLangID = 0;	
	m_nDefLangID = 0;
	m_nActiveID	 = 0;
	m_bLoaded	 = false;
	m_CurCached.clear();
	m_AllStrings.clear();
}

KMUIManager::~KMUIManager(void)
{
	m_AllStrings.clear();
	m_CurCached.clear();
}

bool KMUIManager::AddStringTable(LPCWSTR strFile, const UInt32 & nLangID)
{
	ALLLANGMAPSITR it = m_AllStrings.find(nLangID);
	if (it == m_AllStrings.end())
	{
		std::list<KString> resList;
		resList.push_back(strFile);
		m_AllStrings[nLangID] = resList;
	}
	else
	{
		m_AllStrings[nLangID].push_back(strFile);
	}
	return true;
}

void KMUIManager::LoadStringContent()
{
	std::list<KString> fileList = m_AllStrings[m_nActiveID];
	for (std::list<KString>::iterator it = fileList.begin();
		it != fileList.end(); it++)
	{
		KString strFile = *it;		
		{
			FILE * pFile = _wfopen((strFile.c_str()), L"rb");
			TiXmlDocument doc;
			if (doc.LoadFile(pFile))
			{
				TiXmlElement * pRoot = doc.RootElement();
				TiXmlElement * pChild = pRoot->FirstChildElement();
				while (pChild != NULL)
				{
					SInt32 nResID = 0;
					if (TIXML_SUCCESS == pChild->QueryIntAttribute(RUI_SUBATTR_LANGUAGE_RESID, &nResID))
					{
						LPCSTR lpszValue = pChild->GetText();
						if (lpszValue != NULL && strlen(lpszValue) != 0)
						{
							std::wstring strW;
							KStringHelper::Win32_UTF8_UNICODE(lpszValue, strW);
							m_CurCached[nResID] = strW.c_str();
						}
					}
					pChild = pChild->NextSiblingElement();
				}
			}
			fclose(pFile);
		}
	}
}

LPCWSTR	KMUIManager::GetString(UInt32 nResID, LPCWSTR strFile)
{
	assert(nResID >= 5000);

	if (!m_bLoaded)
	{
		m_bLoaded = true;
		while(true)
		{
			// Priority: User Lang > System > Default.
			if (m_nUserLangID == 0 ||
				m_AllStrings.find(m_nUserLangID) == m_AllStrings.end())
			{
				LANGID userlangID = GetUserDefaultUILanguage();
				if (m_AllStrings.find(userlangID) != m_AllStrings.end())
				{
					m_nActiveID = userlangID;
					break;
				}
				//MAKELANGID(PRIMARYLANGID(userDefaultLang), SUBLANG_DEFAULT); 
				
				LANGID syslangID = GetSystemDefaultUILanguage();
				if (m_AllStrings.find(syslangID) != m_AllStrings.end())
				{
					m_nActiveID = syslangID;
					break;
				}
				//MAKELANGID(PRIMARYLANGID(systemDefaultLang), SUBLANG_DEFAULT);

				m_nActiveID = m_nDefLangID;
				if (m_nActiveID == 0)
				{
					// If default is still not valid, use the first one.
					m_nActiveID = (*m_AllStrings.begin()).first;
				}
			}
			else
			{
				m_nActiveID = m_nUserLangID;
			}
			break;
		}
		LoadStringContent();
	}

	if (m_CurCached.find(nResID) != m_CurCached.end())
	{
		return m_CurCached[nResID].c_str();
	}
	else
	{
		return NULL;
	}
}

void KMUIManager::SetUserLangID(const UInt32 & nLangID)
{
	if (m_nUserLangID == nLangID)
		return ;

	m_nUserLangID = nLangID;
	m_bLoaded = false;
}

UInt32 KMUIManager::GetUserLangID() const
{
	return m_nUserLangID;
}

void KMUIManager::SetDefaultLangID(const UInt32 & nLangID)
{
	if (m_nDefLangID == nLangID)
		return ;

	m_nDefLangID = nLangID;
	m_bLoaded = false;
}

UInt32 KMUIManager::GetDefaultLangID() const
{
	return m_nDefLangID;
}

UInt32 KMUIManager::GetActiveLangID() const
{
	return m_nActiveID;
}

UInt32 KMUIManager::GetAllSupportedLangCount() const
{
	return (UInt32)m_AllStrings.size();
}

void KMUIManager::GetAllSupportedLangs(UInt32* pOut) const
{
	ALLLANGMAPS::const_iterator it = m_AllStrings.begin();
	for (; it != m_AllStrings.end(); it++)
	{
		*pOut++ = (*it).first;
	}
}

KDNAMEEND