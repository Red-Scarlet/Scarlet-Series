#include "Shader.h"

#include "Components/AllocateComponent.h"
#include "Core/ResourceQueue.h"

namespace Renderer {

	Shader::Shader(const String& _Name, const String& _Source)
		: m_Name(_Name), m_Source(_Source)
	{
		AllocateComponent Allocate = { ResourceType::Shader };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	Shader::~Shader()
	{
	}

	void Shader::SetInt(const String& _Name, const uint32& _Int)
	{
		m_Table.Call("SetInt", _Name, _Int);
	}

	void Shader::SetFloat(const String& _Name, const float32& _Float)
	{
		m_Table.Call("SetFloat", _Name, _Float);
	}

	void Shader::SetFloat2(const String& _Name, const Mathematics::Vector2& _Float2)
	{
		m_Table.Call("SetFloat2", _Name, _Float2);
	}

	void Shader::SetFloat3(const String& _Name, const Mathematics::Vector3& _Float3)
	{
		m_Table.Call("SetFloat3", _Name, _Float3);
	}

	void Shader::SetFloat4(const String& _Name, const Mathematics::Vector4& _Float4)
	{
		m_Table.Call("SetFloat4", _Name, _Float4);
	}

	void Shader::SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix4)
	{
		m_Table.Call("SetMat4", _Name, _Matrix4);
	}

	void Shader::Bind()
	{
		m_Table.Call("Bind");
	}

	void Shader::Unbind()
	{
		m_Table.Call("Unbind");
	}

}