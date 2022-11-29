#include "d3dsurface.h"

namespace Renderer
{
	D3DSurface::D3DSurface(ID3D12Device8* device, IDXGIFactory7* pFactory, ID3D12CommandQueue* pCmdQueue, D3DDescriptorHeap* pRTVHeap, HWND hWnd, unsigned short width, unsigned short height)
		: m_hWnd(hWnd), m_width(width), m_height(height), m_pCmd(pCmdQueue), m_pFactory(pFactory), m_pRTVHeap(pRTVHeap), m_d3ddev(device)
	{
		assert(hWnd != NULL && hWnd != INVALID_HANDLE_VALUE);
		assert(pFactory && pCmdQueue);

		Release();
		DXGI_SWAP_CHAIN_DESC1 scd;
		scd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		scd.BufferCount = FRAMEBUFFERS_COUNT;
		scd.Flags = 0;
		scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.Height = height;
		scd.Width = width;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Scaling = DXGI_SCALING_STRETCH;
		scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		scd.Stereo = false;


		IDXGISwapChain1* pSwapChain;
		auto bebra = pFactory->CreateSwapChainForHwnd(m_pCmd, hWnd, &scd, NULL, NULL, &pSwapChain);
		pFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
		pSwapChain->QueryInterface(__uuidof(IDXGISwapChain4), (void**)&m_pSwap);
		pSwapChain->Release();
		m_backBufferIndex = m_pSwap->GetCurrentBackBufferIndex();
		for (unsigned int i = 0; i < FRAMEBUFFERS_COUNT; i++)
		{
			m_renderTargets[i].allocation = pRTVHeap->Allocate();
		}
		CreateRendertargetViews();
	}

	D3DSurface::~D3DSurface()
	{
		assert(m_pSwap == NULL);
	}

	void D3DSurface::Release()
	{
		for (int i = 0; i < FRAMEBUFFERS_COUNT; i++)
		{
			if (m_renderTargets[i].resource)
			{
				RELEASE(m_renderTargets[i].resource);
				m_pRTVHeap->Free(m_renderTargets[i].allocation);
				m_renderTargets->allocation = {};
			}
		}
		if (m_pSwap)
		{
			RELEASE(m_pSwap);
		}
	}

	void D3DSurface::CreateRendertargetViews()
	{
		for (unsigned int i = 0; i < FRAMEBUFFERS_COUNT; i++)
		{
			RENDER_TARGET& target = m_renderTargets[i];
			m_pSwap->GetBuffer(i, IID_PPV_ARGS(&target.resource));
			D3D12_RENDER_TARGET_VIEW_DESC rtvd{};
			rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			rtvd.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			m_d3ddev->CreateRenderTargetView(target.resource, &rtvd, target.allocation.CPU);
			m_renderTargets[i] = target;
		}
		DXGI_SWAP_CHAIN_DESC scd;
		m_pSwap->GetDesc(&scd);
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.Width = scd.BufferDesc.Width;
		m_viewport.Height = scd.BufferDesc.Width;
	}
}