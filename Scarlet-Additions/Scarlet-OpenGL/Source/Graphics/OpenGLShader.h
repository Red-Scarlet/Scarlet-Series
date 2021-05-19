// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.h 04/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletRenderer.h>

typedef std::uint32_t GLenum;

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLShader : public Renderer::Shader
	{
	public:
		OpenGLShader(const String& _Name, const String& _Source);
		OpenGLShader(const String& _Name, const String& _Vertex, const String& _Fragment);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const String& _Name, const uint32& _Int) override;
		virtual void SetFloat(const String& _Name, const float32& _Float) override;
		virtual void SetFloat2(const String& _Name, const Mathematics::Vector2& _Float2) override;
		virtual void SetFloat3(const String& _Name, const Mathematics::Vector3& _Float3) override;
		virtual void SetFloat4(const String& _Name, const Mathematics::Vector4& _Float4) override;
		virtual void SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix3) override;

		virtual const String& GetName() const override { return m_Name; }

	private:
		UnorderedMap<GLenum, String> PreProcess(const String& _Source);
		void Compile(const UnorderedMap<GLenum, String>& _ShaderSources);
		const uint32_t& GetUniformLocation(const String& _Name) const;

	private:
		uint32 m_RendererID;
		String m_Name;
		mutable UnorderedMap<String, uint32> m_UniformLocationCache;

	};

}