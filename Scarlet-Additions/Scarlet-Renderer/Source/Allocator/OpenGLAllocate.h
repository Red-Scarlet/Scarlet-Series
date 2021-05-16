#pragma once

#include "Core/CallbackTable.h"
#include "Components/AllocateComponent.h"
#include "Components/MemoryComponent.h"

#include "Graphics/BufferLayout.h"

#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"

#include <Events/InterfaceEvent.h>
#include <ScarletInterface.h>
#include <ScarletOpenGL.h>

namespace Renderer {

	static OpenGL::OpenGLVertexAttributeTypes OpenGLFromRendererType(const VertexAttributeTypes& _Type)
	{
		switch (_Type)
		{
			case VertexAttributeTypes::Float:		return OpenGL::OpenGLVertexAttributeTypes::Float;
			case VertexAttributeTypes::Float2:		return OpenGL::OpenGLVertexAttributeTypes::Float2;
			case VertexAttributeTypes::Float3:		return OpenGL::OpenGLVertexAttributeTypes::Float3;
			case VertexAttributeTypes::Float4:		return OpenGL::OpenGLVertexAttributeTypes::Float4;
			case VertexAttributeTypes::Mat3:		return OpenGL::OpenGLVertexAttributeTypes::Mat3;
			case VertexAttributeTypes::Mat4:		return OpenGL::OpenGLVertexAttributeTypes::Mat4;
			case VertexAttributeTypes::Int:			return OpenGL::OpenGLVertexAttributeTypes::Int;
			case VertexAttributeTypes::Int2:		return OpenGL::OpenGLVertexAttributeTypes::Int2;
			case VertexAttributeTypes::Int3:		return OpenGL::OpenGLVertexAttributeTypes::Int3;
			case VertexAttributeTypes::Int4:		return OpenGL::OpenGLVertexAttributeTypes::Int4;
			case VertexAttributeTypes::Bool:		return OpenGL::OpenGLVertexAttributeTypes::Bool;
		}

		return OpenGL::OpenGLVertexAttributeTypes::None;
	}

	static OpenGL::OpenGLEnableFlag OpenGLEnableFromRendererType(const RendererEnableFlag& _Type)
	{
		OpenGL::OpenGLEnableFlag Flag = OpenGL::OpenGLEnableFlag::OpenGLNone;

		if ((uint8)_Type & (uint8)RendererEnableFlag::RendererBlend)
			Flag |= OpenGL::OpenGLEnableFlag::OpenGLBlend;
		if ((uint8)_Type & (uint8)RendererEnableFlag::RendererDepthTest)
			Flag |= OpenGL::OpenGLEnableFlag::OpenGLDepthTest;

		return Flag;
	}

	static OpenGL::OpenGLClearFlag OpenGLClearFromRendererType(const RendererClearFlag& _Type)
	{
		OpenGL::OpenGLClearFlag Flag = OpenGL::OpenGLClearFlag::OpenGLNone;

		if((uint8)_Type & (uint8)RendererClearFlag::RendererColor)
			Flag |= OpenGL::OpenGLClearFlag::OpenGLColor;
		if ((uint8)_Type & (uint8)RendererClearFlag::RendererDepth)
			Flag |= OpenGL::OpenGLClearFlag::OpenGLDepth;
		if ((uint8)_Type & (uint8)RendererClearFlag::RendererStencil)
			Flag |= OpenGL::OpenGLClearFlag::OpenGLStencil;

		return Flag;
	}

	static OpenGL::OpenGLPolygonFlag OpenGLPolygonFromRendererType(const RendererPolygonFlag& _Type)
	{
		OpenGL::OpenGLPolygonFlag Flag = OpenGL::OpenGLPolygonFlag::OpenGLNone;

		if ((uint8)_Type & (uint8)RendererPolygonFlag::RendererPoint)
			Flag |= OpenGL::OpenGLPolygonFlag::OpenGLPoint;
		if ((uint8)_Type & (uint8)RendererPolygonFlag::RendererLine)
			Flag |= OpenGL::OpenGLPolygonFlag::OpenGLLine;
		if ((uint8)_Type & (uint8)RendererPolygonFlag::RendererFill)
			Flag |= OpenGL::OpenGLPolygonFlag::OpenGLFill;

		return Flag;
	}

	static OpenGL::OpenGLDrawingFlag OpenGLDrawingFromRendererType(const RendererDrawingFlag& _Type)
	{
		OpenGL::OpenGLDrawingFlag Flag = OpenGL::OpenGLDrawingFlag::OpenGLNone;

		if ((uint8)_Type & (uint8)RendererDrawingFlag::RendererPoints)
			Flag |= OpenGL::OpenGLDrawingFlag::OpenGLPoints;
		if ((uint8)_Type & (uint8)RendererDrawingFlag::RendererLines)
			Flag |= OpenGL::OpenGLDrawingFlag::OpenGLLines;
		if ((uint8)_Type & (uint8)RendererDrawingFlag::RendererTriangles)
			Flag |= OpenGL::OpenGLDrawingFlag::OpenGLTriangles;

		return Flag;
	}

	static CallbackTable OpenGLAllocate(const ResourceType& _Type, const AnyData& _Data)
	{
		switch (_Type)
		{
		case ResourceType::RenderCommand: 
		{			
			Ref<OpenGL::OpenGLCommand> glCommand = AnyCast<Ref<OpenGL::OpenGLCommand>>(_Data);
			CallbackTable callbackTable = {};
			{
				Function<void(const RendererEnableFlag& _Flag)> _Enable = [glCommand](const RendererEnableFlag& _Flag) {

					OpenGL::OpenGLEnableFlag flag = OpenGLEnableFromRendererType(_Flag);
					auto run = std::bind(&OpenGL::OpenGLCommand::Enable, glCommand, flag);
					run();
				};

				Function<void(const RendererEnableFlag& _Flag)> _Disable = [glCommand](const RendererEnableFlag& _Flag) {

					OpenGL::OpenGLEnableFlag flag = OpenGLEnableFromRendererType(_Flag);
					auto run = std::bind(&OpenGL::OpenGLCommand::Disable, glCommand, flag);
					run();
				};

				Function<void(const RendererClearFlag& _Flag)> _SetClearBuffer = [glCommand](const RendererClearFlag& _Flag) {

					OpenGL::OpenGLClearFlag flag = OpenGLClearFromRendererType(_Flag);
					auto run = std::bind(&OpenGL::OpenGLCommand::SetClearBuffer, glCommand, flag);
					run();
				};

				Function<void(const RendererPolygonFlag& _Flag)> _SetPolygonMode = [glCommand](const RendererPolygonFlag& _Flag) {

					OpenGL::OpenGLPolygonFlag flag = OpenGLPolygonFromRendererType(_Flag);
					auto run = std::bind(&OpenGL::OpenGLCommand::SetPolygonMode, glCommand, flag);
					run();
				};

				Function<void(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount)> _DrawArrays = [glCommand](Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount) {
					Interface interface = _VertexArray.GetInterface();

					MemoryComponent* component = {};
					_Event.Push(new ComponentComputeEvent(interface))->Retrieve<MemoryComponent>(&component);
					_Event.Proceed(_Event);
					
					OpenGL::OpenGLDrawingFlag flag = OpenGLDrawingFromRendererType(_Flag);
					
					Ref<OpenGL::OpenGLVertexArray> glArray = AnyCast<Ref<OpenGL::OpenGLVertexArray>>(component->Data);
					auto run = std::bind(&OpenGL::OpenGLCommand::DrawArrays, glCommand, flag, glArray, _IndexCount);
					run();
				};

				Function<void(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount)> _DrawElements = [glCommand](Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount) {
					Interface interface = _VertexArray.GetInterface();

					MemoryComponent* component = {};
					_Event.Push(new ComponentComputeEvent(interface))->Retrieve<MemoryComponent>(&component);
					_Event.Proceed(_Event);
					
					OpenGL::OpenGLDrawingFlag flag = OpenGLDrawingFromRendererType(_Flag);
					
					Ref<OpenGL::OpenGLVertexArray> glArray = AnyCast<Ref<OpenGL::OpenGLVertexArray>>(component->Data);
					auto run = std::bind(&OpenGL::OpenGLCommand::DrawElements, glCommand, flag, glArray, _IndexCount);
					run();
				};

				auto Enable = std::bind(_Enable, std::placeholders::_1);
				CallbackWrapper wrapperEnable; wrapperEnable.Bind<decltype(Enable), const RendererEnableFlag&>(Enable);
				callbackTable.Push("Enable", wrapperEnable);

				auto Disable = std::bind(_Disable, std::placeholders::_1);
				CallbackWrapper wrapperDisable; wrapperDisable.Bind<decltype(Disable), const RendererEnableFlag&>(Disable);
				callbackTable.Push("Disable", wrapperDisable);

				auto SetViewport = std::bind(&OpenGL::OpenGLCommand::SetViewport, glCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
				CallbackWrapper wrapperSetViewport; wrapperSetViewport.Bind<decltype(SetViewport), const uint32&, const uint32&, const uint32&, const uint32&>(SetViewport);
				callbackTable.Push("SetViewport", wrapperSetViewport);

				auto SetClearColor = std::bind(&OpenGL::OpenGLCommand::SetClearColor, glCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
				CallbackWrapper wrapperSetClearColor; wrapperSetClearColor.Bind<decltype(SetClearColor), const float32&, const float32&, const float32&, const float32&>(SetClearColor);
				callbackTable.Push("SetClearColor", wrapperSetClearColor);

				auto SetClearBuffer = std::bind(_SetClearBuffer, std::placeholders::_1);
				CallbackWrapper wrapperSetClearBuffer; wrapperSetClearBuffer.Bind<decltype(SetClearBuffer), const RendererClearFlag&>(SetClearBuffer);
				callbackTable.Push("SetClearBuffer", wrapperSetClearBuffer);
				
				auto SetPolygonMode = std::bind(_SetPolygonMode, std::placeholders::_1);
				CallbackWrapper wrapperSetPolygonMode; wrapperSetPolygonMode.Bind<decltype(SetPolygonMode), const RendererPolygonFlag&>(SetPolygonMode);
				callbackTable.Push("SetPolygonMode", wrapperSetPolygonMode);

				auto DrawArrays = std::bind(_DrawArrays, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
				CallbackWrapper wrapperDrawArrays; wrapperDrawArrays.Bind<decltype(DrawArrays), Event&, const RendererDrawingFlag&, const VertexArray&, const uint32&>(DrawArrays);
				callbackTable.Push("DrawArrays", wrapperDrawArrays);

				auto DrawElements = std::bind(_DrawElements, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
				CallbackWrapper wrapperDrawElements; wrapperDrawElements.Bind<decltype(DrawElements), Event&, const RendererDrawingFlag&, const VertexArray&, const uint32&>(DrawElements);
				callbackTable.Push("DrawElements", wrapperDrawElements);
			}
			return callbackTable;
		}
		break;
		case ResourceType::Shader:
		{
			Ref<OpenGL::OpenGLShader> glShader = AnyCast<Ref<OpenGL::OpenGLShader>>(_Data);
			CallbackTable callbackTable = {};
			{
				auto SetInt = std::bind(&OpenGL::OpenGLShader::SetInt, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetInt; wrapperSetInt.Bind<decltype(SetInt), String, uint32>(SetInt);
				callbackTable.Push("SetInt", wrapperSetInt);

				auto SetFloat = std::bind(&OpenGL::OpenGLShader::SetFloat, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetFloat; wrapperSetFloat.Bind<decltype(SetFloat), String, float32>(SetFloat);
				callbackTable.Push("SetFloat1", wrapperSetFloat);

				auto SetFloat2 = std::bind(&OpenGL::OpenGLShader::SetFloat2, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetFloat2; wrapperSetFloat2.Bind<decltype(SetFloat2), String, Mathematics::Vector2>(SetFloat2);
				callbackTable.Push("SetFloat2", wrapperSetFloat2);

				auto SetFloat3 = std::bind(&OpenGL::OpenGLShader::SetFloat3, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetFloat3; wrapperSetFloat3.Bind<decltype(SetFloat3), String, Mathematics::Vector3>(SetFloat3);
				callbackTable.Push("SetFloat3", wrapperSetFloat3);

				auto SetFloat4 = std::bind(&OpenGL::OpenGLShader::SetFloat4, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetFloat4; wrapperSetFloat4.Bind<decltype(SetFloat4), String, Mathematics::Vector4>(SetFloat4);
				callbackTable.Push("SetFloat4", wrapperSetFloat4);

				auto SetMat4 = std::bind(&OpenGL::OpenGLShader::SetMat4, glShader, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetMat4; wrapperSetMat4.Bind<decltype(SetMat4), String, Mathematics::Matrix4>(SetMat4);
				callbackTable.Push("SetMat4", wrapperSetMat4);

				auto Bind = std::bind(&OpenGL::OpenGLShader::Bind, glShader);
				CallbackWrapper wrapperBind; wrapperBind.Bind<decltype(Bind)>(Bind);
				callbackTable.Push("Bind", wrapperBind);

				auto Unbind = std::bind(&OpenGL::OpenGLShader::Unbind, glShader);
				CallbackWrapper wrapperUnbind; wrapperUnbind.Bind<decltype(Unbind)>(Unbind);
				callbackTable.Push("Unbind", wrapperUnbind);
			}
			return callbackTable;
		}
		break;
		case ResourceType::VertexArray:
		{
			Ref<OpenGL::OpenGLVertexArray> glArray = AnyCast<Ref<OpenGL::OpenGLVertexArray>>(_Data);
			CallbackTable callbackTable = {};
			{
				Function<void(const VertexBuffer& _VertexBuffer, Event& _Event)> _AddVertexBuffer = [glArray](const VertexBuffer& _VertexBuffer, Event& _Event) {
					Interface interface = _VertexBuffer.GetInterface();
					MemoryComponent* component = {};
					_Event.Push(new ComponentComputeEvent(interface))->Retrieve<MemoryComponent>(&component);
					_Event.Proceed(_Event);
					
					Ref<OpenGL::OpenGLVertexBuffer> glBuffer = AnyCast<Ref<OpenGL::OpenGLVertexBuffer>>(component->Data);
					auto run = std::bind(&OpenGL::OpenGLVertexArray::AddVertexBuffer, glArray, glBuffer);
					run();
				};
			
				Function<void(const IndexBuffer& _IndexBuffer, Event& _Event)> _AddIndexBuffer = [glArray](const IndexBuffer& _IndexBuffer, Event& _Event) {
					Interface interface = _IndexBuffer.GetInterface();
					MemoryComponent* component = {};
					_Event.Push(new ComponentComputeEvent(interface))->Retrieve<MemoryComponent>(&component);
					_Event.Proceed(_Event);
					
					Ref<OpenGL::OpenGLIndexBuffer> glBuffer = AnyCast<Ref<OpenGL::OpenGLIndexBuffer>>(component->Data);
					auto run = std::bind(&OpenGL::OpenGLVertexArray::SetIndexBuffer, glArray, glBuffer);
					run();
				};

				auto AddVertexBuffer = std::bind(_AddVertexBuffer, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperAddVertexBuffer; wrapperAddVertexBuffer.Bind<decltype(AddVertexBuffer), const VertexBuffer&, Event&>(AddVertexBuffer);
				callbackTable.Push("AddVertexBuffer", wrapperAddVertexBuffer);

				auto SetIndexBuffer = std::bind(_AddIndexBuffer, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetIndexBuffer; wrapperSetIndexBuffer.Bind<decltype(SetIndexBuffer), const IndexBuffer&, Event&>(SetIndexBuffer);
				callbackTable.Push("SetIndexBuffer", wrapperSetIndexBuffer);
			
				auto Bind = std::bind(&OpenGL::OpenGLVertexArray::Bind, glArray);
				CallbackWrapper wrapperBind; wrapperBind.Bind<decltype(Bind)>(Bind);
				callbackTable.Push("Bind", wrapperBind);
			
				auto Unbind = std::bind(&OpenGL::OpenGLVertexArray::Unbind, glArray);
				CallbackWrapper wrapperUnbind; wrapperUnbind.Bind<decltype(Unbind)>(Unbind);
				callbackTable.Push("Unbind", wrapperUnbind);
			}
			return callbackTable;
		}
		break;
		case ResourceType::VertexBuffer:
		{
			Ref<OpenGL::OpenGLVertexBuffer> glBuffer = AnyCast<Ref<OpenGL::OpenGLVertexBuffer>>(_Data);
			CallbackTable callbackTable = {};
			{
				Function<void(const BufferLayout& _Layout)> _SetLayout = [glBuffer](const BufferLayout& _Layout) {
					Vector<OpenGL::OpenGLBufferElement> elements;
					for (BufferElement element : _Layout)
					{
						auto type = OpenGLFromRendererType(element.Type);
						OpenGL::OpenGLBufferElement newElement = { type, element.Name, element.Normalized };
						elements.push_back(newElement);
					}
					OpenGL::OpenGLBufferLayout layout = { elements };
					
					auto run = std::bind(&OpenGL::OpenGLVertexBuffer::SetLayout, glBuffer, layout);
					run();
				};

				auto SetLayout = std::bind(_SetLayout, std::placeholders::_1);
				CallbackWrapper wrapperSetLayout; wrapperSetLayout.Bind<decltype(SetLayout), const BufferLayout&>(SetLayout);
				callbackTable.Push("SetLayout", wrapperSetLayout);
			
				auto SetData = std::bind(&OpenGL::OpenGLVertexBuffer::SetData, glBuffer, std::placeholders::_1, std::placeholders::_2);
				CallbackWrapper wrapperSetData; wrapperSetData.Bind<decltype(SetData), void*, uint32>(SetData);
				callbackTable.Push("SetData", wrapperSetData);
			
				auto Bind = std::bind(&OpenGL::OpenGLVertexBuffer::Bind, glBuffer);
				CallbackWrapper wrapperBind; wrapperBind.Bind<decltype(Bind)>(Bind);
				callbackTable.Push("Bind", wrapperBind);
			
				auto Unbind = std::bind(&OpenGL::OpenGLVertexBuffer::Unbind, glBuffer);
				CallbackWrapper wrapperUnbind; wrapperUnbind.Bind<decltype(Unbind)>(Unbind);
				callbackTable.Push("Unbind", wrapperUnbind);
			}
			return callbackTable;
		}
		break;
		case ResourceType::IndexBuffer:
		{
			Ref<OpenGL::OpenGLIndexBuffer> glBuffer = AnyCast<Ref<OpenGL::OpenGLIndexBuffer>>(_Data);
			CallbackTable callbackTable = {};
			{
				//auto SetData = std::bind(&OpenGL::OpenGLIndexBuffer::SetData, glBuffer, std::placeholders::_1, std::placeholders::_2);
				//CallbackWrapper wrapperSetData; wrapperSetData.Bind<decltype(SetData), void*, uint32>(SetData);
				//callbackTable.Push("SetData", wrapperSetData);

				auto Bind = std::bind(&OpenGL::OpenGLIndexBuffer::Bind, glBuffer);
				CallbackWrapper wrapperBind; wrapperBind.Bind<decltype(Bind)>(Bind);
				callbackTable.Push("Bind", wrapperBind);

				auto Unbind = std::bind(&OpenGL::OpenGLIndexBuffer::Unbind, glBuffer);
				CallbackWrapper wrapperUnbind; wrapperUnbind.Bind<decltype(Unbind)>(Unbind);
				callbackTable.Push("Unbind", wrapperUnbind);
			}
			return callbackTable;
		}
		break;
		}
	}

}