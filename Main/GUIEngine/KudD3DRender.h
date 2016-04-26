//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudD3DRender.h
///	@brief		Header file for KD3DRender class, implements D3D render.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#ifndef KUDEET_D3D_RENDER_H_INCLUDED__
#define KUDEET_D3D_RENDER_H_INCLUDED__

#pragma once

#include "D3D9Types.h"
#include "D3D9.h"
#include "D3DX9.h"

KDNAMESTART

KDNAMEGUI

//Custom vertex format
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

/* Vertical:

    v0               v1
    |---------------|
    |\              |
    |  \            |
    |    \          |
    |      \        |
    |        \      |
    |          \    |
    |            \  |
    |              \|
    |---------------|
    v3               v2

    z = 0
    rhw = 1
*/

//Custom vertex
struct TLVERTEX
{
    float x;
    float y;
    float z;
    float rhw;
    D3DCOLOR colour;
    float u;
    float v;
};

class KD3DRender : public IGUIRender
{	
public:
	KD3DRender(void);
	virtual ~KD3DRender(void);

public:
	virtual void	StartRender(HWND hWnd);
	virtual void	EndRender();

	// Draw specific GUI elements.
	virtual void	RenderWindow(HDC hDC, const IGUIWindow * const pWindow);
	virtual void	RenderButton(const IGUIButton * const pButton);
	virtual void	RenderEdit(const IGUIEditBox * const pEdit);

	//! Redo initialize for render object when window size or buffer changed.
	virtual void	ReInitialRender();

private:
	HRESULT			Initialize();
	HRESULT			PostInitialize(FInt32 WindowWidth, FInt32 WindowHeight);

private:
	BOOL					m_bInit;
	// Main objects used for creating and rendering the 3D scene
	D3DPRESENT_PARAMETERS	m_d3dpp;			 // Parameters for CreateDevice/Reset
	HWND					m_hWnd;              // The main app window
	HWND					m_hWndFocus;         // The D3D focus window (usually same as m_hWnd)
	HMENU					m_hMenu;             // App menu bar (stored here when full screen)
	LPDIRECT3D9				m_pD3D;              // The main D3D object
	LPDIRECT3DDEVICE9		m_pD3DDevice;        // The D3D rendering device
	LPDIRECT3DVERTEXBUFFER9	m_pD3dVertexBuf;
	D3DCAPS9				m_d3dCaps;           // Caps for the device
	D3DSURFACE_DESC			m_d3dsdBackBuffer;   // Surface desc of the back buffer
	DWORD					m_dwCreateFlags;     // Indicate SW or HW vertex processing
	DWORD					m_dwWindowStyle;     // Saved window style for mode switches
	RECT					m_rcWindowBounds;    // Saved window bounds for mode switches
	RECT					m_rcWindowClient;    // Saved client area size for mode switches

	DWORD					m_dwCreationWidth;   // Width used to create window
	DWORD					m_dwCreationHeight;  // Height used to create window
};

KDNAMEGUIEND

KDNAMEEND

#endif //KUDEET_D3D_RENDER_H_INCLUDED__