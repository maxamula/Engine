#pragma once
#include "common.h"
#include "d3ddescheap.h"

namespace Renderer
{
	struct RENDER_TARGET
	{
		ID3D12Resource* resource = NULL;
		HEAP_ALLOCATION allocation{};
	};

	class D3DSurface
	{
	public:
		D3DSurface() = default;
		D3DSurface(const D3DSurface&) = delete;
		D3DSurface& operator=(const D3DSurface&) = delete;
		D3DSurface(D3DSurface&&) = delete;
		D3DSurface& operator=(D3DSurface&&) = delete;
		D3DSurface(ID3D12Device8* device, IDXGIFactory7* pFactory, ID3D12CommandQueue* pCmdQueue, D3DDescriptorHeap* pRTVHeap, HWND hWnd, unsigned short width, unsigned short height);
		~D3DSurface();

		inline void Present()
		{
			m_pSwap->Present(1, 0);
			m_backBufferIndex = m_pSwap->GetCurrentBackBufferIndex();
		}

		inline D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle(unsigned int index)
		{
			assert(index < FRAMEBUFFERS_COUNT);
			return m_renderTargets[index].allocation.CPU;
		}

		//TODO: add resizing
		void Release();

	private:
		void CreateRendertargetViews();

		ID3D12Device8* m_d3ddev = NULL;
		D3DDescriptorHeap* m_pRTVHeap = NULL;
		IDXGIFactory7* m_pFactory = NULL;
		ID3D12CommandQueue* m_pCmd = NULL;

		IDXGISwapChain4* m_pSwap = NULL;
		D3D12_VIEWPORT m_viewport{};
		RENDER_TARGET m_renderTargets[FRAMEBUFFERS_COUNT]{};
		byte m_backBufferIndex = 0;

		HWND m_hWnd = NULL;
		unsigned short m_width = 0;
		unsigned short m_height = 0;
	};
}