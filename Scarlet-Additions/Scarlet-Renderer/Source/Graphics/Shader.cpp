#include "Shader.h"

namespace Renderer {
	
	Ref<CallbackTable> Shader::s_Callback = CallbackTable::Create();

	void Shader::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<Shader> Shader::Create(const String& _FilePath)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<Shader>(_FilePath);
	} 

	Ref<Shader> Shader::Create(const String& _Name, const String& _VertexPath, const String& _FragPath)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<Shader>(_Name, _VertexPath, _FragPath);
	}

}