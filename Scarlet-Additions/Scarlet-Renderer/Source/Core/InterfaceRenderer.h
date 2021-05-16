// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererContext.h 10/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

#include "Graphics/RenderCommand.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexArray.h"

namespace Renderer {

	using namespace ScarletInterface;

	// OpenGL Interface currently uses GLFW (Abstract to Scarlet-WindowAPI)
	class SCARLET_INTERFACE_API InterfaceRenderer : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;

	private:
		bool OnAppUpdate(AppUpdateEvent& _Event);

	private:
		RenderCommand* m_RenderCommand;
		Shader* m_Shader;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		VertexArray* m_VertexArray;

		bool m_Running = false, m_Initialized = false, m_VertexArraySet = false, m_VertexBufferSet;
	};

}

INTERFACE_ENTRYPOINT(Renderer::InterfaceRenderer);