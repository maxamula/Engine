#include "d3dtexture.h"

namespace Renderer
{
	D3DTexture::D3DTexture(TEXTURE_DESC& desc)
	{
		assert(d3ddev);
		if (desc.resource)
		{
			m_res = desc.resource;
		}
		else
		{
			D3D12_HEAP_PROPERTIES heapProp;
			ZeroMemory(&heapProp, sizeof(D3D12_HEAP_PROPERTIES));
			heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
			d3ddev->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, desc.resDesc, desc.initState, (desc.resDesc->Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL && desc.resDesc->Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET) ? desc.clearVal : NULL, IID_PPV_ARGS(&m_res));
		}

		m_srv = SRVHeap.Allocate();
		d3ddev->CreateShaderResourceView(m_res, desc.srvDesc, m_srv.CPU);
	}
	D3DTexture::D3DTexture(D3DTexture&& other)
	{
		assert(&other != this);
		m_res = MOVE(other.m_res);
		m_srv = MOVE(other.m_srv);
	}
	D3DTexture& D3DTexture::operator=(D3DTexture&& other)
	{
		assert(&other != this);
		m_res = MOVE(other.m_res);
		m_srv = MOVE(other.m_srv);
		return *this;
	}
	
	void D3DTexture::Release()
	{
		SRVHeap.Free(m_srv);
		m_res->Release();
	}
}