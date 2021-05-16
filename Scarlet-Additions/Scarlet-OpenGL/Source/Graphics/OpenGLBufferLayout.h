#pragma once

#include <ScarletInterface.h>

namespace OpenGL {

	using namespace ScarletInterface;

	enum class SCARLET_INTERFACE_API OpenGLVertexAttributeTypes
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static const uint32& OpenGLVertexAttributeTypesSize(const OpenGLVertexAttributeTypes& _Type)
	{
		switch (_Type)
		{
		case OpenGLVertexAttributeTypes::Float:		return 4;
		case OpenGLVertexAttributeTypes::Float2:		return 8;
		case OpenGLVertexAttributeTypes::Float3:		return 12;
		case OpenGLVertexAttributeTypes::Float4:		return 16;
		case OpenGLVertexAttributeTypes::Mat3:		return 36;
		case OpenGLVertexAttributeTypes::Mat4:		return 64;
		case OpenGLVertexAttributeTypes::Int:			return 4;
		case OpenGLVertexAttributeTypes::Int2:		return 8;
		case OpenGLVertexAttributeTypes::Int3:		return 12;
		case OpenGLVertexAttributeTypes::Int4:		return 16;
		case OpenGLVertexAttributeTypes::Bool:		return 1;
		}

		SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown VertexAttributeTypes!");
		return 0;
	}

	struct SCARLET_INTERFACE_API OpenGLBufferElement
	{
	public:
		OpenGLVertexAttributeTypes Type;
		String Name;
		uint32 Size;
		uint32 Offset;
		bool Normalized;

		OpenGLBufferElement() = default;
		OpenGLBufferElement(const OpenGLVertexAttributeTypes& _Type, const String& _Name, const bool& _Normalized = false)
			: Type(_Type), Name(_Name), Size(OpenGLVertexAttributeTypesSize(_Type)), Offset(0), Normalized(_Normalized)
		{
		}

		const uint32& GetComponentCount() const
		{
			switch (Type)
			{
			case OpenGLVertexAttributeTypes::Float:		return 1;
			case OpenGLVertexAttributeTypes::Float2:		return 2;
			case OpenGLVertexAttributeTypes::Float3:		return 3;
			case OpenGLVertexAttributeTypes::Float4:		return 4;
			case OpenGLVertexAttributeTypes::Mat3:		return 9;
			case OpenGLVertexAttributeTypes::Mat4:		return 16;
			case OpenGLVertexAttributeTypes::Int:			return 1;
			case OpenGLVertexAttributeTypes::Int2:		return 2;
			case OpenGLVertexAttributeTypes::Int3:		return 3;
			case OpenGLVertexAttributeTypes::Int4:		return 4;
			case OpenGLVertexAttributeTypes::Bool:		return 1;
			}

			SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class SCARLET_INTERFACE_API OpenGLBufferLayout
	{
	public:
		OpenGLBufferLayout() = default;
		OpenGLBufferLayout(const Vector<OpenGLBufferElement>& _Element)
			: m_Elements(_Element)
		{
			CalculateOffsetAndStride();
		}
		OpenGLBufferLayout(const InitializerList<OpenGLBufferElement>& _Element)
			: m_Elements(_Element)
		{
			CalculateOffsetAndStride();
		}

		const uint32& GetStride() const { return m_Stride; }
		const Vector<OpenGLBufferElement>& GetElements() const { return m_Elements; }

		Vector<OpenGLBufferElement>::iterator begin() { return m_Elements.begin(); }
		Vector<OpenGLBufferElement>::iterator end() { return m_Elements.end(); }
		Vector<OpenGLBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		Vector<OpenGLBufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride()
		{
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		Vector<OpenGLBufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

}