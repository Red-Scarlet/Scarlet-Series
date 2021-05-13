#pragma once

#include "Core/CallbackTable.h"
#include "Components/AllocateComponent.h"
#include "Components/MemoryComponent.h"

#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include <Events/InterfaceEvent.h>
#include <ScarletInterface.h>
#include <ScarletOpenGL.h>

namespace Renderer {

	static CallbackTable OpenGLAllocate(const ResourceType& _Type, const AnyData& _Data)
	{
		switch (_Type)
		{
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

		}
		break;
		}
	}

}