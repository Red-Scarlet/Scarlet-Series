#pragma once

#include <ScarletInterface.h>
#include "Components/AllocateComponent.h"

namespace Renderer {

	using namespace ScarletInterface;
	
	class SCARLET_INTERFACE_API ResourceQueue
	{
	protected:
		ResourceQueue();
		~ResourceQueue();

	public:
		ResourceQueue(ResourceQueue& _Other) = delete;
		void operator=(const ResourceQueue&) = delete;
		static ResourceQueue* GetInstance();

		AllocateComponent& Back();
		void Push(const AllocateComponent& _Component);
		void Pop();
		bool Empty() { return m_Queue.empty(); }

	private:
		static ResourceQueue* s_Instance;
		static std::mutex s_QueueMutex;

		// inbound  (i) -- (TO ALLOCATE)
		// outbound (o) -- (REQUEST MEM)

		Vector<AllocateComponent> m_Queue;
	};

}