// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceRenderer.h"

#include <Events/InterfaceEvent.h>
#include "Components/RendererComponent.h"
#include "InterfaceAllocator.h"
#include "ResourceQueue.h"

#include "Graphics/Shader.h"

namespace Renderer {

	void InterfaceRenderer::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<RendererComponent>();
			_Event.Proceed(_Event);

			_Event.Push(new ComponentPushEvent(this))->Bind<RendererComponent>(RendererContext::API::OpenGL);
			_Event.Push(new InterfacePushEvent(this))->Bind(new InterfaceAllocator());
			_Event.Proceed(_Event);

			String shaderSource = FileUtils::ReadFile("Assets/Shaders/FlatColor.glsl");
			m_Shader = CreateRef<Shader>("FlatColor", shaderSource);

			m_Initialized = true, m_Running = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceRenderer::OnAppUpdate));
	}

	bool InterfaceRenderer::OnAppUpdate(AppUpdateEvent& _Event)
	{
		if (m_Running)
		{
			ResourceQueue* queue = ResourceQueue::GetInstance();

			while (!queue->Empty())
			{
				AllocateComponent& component = queue->Back();
				
				switch (component.Type)
				{
				case ResourceType::Shader:
					Shader* shader = AnyCast<Shader*>(component.Data);
					_Event.Push(new InterfaceRequestEvent(&shader->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(shader->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
					break;
				}

				queue->Pop();
			}

			if(m_Shader->m_Interface != uint64_max) 
				m_Shader->Bind();
		}

		return true;
	}
}