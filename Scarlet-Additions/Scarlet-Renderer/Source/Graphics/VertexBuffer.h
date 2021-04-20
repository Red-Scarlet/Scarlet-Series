// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	enum class VertexAttributeTypes
	{ None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

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

	struct BufferElement
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

	class BufferLayout
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

	struct MeshVertex
	{
	public:
		Mathematics::Vector3 Position;
		Mathematics::Vector3 Normal;
		Mathematics::Vector2 TxtCoord;

		MeshVertex(const Mathematics::Vector3& _Position = { 0.0f, 0.0f, 0.0f }, const Mathematics::Vector3& _Normal = { 0.0f, 0.0f, 0.0f },
			const Mathematics::Vector2& _TexCoord = { 0.0f, 0.0f })
			: Position(_Position), Normal(_Normal), TxtCoord(_TexCoord)
		{
		}

	};

	class OpenGLVertexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLVertexBuffer(const uint32& _Size);
		OpenGLVertexBuffer(const Vector<MeshVertex>& _Vertices);
		OpenGLVertexBuffer(float32* _Vertices, const uint32& _Size);

		virtual ~OpenGLVertexBuffer();

		void SetData(const void* _Data, const uint32& _Size);
		void SetLayout(const BufferLayout& _Layout);
		
		void Bind() const;
		void Unbind() const;

	private:
		uint32 m_RendererID;
		BufferLayout m_Layout;

	public:
		static Ref<OpenGLVertexBuffer> Create(const uint32& _Size)
		{ return CreateRef<OpenGLVertexBuffer>(_Size); }

		static Ref<OpenGLVertexBuffer> Create(const Vector<MeshVertex>& _Vertices)
		{ return CreateRef<OpenGLVertexBuffer>(_Vertices); }

		static Ref<OpenGLVertexBuffer> Create(float32* _Vertices, const uint32& _Size)
		{ return CreateRef<OpenGLVertexBuffer>(_Vertices, _Size); }

	};

}