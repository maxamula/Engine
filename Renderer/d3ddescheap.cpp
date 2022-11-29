#include "d3ddescheap.h"

namespace Renderer
{
	D3DDescriptorHeap::D3DDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, D3D12_DESCRIPTOR_HEAP_FLAGS flags, size_t capacity)
	{
		m_cap = capacity;
		m_heap = std::make_unique<DirectX::DescriptorHeap>(device, type, flags, capacity);
		m_available = boost::dynamic_bitset<unsigned int>(capacity);
		m_available.set();
		m_shaderVisible = flags == D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE ? true : false;
	}

	D3DDescriptorHeap::~D3DDescriptorHeap()
	{
		assert(m_heap.get() == NULL);
	}

	HEAP_ALLOCATION D3DDescriptorHeap::Allocate()
	{
		assert(m_size < m_cap);
		std::lock_guard<std::mutex> lock{ m_mutex };
		m_size++;
		size_t index = GetFreeIndex();
		m_available.set(index, false);
		return { index, m_heap->GetCpuHandle(index), m_shaderVisible ? m_heap->GetGpuHandle(index) : D3D12_GPU_DESCRIPTOR_HANDLE{} };
	}

	void D3DDescriptorHeap::Free(HEAP_ALLOCATION& allocation)
	{
		std::lock_guard<std::mutex> lock{ m_mutex };
		if (m_available[allocation.index] == false)
		{
			m_size--;
			m_available.set(allocation.index);
		}
	}

	size_t D3DDescriptorHeap::GetFreeIndex() const
	{
		for (size_t index = 0; index < m_cap; index++)
			if (m_available[index] == true)
				return index;
		return (size_t)(-1);
	}
}