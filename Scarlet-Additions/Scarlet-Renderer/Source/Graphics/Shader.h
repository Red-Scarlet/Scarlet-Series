// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.h 04/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API Shader
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		Shader(const String& _Name, const String& _Source);
		~Shader();

		void SetInt(const String& _Name, const uint32& _Int);
		void SetFloat(const String& _Name, const float32& _Float);
		void SetFloat2(const String& _Name, const Mathematics::Vector2& _Float2);
		void SetFloat3(const String& _Name, const Mathematics::Vector3& _Float3);
		void SetFloat4(const String& _Name, const Mathematics::Vector4& _Float4);
		void SetMat4(const String& _Name, const Mathematics::Matrix4& _Matrix3);

		void Bind();
		void Unbind();

		const String& GetName() const { return m_Name; }
		const String& GetSource() const { return m_Source; }

	private:
		Interface m_Interface = uint64_max;
		String m_Name;
		String m_Source;

		CallbackTable m_Table;
	};

}