// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.h 04/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

typedef std::uint32_t GLenum;

namespace OpenGL {

	using namespace ScarletInterface;

	class OpenGLShader
	{
	public:
		OpenGLShader(const String& _Name, const String& _Source);
		virtual ~OpenGLShader();

		void SetInt(const String& _Name, const uint32& _Int);
		void SetFloat(const String& _Name, const float32& _Float);
		void SetFloat2(const String& _Name, const Mathematics::Vector2& _Float2);
		void SetFloat3(const String& _Name, const Mathematics::Vector3& _Float3);
		void SetFloat4(const String& _Name, const Mathematics::Vector4& _Float4);
		void SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix3);

		const String& GetName() const { return m_Name; }

		void Bind() const;
		void Unbind() const;

	private:
		UnorderedMap<GLenum, String> PreProcess(const String& _Source);
		void Compile(const UnorderedMap<GLenum, String>& _ShaderSources);
		const uint32_t& GetUniformLocation(const String& _Name) const;

	private:
		uint32 m_RendererID;
		String m_Name;
		mutable UnorderedMap<String, uint32> m_UniformLocationCache;

	public:
		static Ref<OpenGLShader> Create(const String& _Name, const String& _Source)
		{ return CreateRef<OpenGLShader>(_Name, _Source); }

	};

}