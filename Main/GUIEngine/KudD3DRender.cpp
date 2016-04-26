//////////////////////////////////////////////////////////////////////////
///
///		Copyright (C) 2010 Kudeet. All rights reserved.
///
///	This file is part of the "Kudeet GUI" library.
///	For conditions of distribution, see copyright notice in license.txt
///
///	@file		KudD3DRender.cpp
///	@brief		Implements KD3DRender methods to support Direct3D render.
///	@version	0.1
///	@author		Yiling Lai
///	@date		Jan. 2010
///
///	Changed History:
//////////////////////////////////////////////////////////////////////////

#include "BaseDefines.h"
#include <windowsx.h>
#include <basetsd.h>
#include <mmsystem.h>
#include <stdio.h>
#include <tchar.h>

#include "IGUIRender.h"
#include "KudD3DRender.h"

KDNAMESTART

KDNAMEGUI

KD3DRender::KD3DRender(void) :
	m_bInit(FALSE)
{
}

KD3DRender::~KD3DRender(void)
{
}

void KD3DRender::StartRender(HWND hWnd)
{
	m_hWnd = hWnd;
	Initialize();
	
	if (NULL == m_pD3DDevice)
		return;

	// Clear the back buffer to a blue color
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(127, 185, 207), 1.0f, 0 );

	// Begin the scene
	m_pD3DDevice->BeginScene();
}

void KD3DRender::ReInitialRender()
{
}

void KD3DRender::EndRender()
{
	// End the scene
	m_pD3DDevice->EndScene();

	// Present the back buffer contents to the display
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

HRESULT KD3DRender::Initialize()
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Get the current desktop display mode
	D3DDISPLAYMODE D3DDM;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DDM)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.
	D3DPRESENT_PARAMETERS D3DParam; 
	ZeroMemory(&D3DParam, sizeof(D3DParam));
	D3DParam.Windowed = TRUE;
	D3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DParam.BackBufferFormat = D3DDM.Format;		// D3DFMT_A8R8G8B8

	// Create the Direct3D device. Here we are using the default adapter (most
	// systems only have one, unless they have multiple graphics hardware cards
	// installed) and requesting the HAL (which is saying we want the hardware
	// device rather than a software one). Software vertex processing is 
	// specified since we know it will work on all cards. On cards that support 
	// hardware vertex processing, though, we would see a big performance gain 
	// by specifying hardware vertex processing.
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&D3DParam,
		&m_pD3DDevice)))
	{
		return E_FAIL;
	}

	// Set vertex shader
	m_pD3DDevice->SetVertexShader(NULL);
	m_pD3DDevice->SetFVF(D3DFVF_TLVERTEX);

	// Create vertex buffer and set as stream source
	//m_pD3DDevice->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL, D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &m_pD3dVertexBuf, 0);
	//m_pD3DDevice->SetStreamSource (0, m_pD3dVertexBuf, 0, sizeof(TLVERTEX));

	// Setup rendering states
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Part three, set the render flags.
	m_pD3DDevice->SetRenderState ( D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState ( D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState ( D3DRS_ZENABLE, FALSE);

	// Set diffuse blending for alpha set in vertices.
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,  D3DTOP_SELECTARG1);

	RECT rc = { 0 };
	GetWindowRect(m_hWnd, &rc);

	PostInitialize((FInt32)rc.right - rc.left, (FInt32)rc.bottom - rc.top);

	return S_OK;
}

HRESULT KD3DRender::PostInitialize(FInt32 WindowWidth, FInt32 WindowHeight)
{
	D3DXMATRIX Ortho2D, Identity;

	D3DXMatrixOrthoLH(&Ortho2D, WindowWidth, WindowHeight, 0.0f, 1.0f);
	D3DXMatrixIdentity(&Identity);

	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &Identity);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &Identity);

	return S_OK;
}

void KD3DRender::RenderWindow(HDC hDC, const IGUIWindow * const pWindow)
{
}

void KD3DRender::RenderButton(const IGUIButton * const pButton)
{
}

void KD3DRender::RenderEdit(const IGUIEditBox * const pEdit)
{
}

KDNAMEGUIEND

KDNAMEEND