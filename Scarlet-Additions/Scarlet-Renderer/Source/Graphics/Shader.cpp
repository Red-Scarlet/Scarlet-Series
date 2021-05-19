#include "Shader.h"

namespace Renderer {
	
	//Ref<CallbackTable<Shader>> ShaderCallback = nullptr;

	Ref<Shader> Shader::Create(const String& _FilePath)
	{
		if (ShaderCallback->Empty()) return nullptr;
		return ShaderCallback->Create(_FilePath);
	} 

	Ref<Shader> Shader::Create(const String& _Name, const String& _VertexPath, const String& _FragPath)
	{
		if (ShaderCallback->Empty()) return nullptr;
		return ShaderCallback->Create(_Name, _VertexPath, _FragPath);
	}

}