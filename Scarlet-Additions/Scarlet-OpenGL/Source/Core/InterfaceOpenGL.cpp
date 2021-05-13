#include "InterfaceOpenGL.h"
#include "Components/OpenGLComponent.h"

#include <Events/InterfaceEvent.h>
#include <ScarletGLFW.h>

namespace OpenGL {

    // Can Handle Engine/Module Manager Events.
    void InterfaceOpenGL::OnGlobal(Event& _Event)
    {
        if (!m_Initialized)
        {
            _Event.Push(new ComponentPushEvent(this))->Bind<OpenGLComponent>(nullptr);
            _Event.Push(new SignaturePushEvent(this))->Bind<OpenGLComponent>();
            _Event.Proceed(_Event);

            m_Initialized = true, m_Running = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceOpenGL::OnAppUpdate));
    }

    bool InterfaceOpenGL::OnAppUpdate(AppUpdateEvent& _Event)
    {
        if (m_Running)
        {
            OpenGLCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            OpenGLCommand::SetClearBuffer(OpenGLClearFlag::OpenGLColor | OpenGLClearFlag::OpenGLDepth);
        }

        return true;
    }

}