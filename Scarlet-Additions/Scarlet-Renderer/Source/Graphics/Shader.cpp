#include "Shader.h"

namespace Renderer {
	
	Ref<CallbackTable<Shader>> Shader::s_Callback = CallbackTable<Shader>::Create();

	void Shader::PushWrapper(const CallbackWrapper<Shader>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<Shader> Shader::Create(const String& _FilePath)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_FilePath);
	} 

	Ref<Shader> Shader::Create(const String& _Name, const String& _VertexPath, const String& _FragPath)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Name, _VertexPath, _FragPath);
	}

}