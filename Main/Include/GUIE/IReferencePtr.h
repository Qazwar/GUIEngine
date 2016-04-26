//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IReferencePtr.h
///	@brief		Declare the dynamic allocated/created object management.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_IREFERENCEPTR_H_INCLUDED__
#define KUDEET_IREFERENCEPTR_H_INCLUDED__

#pragma once

KDNAMESTART

//! Base class for all the dynamic allocated/created object
class IReferencePtr
{
public:
	IReferencePtr() : m_nRefCount(1)
	{
	}

	virtual ~IReferencePtr()
	{
	}

	void AddRef()	const
	{
		++m_nRefCount;
	}

	bool Drop()	const
	{
		assert(m_nRefCount > 0);
		--m_nRefCount;
		if (!m_nRefCount)
		{
#ifdef _DEBUG
			OutputDebugString(m_DebugName.c_str());
			OutputDebugString(L" Object Destroyed \r\n");
#endif ///
			delete this;
			return true;
		}
		return false;
	}

	SInt32 GetCount() const
	{
		return m_nRefCount;
	}

#ifdef _DEBUG
	void SetDebugName(LPWSTR lpszName)
	{
		m_DebugName = lpszName;
	}
#endif //

private:
	mutable SInt32	m_nRefCount;

#ifdef _DEBUG
	KString			m_DebugName;
#endif //
};

KDNAMEEND

#endif //KUDEET_IREFERENCEPTR_H_INCLUDED__

