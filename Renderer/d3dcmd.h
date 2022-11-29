#pragma once
#include "common.h"

namespace Renderer
{
	class D3DCommand
	{
	public:
		D3DCommand() = default;
		D3DCommand(const D3DCommand&) = delete;
		D3DCommand& operator=(const D3DCommand&) = delete;
		D3DCommand(D3DCommand&&) = delete;
		D3DCommand& operator=(D3DCommand&&) = delete;
		D3DCommand(ID3D12Device8* d3ddev, D3D12_COMMAND_LIST_TYPE type);

		void BeginFrame();
		void EndFrame();
		void Flush();
		void Release();
		inline ID3D12CommandQueue* CmdQueue() const { return m_cmdQueue; }
		inline ID3D12GraphicsCommandList6* CmdList() const { return m_cmdList; }
		inline uint8_t CurrentFrame() const { return m_iFrame; }

	private:
		void WaitGPU(HANDLE event, ID3D12Fence1* pFence);	// wait if gpu is busy while executing commands

		ID3D12CommandQueue* m_cmdQueue = NULL;
		ID3D12GraphicsCommandList6* m_cmdList = NULL;
		ID3D12CommandAllocator* m_cmdAlloc[FRAMEBUFFERS_COUNT];
		ID3D12Fence1* m_fence = NULL;
		HANDLE m_fenceEvent = NULL;
		uint64_t m_fenceValue = 0;
		uint8_t m_iFrame = 0;
	};
}