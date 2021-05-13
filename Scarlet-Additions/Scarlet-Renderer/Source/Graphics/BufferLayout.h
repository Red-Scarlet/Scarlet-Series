#pragma once

#include <ScarletInterface.h>

namespace  {

	using namespace ScarletInterface;

	enum class SCARLET_INTERFACE_API VertexAttributeTypes
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static const uint32& VertexAttributeTypesSize(const VertexAttributeTypes& _Type)
	{
		switch (_Type)
		{
		case VertexAttributeTypes::Float:		return 4;
		case VertexAttributeTypes::Float2:		return 8;
		case VertexAttributeTypes::Float3:		return 12;
		case VertexAttributeTypes::Float4:		return 16;
		case VertexAttributeTypes::Mat3:		return 36;
		case VertexAttributeTypes::Mat4:		return 64;
		case VertexAttributeTypes::Int:			return 4;
		case VertexAttributeTypes::Int2:		return 8;
		case VertexAttributeTypes::Int3:		return 12;
		case VertexAttributeTypes::Int4:		return 16;
		case VertexAttributeTypes::Bool:		return 1;
		}

		SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown VertexAttributeTypes!");
		return 0;
	}


	struct SCARLET_INTERFACE_API BufferElement
	{
	public:
		VertexAttributeTypes Type;
		String Name;
		uint32 Size;
		uint32 Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(const VertexAttributeTypes& _Type, const String& _Name, const bool& _Normalized = false)
			: Type(_Type), Name(_Name), Size(VertexAttributeTypesSize(_Type)), Offset(0), Normalized(_Normalized)
		{
		}

		const uint32& GetComponentCount() const
		{
			switch (Type)
			{
			case VertexAttributeTypes::Float:		return 1;
			case VertexAttributeTypes::Float2:		return 2;
			case VertexAttributeTypes::Float3:		return 3;
			case VertexAttributeTypes::Float4:		return 4;
			case VertexAttributeTypes::Mat3:		return 9;
			case VertexAttributeTypes::Mat4:		return 16;
			case VertexAttributeTypes::Int:			return 1;
			case VertexAttributeTypes::Int2:		return 2;
			case VertexAttributeTypes::Int3:		return 3;
			case VertexAttributeTypes::Int4:		return 4;
			case VertexAttributeTypes::Bool:		return 1;
			}

			SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class SCARLET_INTERFACE_API BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const InitializerList<BufferElement>& _Element)
			: m_Elements(_Element)
		{
			CalculateOffsetAndStride();
		}

		const uint32& GetStride() const { return m_Stride; }
		const Vector<BufferElement>& GetElements() const { return m_Elements; }

		Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		Vector<BufferElement>::iterator end() { return m_Elements.end(); }
		Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		Vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

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
		Vector<BufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

}