#include "ResourceQueue.h"

namespace Renderer {

	ResourceQueue* ResourceQueue::s_Instance = nullptr;
	std::mutex ResourceQueue::s_QueueMutex;

	ResourceQueue::ResourceQueue()
	{
	}

	ResourceQueue::~ResourceQueue()
	{
	}

	ResourceQueue* ResourceQueue::GetInstance()
	{
		std::lock_guard<std::mutex> lock(s_QueueMutex);
		if (s_Instance == nullptr)
			s_Instance = new ResourceQueue();
		return s_Instance;
	}

	AllocateComponent& ResourceQueue::Back()
	{
		return m_Queue.back();
	}

	void ResourceQueue::Push(const AllocateComponent& _Component)
	{
		m_Queue.push_back(_Component);
	}

	void ResourceQueue::Pop()
	{
		m_Queue.pop_back();
	}

}