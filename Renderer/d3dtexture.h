#pragma once
#include "common.h"
#include "core.h"

namespace Renderer
{
	struct TEXTURE_DESC
	{
		ID3D12Resource* resource;
		D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc;
		D3D12_RESOURCE_DESC* resDesc;
		D3D12_RESOURCE_STATES initState;
		D3D12_CLEAR_VALUE* clearVal;
	};

	class D3DTexture
	{
	public:
		D3DTexture() = default;
		D3DTexture(TEXTURE_DESC& desc);
		D3DTexture(D3DTexture&&);
		D3DTexture& operator=(D3DTexture&&);
		D3DTexture(const D3DTexture&) = delete;
		D3DTexture& operator=(const D3DTexture&) = delete;
		inline ID3D12Resource* Resource() const { return m_res; }
		void Release();
	private:

		ID3D12Resource* m_res;
		HEAP_ALLOCATION m_srv;
	};
}

