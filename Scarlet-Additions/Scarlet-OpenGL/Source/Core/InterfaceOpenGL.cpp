#include "InterfaceOpenGL.h"
#include <Events/InterfaceEvent.h>
#include "Graphics/OpenGLCommand.h"
#include "Components/OpenGLComponent.h"

#include <ScarletGLFW.h>

namespace OpenGL {

    // Can Handle Engine/Module Manager Events.
    void InterfaceOpenGL::OnGlobal(Event& _Event)
    {
        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceOpenGL::OnAppUpdate));

        _Event.SetNext(new SignaturePushEvent(this))->Bind<OpenGLComponent>();
    }

    void InterfaceOpenGL::OnLocal(Event& _Event)
    {
    }

    bool InterfaceOpenGL::OnAppUpdate(AppUpdateEvent& _Event)
    {
        if (!m_Initialized)
        {
            _Event.SetNext(new SignaturePopEvent(this))->Bind<OpenGLComponent>();
            _Event.SetNext(new SignaturePushEvent(this))->Bind<GLFW::GLFWComponent>();

            {
                //for (auto interfac : m_InterfaceSet)
                //{
                    
                //}

                //m_Context = OpenGLContext::Create();
            }

            _Event.SetNext(new SignaturePopEvent(this))->Bind<GLFW::GLFWComponent>();
            _Event.SetNext(new SignaturePushEvent(this))->Bind<OpenGLComponent>();

            m_Initialized = true;
        }

        if (m_Running)
        {
            OpenGLCommand::SetClearColor(0.8f, 0.3f, .5f, 1.0f);
            OpenGLCommand::SetClearBuffer(OpenGLClearFlag::OpenGLColor | OpenGLClearFlag::OpenGLDepth);
        }

        return true;
    }

}