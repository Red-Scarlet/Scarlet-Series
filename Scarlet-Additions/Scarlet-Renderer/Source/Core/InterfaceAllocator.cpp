// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceAllocator.cpp 08/04/2021 - Interface Class.
#include "InterfaceAllocator.h"

#include "Core/CallbackTable.h"
#include "Components/AllocateComponent.h"
#include "Components/MemoryComponent.h"

#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"

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
				case ResourceType::RenderCommand:
				{
					RenderCommand* command = AnyCast<RenderCommand*>(component->Resource);
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						Ref<OpenGL::OpenGLCommand> glCommand = OpenGL::OpenGLCommand::Create();
						MemoryComponent mem = { glCommand };
						_Event.Push(new ComponentPushEvent(command->GetInterface()))->Bind<MemoryComponent>(mem);
						_Event.Proceed(_Event);
						command->m_Table = OpenGLAllocate(component->Type, glCommand);
					}
					break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
				}
				break;
				case ResourceType::Shader:
				{
					Shader* shader = AnyCast<Shader*>(component->Resource);
					switch (m_API)	
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						Ref<OpenGL::OpenGLShader> glShader = OpenGL::OpenGLShader::Create(shader->m_Name, shader->m_Source);
						MemoryComponent mem = { glShader };
						_Event.Push(new ComponentPushEvent(shader->GetInterface()))->Bind<MemoryComponent>(mem);
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
				}
				break;
				case ResourceType::VertexArray:
				{
					VertexArray* vertexArray = AnyCast<VertexArray*>(component->Resource);
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						Ref<OpenGL::OpenGLVertexArray> glArray = OpenGL::OpenGLVertexArray::Create();
						MemoryComponent mem = { glArray };
						_Event.Push(new ComponentPushEvent(vertexArray->GetInterface()))->Bind<MemoryComponent>(mem);
						_Event.Proceed(_Event);
						vertexArray->m_Table = OpenGLAllocate(component->Type, glArray);
					}
					break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
				}
				break;
				case ResourceType::VertexBuffer:
				{
					VertexBuffer* buffer = AnyCast<VertexBuffer*>(component->Resource);
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						float32* data = (float32*)buffer->m_Data;
						Ref<OpenGL::OpenGLVertexBuffer> glBuffer = OpenGL::OpenGLVertexBuffer::Create(data, buffer->m_Size);
						MemoryComponent mem = { glBuffer };
						_Event.Push(new ComponentPushEvent(buffer->GetInterface()))->Bind<MemoryComponent>(mem);
						_Event.Proceed(_Event);
						buffer->m_Table = OpenGLAllocate(component->Type, glBuffer);
					}
					break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
				}
				break;
				case ResourceType::IndexBuffer:
				{
					IndexBuffer* buffer = AnyCast<IndexBuffer*>(component->Resource);
					switch (m_API)
					{
					case RendererContext::API::None:
						break;
					case RendererContext::API::OpenGL:
					{
						uint32* data = (uint32*)buffer->m_Data;
						Ref<OpenGL::OpenGLIndexBuffer> glBuffer = OpenGL::OpenGLIndexBuffer::Create(data, buffer->m_Size, buffer->GetCount());
						MemoryComponent mem = { glBuffer };
						_Event.Push(new ComponentPushEvent(buffer->GetInterface()))->Bind<MemoryComponent>(mem);
						_Event.Proceed(_Event);
						buffer->m_Table = OpenGLAllocate(component->Type, glBuffer);
					}
					break;
					case RendererContext::API::Vulkan:
						break;
					case RendererContext::API::Dx12:
						break;
					default:
						break;
					}
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

				std::cout << "Allocated: " << i << std::endl;

				_Event.Push(new ComponentPopEvent(i))->Bind<AllocateComponent>();
			}
		}
	}

}