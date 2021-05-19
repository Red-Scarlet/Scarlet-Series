// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletRenderer.h>

namespace OpenGL {

	using namespace ScarletInterface;
	
	class SCARLET_INTERFACE_API OpenGLCommand : public Renderer::RenderCommand
	{
	public:
		OpenGLCommand(const String& _Name);
		virtual ~OpenGLCommand() = default;

		virtual void Enable(const Renderer::RendererEnableFlag& _Flag) override;
		virtual void Disable(const Renderer::RendererEnableFlag& _Flag) override;

		virtual void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height) override;
		virtual void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A) override;
		virtual void SetClearBuffer(const Renderer::RendererClearFlag& _Flag) override;
		virtual void SetPolygonMode(const Renderer::RendererPolygonFlag& _Flag) override;

		virtual void DrawArrays(const Renderer::RendererDrawingFlag& _Flag, const Ref<Renderer::VertexArray>& _VertexArray, const uint32& _IndexCount = 0) override;
		virtual void DrawElements(const Renderer::RendererDrawingFlag& _Flag, const Ref<Renderer::VertexArray>& _VertexArray, const uint32& _IndexCount = 0) override;

	private:
		String m_Name;
	};

}