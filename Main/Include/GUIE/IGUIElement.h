//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		IGUIElement.h
///	@brief		Declare the kudeet GUI element basic functions.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_GUI_IGUIELEMENT_H_INCLUDED__
#define KUDEET_GUI_IGUIELEMENT_H_INCLUDED__

#pragma once

KDNAMESTART

KDNAMEGUI

// forward delcare
class IGUIWindow;

//! Base class for all the element in GUI system
class IGUIElement : public IReferencePtr, public IEventHandler
{
public:
	IGUIElement(KDE_ELEMENT_TYPE type, IGUIElement* parent, UInt32 ctrlID)
	{
		m_eType			= type;
		m_pParent		= parent;
		m_pWindow		= NULL;
		m_CtrlID		= ctrlID;
		m_bIsEnable		= true;
		m_bIsVisible	= true;
		m_bIsTabStop	= true;
		m_bIsFocusable	= false;		
		m_bIsFocused	= false;
		m_nWidth		= 0;
		m_nHeight		= 0;
		m_nLeft			= 0;
		m_nRight		= 0;
		m_nBottom		= 0;
		m_nTop			= 0;
		m_nMinWidth		= 0;
		m_nMinHeight	= 0;
		m_nMaxWidth		= 0;
		m_nMaxHeight	= 0;
		m_nTabOrder		= 0;

		m_Name.clear();
		m_Text.clear();
		m_Children.clear();		
	}

	//! Destructor
	virtual ~IGUIElement()
	{
		std::vector<IGUIElement*>::iterator it = m_Children.begin();
		std::vector<IGUIElement*>::iterator itend = m_Children.end();
		for (; it != itend; ++it)
		{
			(*it)->Drop();
		}
	}

public:
	void	SetWindow		(IGUIWindow*	pWindow)		{ m_pWindow		= pWindow;	}
	void	SetElementType	(KDE_ELEMENT_TYPE value)		{ m_eType		= value;	}
	void	SetParent		(IGUIElement *	pValue)			{ m_pParent		= pValue;	}
	void	SetElementName	(LPCWSTR		value)			{ m_Name		= value;	}
	void	SetElementText	(LPCWSTR		value)			{ m_Text		= value;	}
	void	SetIsEnable		(bool value)					{ m_bIsEnable	= value;	}
	void	SetIsVisible	(bool value)					{ m_bIsVisible	= value;	}
	void	SetIsTabStop	(bool value)					{ m_bIsTabStop	= value;	}
	void	SetIsFocused	(bool value)					{ m_bIsFocused	= value;	}
	void	SetIsFocusable	(bool value)					{ m_bIsFocusable= value;	}
	void	SetMargin		(const KRect & value)			{ m_RCMargin	= value;	}
	void	SetLeft			(SInt32   value)				{ m_nLeft		= value;	}
	void	SetRight		(SInt32   value)				{ m_nRight		= value;	}
	void	SetWidth		(UInt32	  value)				{ m_nWidth		= value;	}
	void	SetHeight		(UInt32   value)				{ m_nHeight		= value;	}
	void	SetBottom		(SInt32   value)				{ m_nBottom		= value;	}
	void	SetTop			(SInt32   value)				{ m_nTop		= value;	}
	void	SetMinWidth		(UInt32   value)				{ m_nMinWidth	= value;	}
	void	SetMinHeight	(UInt32   value)				{ m_nMinHeight	= value;	}
	void	SetMaxWidth		(UInt32   value)				{ m_nMaxWidth	= value;	}
	void	SetMaxHeight	(UInt32   value)				{ m_nMaxHeight	= value;	}
	void	SetCtrlID		(UInt32   value)				{ m_CtrlID		= value;	}
	void	SetTabOrder		(UInt32   value)				{ m_nTabOrder	= value;	}

	IGUIWindow *			Window()			const		{ return m_pWindow;			}
	IGUIElement	*			Parent()			const		{ return m_pParent;			}
	KDE_ELEMENT_TYPE		ElementType()		const		{ return m_eType;			}
	LPCWSTR					ElementName()		const		{ return m_Name.c_str();	}
	LPCWSTR					ElementText()		const		{ return m_Text.c_str();	}
	KRect					ElementRect()		const		{ return m_RCClient;		}
	KRect					Margin()			const		{ return m_RCMargin;		}
	bool					IsTabStop()			const		{ return m_bIsTabStop;		}
	bool					IsFocused()			const		{ return m_bIsFocused;		}
	bool					IsVisible()			const		{ return m_bIsVisible;		}
	bool					IsEnable()			const		{ return m_bIsEnable;		}
	bool					IsFocusable()		const		{ return m_bIsFocusable;	}
	SInt32					Left()				const		{ return m_nLeft;			}
	SInt32					Right()				const		{ return m_nRight;			}
	SInt32					Bottom()			const		{ return m_nBottom;			}
	SInt32					Top()				const		{ return m_nTop;			}
	UInt32					Height()			const		{ return m_nHeight;			}
	UInt32					Width()				const		{ return m_nWidth;			}
	UInt32					MinWidth()			const		{ return m_nMinWidth;		}
	UInt32					MinHeight()			const		{ return m_nMinHeight;		}
	UInt32					MaxWidth()			const		{ return m_nMaxWidth;		}
	UInt32					MaxHeight()			const		{ return m_nMaxHeight;		}
	SInt32					TabOrder()			const		{ return m_nTabOrder;		}
	UInt32					CtrlID()			const		{ return m_CtrlID;			}
	IGUIElement*			GetChild(SInt32 nIndex)			{ return m_Children[nIndex];}
	UInt32					GetChildCount()		const		{ return (SInt32)m_Children.size();	}

public:

	bool IsLayout()
	{
		return (m_eType == EET_LAYOUT_STACKPANEL || 
			m_eType == EET_LAYOUT_DOCKPANEL || 
			m_eType == EET_LAYOUT_BASICPANEL);
	}

	void SetElementRect(const KRect & value)
	{
		m_RCClient	= value;
		m_nLeft		= value.left;
		m_nRight	= value.right;
		m_nTop		= value.top;
		m_nBottom	= value.bottom;
		m_nWidth	= value.Width();
		m_nHeight	= value.Height();
	}

	virtual bool AddChildElement(IGUIElement * pElement)
	{
		if (pElement == NULL)
			return false;

		pElement->SetParent(this);
		m_Children.push_back(pElement);

		return true;
	}

	//! Draws the element and its children.
	virtual void Draw(HDC hDC, RECT rcPaint)
	{
		if (!m_bIsVisible)
			return;

		SInt32 nSize = (SInt32)m_Children.size();

		std::vector<IGUIElement*>::iterator it = m_Children.begin();
		std::vector<IGUIElement*>::iterator itend = m_Children.end();
		for (; it != itend; ++it)
		{
			(*it)->Draw(hDC, rcPaint);
		}
	}

	IGUIElement* HitTest(const KPoint& point)
	{
		IGUIElement* target = 0;
		std::vector<IGUIElement*>::reverse_iterator it = m_Children.rbegin();
		if (IsVisible())
		{
			while(it != m_Children.rend())
			{
				target = (*it)->HitTest(point);
				if (target)
					return target;
				++it;
			}
		}

		if (IsVisible() && !IsLayout())
		{
			KRect rc = this->ElementRect();
			if (rc.PtInRect(point))
				target = this;
		}

		return target;
	}

	virtual bool OnEvent(const KDS_EVENT& event, UInt32 dwMsgMapID = 0)
	{
		if (NULL != m_pParent)
			return m_pParent->OnEvent(event);
		return true;
	}

	//! Update this correct element position.
	/*! In some case we might set different position value with
		different property, but these values might be conflict.
		Then we need to update these element position to correct
		value with predefined priority.	*/
	virtual void UpdateElementLayout()
	{
		m_RCClient.left		= Left();
		m_RCClient.top		= Top();
		m_RCClient.bottom	= Top() + Height();
		m_RCClient.right	= Left() + Width();

		FinishUpdateLayout();

		std::vector<IGUIElement*>::iterator it = m_Children.begin();
		while (it != m_Children.end())
		{
			(*it)->UpdateElementLayout();
			++it;
		}		
	}

	virtual void FinishUpdateLayout() { }

protected:
	KDE_ELEMENT_TYPE	m_eType;
	KString				m_Name;
	KString				m_Text;
	KRect				m_RCClient;
	KRect				m_RCMargin;

	bool				m_bIsTabStop;
	bool				m_bIsFocused;
	bool				m_bIsVisible;
	bool				m_bIsEnable;
	bool				m_bIsFocusable;

	SInt32				m_nTabOrder;

	UInt32				m_nWidth;
	UInt32				m_nHeight;
	SInt32				m_nLeft;
	SInt32				m_nRight;
	SInt32				m_nBottom;
	SInt32				m_nTop;
	UInt32				m_nMinWidth;
	UInt32				m_nMinHeight;
	UInt32				m_nMaxWidth;
	UInt32				m_nMaxHeight;
	UInt32				m_CtrlID;

	//! List of all children of this element.
	std::vector<IGUIElement*>	m_Children;
	IGUIElement *				m_pParent;
	IGUIWindow *				m_pWindow;
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_GUI_IGUIELEMENT_H_INCLUDED__