// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceAllocator.cpp 08/04/2021 - Interface Class.
#include "InterfaceAllocator.h"

#include "Core/CallbackTable.h"
#include "Components/AllocateComponent.h"
#include "Components/MemoryComponent.h"

#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include <Events/InterfaceEvent.h>
#include <ScarletOpenGL.h>

#include "Allocator/OpenGLAllocate.h"

namespace Renderer {

	void InterfaceAllocator::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<RendererComponent>();
			_Event.Proceed(_Event);
			{
				RendererComponent* component = {};
				_Event.Push(new ComponentComputeEvent((Interface)2))->Retrieve<RendererComponent>(&component);
				_Event.Proceed(_Event);

				if(component) m_API = component->Context->GetAPI();
			}
			_Event.Push(new SignaturePopEvent(this))->Bind<RendererComponent>();
			_Event.Proceed(_Event);
			_Event.Push(new SignaturePushEvent(this))->Bind<AllocateComponent>();
			_Event.Proceed(_Event);

			m_Initialized = true, m_Running = true;
		}

		if (m_Running)
		{
			for (const Interface& i : m_Set)
			{
				if (i == m_Interface) return;

				AllocateComponent* component = {};
				_Event.Push(new ComponentComputeEvent(i))->Retrieve<AllocateComponent>(&component);
				_Event.Proceed(_Event);

				if (!component) return;

				switch (component->Type)
				{
				case ResourceType::None:
					break;
				case ResourceType::Shader:
				{
					Shader* shader = AnyCast<Shader*>(component->Data);
					switch (m_API)	
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						Ref<OpenGL::OpenGLShader> glShader = OpenGL::OpenGLShader::Create(shader->m_Name, shader->m_Source);
						MemoryComponent mem = { glShader };
						_Event.Push(new ComponentPushEvent(this))->Bind<MemoryComponent>(mem);
						_Event.Proceed(_Event);
						shader->m_Table = OpenGLAllocate(component->Type, glShader);
					}
					break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				}
				case ResourceType::VertexArray:
				//{
				//	VertexArray* vertexArray = AnyCast<VertexArray*>(component->Data);
				//	switch (m_API)
				//	{
				//	case RendererContext::API::None:
				//		break;
				//	case RendererContext::API::OpenGL:
				//	{
				//		Ref<OpenGL::OpenGLVertexArray> glVertexArray = OpenGL::OpenGLVertexArray::Create();
				//		MemoryComponent mem = { glVertexArray };
				//		_Event.Push(new ComponentPushEvent(this))->Bind<MemoryComponent>(mem);
				//		_Event.Proceed(_Event);
				//
				//		CallbackTable callbackTable = {};
				//		{
				//			auto AddVertexBuffer = std::bind(&OpenGL::OpenGLVertexArray::AddVertexBuffer, glVertexArray, std::placeholders::_1);
				//			CallbackWrapper wrapperAddVertexBuffer; wrapperAddVertexBuffer.Bind<decltype(AddVertexBuffer), Ref<OpenGL::OpenGLVertexBuffer>>(AddVertexBuffer);
				//			callbackTable.Push("AddVertexBuffer", wrapperAddVertexBuffer);
				//
				//			auto SetIndexBuffer = std::bind(&OpenGL::OpenGLVertexArray::SetIndexBuffer, glVertexArray, std::placeholders::_1);
				//			CallbackWrapper wrapperSetIndexBuffer; wrapperSetIndexBuffer.Bind<decltype(SetIndexBuffer), Ref<OpenGL::OpenGLIndexBuffer>>(SetIndexBuffer);
				//			callbackTable.Push("SetIndexBuffer", wrapperSetIndexBuffer);
				//
				//			auto Bind = std::bind(&OpenGL::OpenGLVertexArray::Bind, glVertexArray);
				//			CallbackWrapper wrapperBind; wrapperBind.Bind<decltype(Bind)>(Bind);
				//			callbackTable.Push("Bind", wrapperBind);
				//
				//			auto Unbind = std::bind(&OpenGL::OpenGLVertexArray::Unbind, glVertexArray);
				//			CallbackWrapper wrapperUnbind; wrapperUnbind.Bind<decltype(Unbind)>(Unbind);
				//			callbackTable.Push("Unbind", wrapperUnbind);
				//		}
				//
				//		vertexArray->m_Table = std::move(callbackTable);
				//	}
				//	break;
				//	case RendererContext::API::Vulkan:
				//		break;
				//	case RendererContext::API::Dx12:
				//		break;
				//	default:
				//		break;
				//	}
				//	break;
				//}
				case ResourceType::VertexBuffer:
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
						break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				case ResourceType::IndexBuffer:
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
						break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				case ResourceType::TextureBuffer:
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
						break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				case ResourceType::UniformBuffer:
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
						break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				case ResourceType::FrameBuffer:
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
						break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
					break;
				}

				_Event.Push(new ComponentPopEvent(i))->Bind<AllocateComponent>();
			}
		}
	}

}