// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceRenderer.h"

#include <Events/InterfaceEvent.h>
#include "Components/RendererComponent.h"
#include "InterfaceAllocator.h"
#include "ResourceQueue.h"

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

			m_RenderCommand = new RenderCommand();

			String shaderSource = FileUtils::ReadFile("Assets/Shaders/FlatColor.glsl");
			m_Shader = new Shader("FlatColor", shaderSource);

			uint32 indices[] = { 0, 1, 2, 2, 3, 0 };
			m_IndexBuffer = new IndexBuffer(indices, sizeof(indices), 6);

			float32 vertices[] = {
			   0.0f, 0.0f, 0.0f,
			   0.5f, 0.0f, 0.0f,
			   0.5f, 0.5f, 0.0f,
			   0.0f, 0.5f, 0.0f
			};
			m_VertexBuffer = new VertexBuffer(vertices, sizeof(vertices));

			m_VertexArray = new VertexArray();

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
				case ResourceType::RenderCommand:
				{
					RenderCommand* renderCommand = AnyCast<RenderCommand*>(component.Resource);
					_Event.Push(new InterfaceRequestEvent(&renderCommand->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(renderCommand->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
				}
				break;
				case ResourceType::Shader:
				{
					Shader* shader = AnyCast<Shader*>(component.Resource);
					_Event.Push(new InterfaceRequestEvent(&shader->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(shader->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
				}
				break;
				case ResourceType::VertexArray:
				{
					VertexArray* vertexArray = AnyCast<VertexArray*>(component.Resource);
					_Event.Push(new InterfaceRequestEvent(&vertexArray->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(vertexArray->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
				}
				break;
				case ResourceType::VertexBuffer:
				{
					VertexBuffer* vertexBuffer = AnyCast<VertexBuffer*>(component.Resource);
					_Event.Push(new InterfaceRequestEvent(&vertexBuffer->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(vertexBuffer->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
				}
				break;
				case ResourceType::IndexBuffer:
				{
					IndexBuffer* indexBuffer = AnyCast<IndexBuffer*>(component.Resource);
					_Event.Push(new InterfaceRequestEvent(&indexBuffer->m_Interface));
					_Event.Proceed(_Event);
					_Event.Push(new ComponentPushEvent(indexBuffer->m_Interface))->Bind<AllocateComponent>(component);
					_Event.Proceed(_Event);
				}
				break;
				}
				queue->Pop();
			}

			{
				if (m_VertexBuffer->Ready() && m_VertexBufferSet == false) {
					BufferLayout layout = {
						{ VertexAttributeTypes::Float3, "a_Position" }
					};
					m_VertexBuffer->SetLayout(layout);
					m_VertexBufferSet = true;
				}

				if (m_VertexArray->Ready() && m_VertexBuffer->Ready() && m_IndexBuffer->Ready() && m_VertexArraySet == false)
				{
					m_VertexArray->AddVertexBuffer(*m_VertexBuffer, _Event);
					m_VertexArray->SetIndexBuffer(*m_IndexBuffer, _Event);
					m_VertexArraySet = true;
				}

				if (m_Shader->Ready())
					m_Shader->Bind();

				if (m_VertexArray->Ready())
					m_VertexArray->Bind();

				if (m_RenderCommand->Ready()) 
				{
					m_RenderCommand->SetClearColor(0.10f, 0.10f, 0.10f, 1.00f);
					m_RenderCommand->SetClearBuffer(RendererClearFlag::RendererColor | RendererClearFlag::RendererDepth);

					m_RenderCommand->DrawElements(_Event, RendererDrawingFlag::RendererTriangles, *m_VertexArray);
				}

			}
			
		}

		return true;
	}
}