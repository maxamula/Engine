#pragma once
#include "common.h"
#include "d3ddescheap.h"
#include "d3dcmd.h"
#include "window.h"

namespace Renderer 
{
	extern IDXGIFactory7* dxgiFactory;
	extern IDXGIAdapter4* dxgiAdapter;
	extern ID3D12Device8* d3ddev;
	extern D3DCommand d3dcmd;
	extern D3DDescriptorHeap RTVHeap;
	extern D3DDescriptorHeap DSVHeap;
	extern D3DDescriptorHeap SRVHeap;
	extern D3DDescriptorHeap UAVHeap;

	void Initialize();
	void Shutdown();
}