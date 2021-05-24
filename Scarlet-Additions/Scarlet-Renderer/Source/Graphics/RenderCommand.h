#pragma once

#include <ScarletInterface.h>
#include "VertexArray.h"

namespace Renderer {

	using namespace ScarletInterface;

	enum class SCARLET_INTERFACE_API RendererEnableFlag : uint8
	{
		RendererNone = 0x00,
		RendererBlend = 0x01,
		RendererDepthTest = 0x02,
	};

	enum class SCARLET_INTERFACE_API RendererClearFlag : uint8
	{
		RendererNone = 0x00,
		RendererColor = 0x01,
		RendererDepth = 0x02,
		RendererStencil = 0x04
	};

	enum class SCARLET_INTERFACE_API RendererPolygonFlag : uint8
	{
		RendererNone = 0x00,
		RendererPoint = 0x01,
		RendererLine = 0x02,
		RendererFill = 0x04
	};

	enum class SCARLET_INTERFACE_API RendererDrawingFlag : uint8
	{
		RendererNone = 0x00,
		RendererPoints = 0x01,
		RendererLines = 0x02,
		RendererTriangles = 0x04
	};

	class SCARLET_INTERFACE_API RenderCommand
	{
	public:
		virtual ~RenderCommand() = default;

		virtual void Enable(const RendererEnableFlag& _Flag) = 0;
		virtual void Disable(const RendererEnableFlag& _Flag) = 0;

		virtual void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height) = 0;
		virtual void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A) = 0;
		virtual void SetClearBuffer(const RendererClearFlag& _Flag) = 0;
		virtual void SetPolygonMode(const RendererPolygonFlag& _Flag) = 0;

		virtual void DrawArrays(const RendererDrawingFlag& _Flag, const Ref<VertexArray>& _VertexArray, const uint32& _IndexCount = 0) = 0;
		virtual void DrawElements(const RendererDrawingFlag& _Flag, const Ref<VertexArray>& _VertexArray, const uint32& _IndexCount = 0) = 0;

	private:
		static Ref<CallbackTable<RenderCommand>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<RenderCommand>& _Wrapper);
		static Ref<RenderCommand> Create(const String& _Name);
	};

}