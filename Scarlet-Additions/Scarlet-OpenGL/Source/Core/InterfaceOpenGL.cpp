#include "InterfaceOpenGL.h"
#include <ScarletRenderer.h>

#include "Graphics/OpenGLCommand.h"
#include "Graphics/OpenGLShader.h"
#include "Graphics/OpenGLVertexArray.h"
#include "Graphics/OpenGLVertexBuffer.h"
#include "Graphics/OpenGLIndexBuffer.h"

namespace OpenGL {

    // Can Handle Engine/Module Manager Events.
    void InterfaceOpenGL::OnGlobal(Event& _Event)
    {
        if (!m_Initialized)
        {
            _Event.Push(new ComponentPushEvent(this))->Bind<OpenGLComponent>(nullptr);
            _Event.Push(new SignaturePushEvent(this))->Bind<OpenGLComponent>();
            _Event.Proceed(_Event);
            
            Renderer::RenderCommandCallback = Renderer::CallbackTable<Renderer::RenderCommand>::Create();
            {
                Function<Ref<Renderer::RenderCommand>(const String& _Name)> _RenderCommand = [](const String& _Name) { return CreateRef<OpenGLCommand>(_Name); };
                auto _RenderCommandBind = std::bind(_RenderCommand, std::placeholders::_1);
                Renderer::CallbackWrapper<Renderer::RenderCommand> _RenderCommandWrapper;
                _RenderCommandWrapper.Bind<decltype(_RenderCommandBind), const String&>(_RenderCommandBind);
                Renderer::RenderCommandCallback->Push(_RenderCommandWrapper);
            }

            Renderer::ShaderCallback = Renderer::CallbackTable<Renderer::Shader>::Create();
            {
                Function<Ref<Renderer::Shader>(const String& _Name, const String& _FilePath)> _Shader = [](const String& _Name, const String& _FilePath) { return CreateRef<OpenGLShader>(_Name, _FilePath); };
                auto _ShaderBind = std::bind(_Shader, std::placeholders::_1, std::placeholders::_2);
                Renderer::CallbackWrapper<Renderer::Shader> _ShaderWrapper;
                _ShaderWrapper.Bind<decltype(_ShaderBind), const String&, const String&>(_ShaderBind);
                Renderer::ShaderCallback->Push(_ShaderWrapper);
            }
            {
                Function<Ref<Renderer::Shader>(const String& _Name, const String& _Vertex, const String& _Fragment)> _Shader = 
                    [](const String& _Name, const String& _Vertex, const String& _Fragment) { return CreateRef<OpenGLShader>(_Name, _Vertex, _Fragment); };
                auto _ShaderBind = std::bind(_Shader, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                Renderer::CallbackWrapper<Renderer::Shader> _ShaderWrapper;
                _ShaderWrapper.Bind<decltype(_ShaderBind), const String&, const String&, const String&>(_ShaderBind);
                Renderer::ShaderCallback->Push(_ShaderWrapper);
            }

            Renderer::VertexArrayCallback = Renderer::CallbackTable<Renderer::VertexArray>::Create();
            {
                Function<Ref<Renderer::VertexArray>(const String& _Name)> _VertexArray = [](const String& _Name) { return CreateRef<OpenGLVertexArray>(_Name); };
                auto _VertexArrayBind = std::bind(_VertexArray, std::placeholders::_1);
                Renderer::CallbackWrapper<Renderer::VertexArray> _VertexArrayWrapper;
                _VertexArrayWrapper.Bind<decltype(_VertexArrayBind), const String&>(_VertexArrayBind);
                Renderer::VertexArrayCallback->Push(_VertexArrayWrapper);
            }

            Renderer::VertexBufferCallback = Renderer::CallbackTable<Renderer::VertexBuffer>::Create();
            {
                Function<Ref<Renderer::VertexBuffer>(const uint32& _Size)> _VertexBuffer = [](const uint32& _Size) { return CreateRef<OpenGLVertexBuffer>(_Size); };
                auto _VertexBufferBind = std::bind(_VertexBuffer, std::placeholders::_1);
                Renderer::CallbackWrapper<Renderer::VertexBuffer> _VertexBufferWrapper;
                _VertexBufferWrapper.Bind<decltype(_VertexBufferBind), const uint32&>(_VertexBufferBind);
                Renderer::VertexBufferCallback->Push(_VertexBufferWrapper);
            }
            {
                Function<Ref<Renderer::VertexBuffer>(float32* _Vertices, const uint32& _Size)> _VertexBuffer = [](float32* _Vertices, const uint32& _Size) { return CreateRef<OpenGLVertexBuffer>(_Vertices, _Size); };
                auto _VertexBufferBind = std::bind(_VertexBuffer, std::placeholders::_1, std::placeholders::_2);
                Renderer::CallbackWrapper<Renderer::VertexBuffer> _VertexBufferWrapper;
                _VertexBufferWrapper.Bind<decltype(_VertexBufferBind), float32*, const uint32&>(_VertexBufferBind);
                Renderer::VertexBufferCallback->Push(_VertexBufferWrapper);
            }

            Renderer::IndexBufferCallback = Renderer::CallbackTable<Renderer::IndexBuffer>::Create();
            {
                Function<Ref<Renderer::IndexBuffer>(const uint32& _Size)> _IndexBuffer = [](const uint32& _Size) { return CreateRef<OpenGLIndexBuffer>(_Size); };
                auto _IndexBufferBind = std::bind(_IndexBuffer, std::placeholders::_1);
                Renderer::CallbackWrapper<Renderer::IndexBuffer> _IndexBufferWrapper;
                _IndexBufferWrapper.Bind<decltype(_IndexBufferBind), const uint32&>(_IndexBufferBind);
                Renderer::IndexBufferCallback->Push(_IndexBufferWrapper);
            }
            {
                Function<Ref<Renderer::IndexBuffer>(uint32* _Indices, const uint32& _Size)> _IndexBuffer = [](uint32* _Indices, const uint32& _Size) { return CreateRef<OpenGLIndexBuffer>(_Indices, _Size); };
                auto _IndexBufferBind = std::bind(_IndexBuffer, std::placeholders::_1, std::placeholders::_2);
                Renderer::CallbackWrapper<Renderer::IndexBuffer> _IndexBufferWrapper;
                _IndexBufferWrapper.Bind<decltype(_IndexBufferBind), uint32*, const uint32&>(_IndexBufferBind);
                Renderer::IndexBufferCallback->Push(_IndexBufferWrapper);
            }

            m_Initialized = true;
        }
    }

}