#include "InterfaceGLFW.h"

#include <Events/InterfaceEvent.h>

namespace GLFW {

    // Can Handle Engine/Module Manager Events.
    void InterfaceGLFW::OnGlobal(Event& _Event)
    {
        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnAppUpdate));
    }

    void InterfaceGLFW::OnLocal(Event& _Event)
    {
        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<WindowCloseEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnWindowClose));
    }

    bool InterfaceGLFW::OnAppUpdate(AppUpdateEvent& _Event)
    {
        if (!m_Initialized)
        {
            WindowProps WindowProperties;
            WindowProperties.Title = "ScarletGLFW";
            m_Instance = Window::Create(WindowProperties);
            m_Instance->SetEventCallback(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnLocal));
            m_Context = GLFWContext::Create((GLFWwindow*)m_Instance->GetNativeWindow());
            m_Context->SwapInterval();
            m_Running = true, m_Initialized = true;
        }

        if (m_Running && !m_Minimized)
        {
            m_Instance->OnUpdate();
            m_Context->SwapBuffers();
        }

        if (!m_Running)
        {
            m_Instance.reset();
            m_Context.reset();

            _Event.SetNext(new InterfacePopEvent(this));
        }

        return !m_Minimized;
    }

    bool InterfaceGLFW::OnWindowClose(WindowCloseEvent& _Event)
    {
        m_Running = false;
        m_Minimized = true;

        return false;
    }

    bool InterfaceGLFW::OnWindowResize(WindowResizeEvent& _Event)
    {
        m_Minimized = false;
        if (_Event.GetWidth() == 0 || _Event.GetHeight() == 0)
            m_Minimized = true;

        return false;
    }
}