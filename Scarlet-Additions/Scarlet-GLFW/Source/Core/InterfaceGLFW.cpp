#include "InterfaceGLFW.h"

#include <Events/InterfaceEvent.h>
#include "Components/GLFWComponent.h"

namespace GLFW {

    // Can Handle Engine/Module Manager Events.
    void InterfaceGLFW::OnGlobal(Event& _Event)
    {
        if (!m_Initialized)
        {
            WindowProps WindowProperties;
            WindowProperties.Title = "ScarletGLFW";

            _Event.Push(new ComponentPushEvent(this))->Bind<GLFWComponent>(WindowProperties);
            _Event.Push(new SignaturePushEvent(this))->Bind<GLFWComponent>();
            _Event.Proceed(_Event);

            GLFWComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<GLFWComponent>(&component);
            _Event.Proceed(_Event);

            component->Instance->SetEventCallback(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnLocal));
            component->Context->SwapInterval();

            m_Initialized = true, m_Running = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnAppUpdate));
        if (!_Event.Handled) Sleep(1000); return;
    }

    void InterfaceGLFW::OnLocal(Event& _Event)
    {
        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<WindowCloseEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnWindowClose));
    }

    bool InterfaceGLFW::OnAppUpdate(AppUpdateEvent& _Event)
    {
        if (m_Running)
        {
            GLFWComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<GLFWComponent>(&component);
            _Event.Proceed(_Event);

            component->Context->SwapBuffers();
            component->Instance->OnUpdate();
        }

        if (!m_Running)
        {
            GLFWComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<GLFWComponent>(&component);
            _Event.Proceed(_Event);

            component->Context.reset();
            component->Instance.reset();
        }

        return m_Running;
    }

    bool InterfaceGLFW::OnWindowClose(WindowCloseEvent& _Event)
    {
        m_Running = false;

        return true;
    }

    bool InterfaceGLFW::OnWindowResize(WindowResizeEvent& _Event)
    {
        m_Minimized = false;
        if (_Event.GetWidth() == 0 || _Event.GetHeight() == 0)
            m_Minimized = true;

        return true;
    }
}