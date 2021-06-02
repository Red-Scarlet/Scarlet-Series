#include "InterfaceOpenGL.h"
#include <ScarletRenderer.h>

#include "Graphics/OpenGLCommand.h"
#include "Graphics/OpenGLShader.h"
#include "Graphics/OpenGLVertexArray.h"
#include "Graphics/OpenGLVertexBuffer.h"
#include "Graphics/OpenGLIndexBuffer.h"

#include <ScarletWindow.h>

namespace OpenGL {

    // Can Handle Engine/Module Manager Events.
    void InterfaceOpenGL::OnGlobal(Event& _Event)
    {       
        this->SetCallbacks(_Event);

        _Event.Push(new InterfaceRequirementEvent(this))->Set({
            "Scarlet-Renderer"
        });
        if (_Event.Proceed(_Event) == false) return;

        if (!m_Initialized)
        {
            {
                _Event.Push(new SignaturePushEvent(this))->Bind<Renderer::RendererComponent>();
                _Event.Proceed(_Event);

                for (Interface i : m_Set)
                {
                    Renderer::RendererComponent* component = {};
                    _Event.Push(new ComponentComputeEvent(i))->Retrieve<Renderer::RendererComponent>(&component);
                    _Event.Proceed(_Event);

                    if (component) component->API = "OpenGL";
                }

                _Event.Push(new SignaturePopEvent(this))->Bind<Renderer::RendererComponent>();
                _Event.Proceed(_Event);
            }

            {
                void* procAddess = nullptr;
                _Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
                _Event.Proceed(_Event);

                for (Interface i : m_Set)
                {
                    Window::WindowComponent* component = {};
                    _Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
                    _Event.Proceed(_Event);

                    if (component)
                    {
                        if (component->Instance)
                        {
                            component->Instance->SetCurrent();
                            procAddess = component->Instance->GetProcAddress();
                        }
                        else
                        {
                            _Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
                            _Event.Proceed(_Event);
                            return;
                        }
                    }
                }

                _Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
                _Event.Push(new SignaturePushEvent(this))->Bind<OpenGLComponent>();
                _Event.Push(new ComponentPushEvent(this))->Bind<OpenGLComponent>(procAddess);
                _Event.Proceed(_Event);
            }
            
            {
                Function<Ref<Renderer::RenderCommand>(const String& _Name)> _RenderCommand = [](const String& _Name) { return CreateRef<OpenGLCommand>(_Name); };
                auto _RenderCommandBind = std::bind(_RenderCommand, std::placeholders::_1);
                CallbackWrapper _RenderCommandWrapper;
                _RenderCommandWrapper.Bind<Renderer::RenderCommand, decltype(_RenderCommandBind), const String&>(_RenderCommandBind);
                Renderer::RenderCommand::PushWrapper(_RenderCommandWrapper);
            }

            {
                Function<Ref<Renderer::Shader>(const String& _Name, const String& _FilePath)> _Shader = [](const String& _Name, const String& _FilePath) { return CreateRef<OpenGLShader>(_Name, _FilePath); };
                auto _ShaderBind = std::bind(_Shader, std::placeholders::_1, std::placeholders::_2);
                CallbackWrapper _ShaderWrapper;
                _ShaderWrapper.Bind<Renderer::Shader, decltype(_ShaderBind), const String&, const String&>(_ShaderBind);
                Renderer::Shader::PushWrapper(_ShaderWrapper);
            }
            {
                Function<Ref<Renderer::Shader>(const String& _Name, const String& _Vertex, const String& _Fragment)> _Shader = 
                    [](const String& _Name, const String& _Vertex, const String& _Fragment) { return CreateRef<OpenGLShader>(_Name, _Vertex, _Fragment); };
                auto _ShaderBind = std::bind(_Shader, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                CallbackWrapper _ShaderWrapper;
                _ShaderWrapper.Bind<Renderer::Shader, decltype(_ShaderBind), const String&, const String&, const String&>(_ShaderBind);
                Renderer::Shader::PushWrapper(_ShaderWrapper);
            }

            {
                Function<Ref<Renderer::VertexArray>(const String& _Name)> _VertexArray = [](const String& _Name) { return CreateRef<OpenGLVertexArray>(_Name); };
                auto _VertexArrayBind = std::bind(_VertexArray, std::placeholders::_1);
                CallbackWrapper _VertexArrayWrapper;
                _VertexArrayWrapper.Bind<Renderer::VertexArray, decltype(_VertexArrayBind), const String&>(_VertexArrayBind);
                Renderer::VertexArray::PushWrapper(_VertexArrayWrapper);
            }

            {
                Function<Ref<Renderer::VertexBuffer>(const uint32& _Size)> _VertexBuffer = [](const uint32& _Size) { return CreateRef<OpenGLVertexBuffer>(_Size); };
                auto _VertexBufferBind = std::bind(_VertexBuffer, std::placeholders::_1);
                CallbackWrapper _VertexBufferWrapper;
                _VertexBufferWrapper.Bind<Renderer::VertexBuffer, decltype(_VertexBufferBind), const uint32&>(_VertexBufferBind);
                Renderer::VertexBuffer::PushWrapper(_VertexBufferWrapper);
            }
            {
                Function<Ref<Renderer::VertexBuffer>(float32* _Vertices, const uint32& _Size)> _VertexBuffer = [](float32* _Vertices, const uint32& _Size) { return CreateRef<OpenGLVertexBuffer>(_Vertices, _Size); };
                auto _VertexBufferBind = std::bind(_VertexBuffer, std::placeholders::_1, std::placeholders::_2);
                CallbackWrapper _VertexBufferWrapper;
                _VertexBufferWrapper.Bind<Renderer::VertexBuffer, decltype(_VertexBufferBind), float32*, const uint32&>(_VertexBufferBind);
                Renderer::VertexBuffer::PushWrapper(_VertexBufferWrapper);
            }

            {
                Function<Ref<Renderer::IndexBuffer>(const uint32& _Size)> _IndexBuffer = [](const uint32& _Size) { return CreateRef<OpenGLIndexBuffer>(_Size); };
                auto _IndexBufferBind = std::bind(_IndexBuffer, std::placeholders::_1);
                Renderer::CallbackWrapper _IndexBufferWrapper;
                _IndexBufferWrapper.Bind<Renderer::IndexBuffer, decltype(_IndexBufferBind), const uint32&>(_IndexBufferBind);
                Renderer::IndexBuffer::PushWrapper(_IndexBufferWrapper);
            }
            {
                Function<Ref<Renderer::IndexBuffer>(uint32* _Indices, const uint32& _Size)> _IndexBuffer = [](uint32* _Indices, const uint32& _Size) { return CreateRef<OpenGLIndexBuffer>(_Indices, _Size); };
                auto _IndexBufferBind = std::bind(_IndexBuffer, std::placeholders::_1, std::placeholders::_2);
                CallbackWrapper _IndexBufferWrapper;
                _IndexBufferWrapper.Bind<Renderer::IndexBuffer, decltype(_IndexBufferBind), uint32*, const uint32&>(_IndexBufferBind);
                Renderer::IndexBuffer::PushWrapper(_IndexBufferWrapper);
            }

            m_RenderCommand = Renderer::RenderCommand::Create("BasicCommmand");
            m_Running = true, m_Initialized = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceOpenGL::OnAppUpdate));
        if (!_Event.Handled) return;
    }

    void InterfaceOpenGL::OnEditor(Event& _Event)
    {
        if(m_Running)
        {
            if (!m_Panel) m_Panel = PanelUI::Create("GLPanel");
            if (m_Panel && !m_EditorInitialized)
            {
                m_Panel->Attach(LabelUI::Create("Hello, GL!"));;
                m_EditorInitialized = true;
            }

            _Event.Push(new EditorPanelBindEvent())->Bind(m_Panel);
        }
    }

    bool InterfaceOpenGL::OnAppUpdate(AppUpdateEvent& _Event)
    {
        return m_Running;
    }

}