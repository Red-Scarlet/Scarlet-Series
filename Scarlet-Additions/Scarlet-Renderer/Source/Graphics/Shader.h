#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const String& _Name, const uint32& _Value) = 0;
		virtual void SetFloat(const String& _Name, const float32& _Value) = 0;
		virtual void SetFloat2(const String& _Name, const Mathematics::Vector2& _Value) = 0;
		virtual void SetFloat3(const String& _Name, const Mathematics::Vector3& _Value) = 0;
		virtual void SetFloat4(const String& _Name, const Mathematics::Vector4& _Value) = 0;
		virtual void SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix) = 0;

		virtual const String& GetName() const = 0;

	private:
		static Ref<CallbackTable<Shader>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<Shader>& _Wrapper);
		static Ref<Shader> Create(const String& _FilePath);
		static Ref<Shader> Create(const String& _Name, const String& _VertexPath, const String& _FragPath);
	};

}