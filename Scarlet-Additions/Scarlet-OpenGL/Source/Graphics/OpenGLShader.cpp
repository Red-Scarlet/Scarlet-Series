// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.cpp 04/04/2021 - Functional Class.
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace OpenGL {

	static GLenum ShaderTypeFromString(const String& _Type)
	{
		if (_Type == "vertex")
			return GL_VERTEX_SHADER;
		if (_Type == "fragment" || _Type == "pixel")
			return GL_FRAGMENT_SHADER;

		SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const String& _Name, const String& _Source)
		: m_Name(_Name)
	{
		auto shaderSources = PreProcess(_Source);
		Compile(shaderSources);

		//SCARLET_INTERFACE_INFO("Shader: Compiled {0} !", m_Name);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::SetInt(const String& _Name, const uint32& _Int)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniform1i(location, _Int);
	}

	void OpenGLShader::SetFloat(const String& _Name, const float32& _Float)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniform1f(location, _Float);
	}

	void OpenGLShader::SetFloat2(const String& _Name, const Mathematics::Vector2& _Float2)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniform2f(location, _Float2.x, _Float2.y);
	}

	void OpenGLShader::SetFloat3(const String& _Name, const Mathematics::Vector3& _Float3)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniform3f(location, _Float3.x, _Float3.y, _Float3.z);
	}

	void OpenGLShader::SetFloat4(const String& _Name, const Mathematics::Vector4& _Float4)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniform4f(location, _Float4.x, _Float4.y, _Float4.z, _Float4.w);
	}

	void OpenGLShader::SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix4)
	{
		uint32 location = GetUniformLocation(_Name);
		glUniformMatrix4fv(location, 1, GL_FALSE, Mathematics::MathFunction::ValuePtr(_Matrix4));
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	UnorderedMap<GLenum, String> OpenGLShader::PreProcess(const String& _Source)
	{
		UnorderedMap<GLenum, String> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = _Source.find(typeToken, 0);
		while (pos != String::npos)
		{
			size_t eol = _Source.find_first_of("\r\n", pos);
			SCARLET_INTERFACE_ASSERT(eol != String::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			String type = _Source.substr(begin, eol - begin);
			SCARLET_INTERFACE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = _Source.find_first_not_of("\r\n", eol);
			pos = _Source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = _Source.substr(nextLinePos, pos - (nextLinePos == String::npos ? _Source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const UnorderedMap<GLenum, String>& _ShaderSources)
	{
		GLuint program = glCreateProgram();

		Vector<GLenum> glShaderIDs;
		for (auto& kv : _ShaderSources)
		{
			GLenum type = kv.first;
			const String& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				Vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				SCARLET_INTERFACE_ERROR("{0}", infoLog.data());
				SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			Vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			SCARLET_INTERFACE_ERROR("{0}", infoLog.data());
			SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}

	const uint32_t& OpenGLShader::GetUniformLocation(const String& _Name) const
	{
		if (m_UniformLocationCache.find(_Name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[_Name];

		uint32 location = glGetUniformLocation(m_RendererID, _Name.c_str());
		m_UniformLocationCache[_Name] = location;
		return location;
	}

}