#include "InterfaceGLFW.h"

#include <Events/InterfaceEvent.h>
#include "Components/GLFWComponent.h"
#include "Platform/Windows/WindowsWindow.h"

namespace GLFW {

    // Can Handle Engine/Module Manager Events.
    void InterfaceGLFW::OnGlobal(Event& _Event)
    {
        if (!m_Initialized)
        {
            _Event.Push(new SignaturePushEvent(this))->Bind<GLFWComponent>();
            _Event.Proceed(_Event);

            {
                Function<Ref<Window::WindowContext>(const Window::WindowProps& _Props)> _WindowContext = [](const Window::WindowProps& _Props) { return CreateRef<WindowsWindow>(_Props); };
                auto _WindowContextBind = std::bind(_WindowContext, std::placeholders::_1);
                CallbackWrapper<Window::WindowContext> _WindowContextWrapper;
                _WindowContextWrapper.Bind<decltype(_WindowContextBind), const Window::WindowProps&>(_WindowContextBind);
                Window::WindowContext::PushWrapper(_WindowContextWrapper);
            }

            Window::WindowProps WindowProperties;
            WindowProperties.Title = "ScarletGLFW";

            GLFWComponent component = {};
            component.Instance = Window::WindowContext::Create(WindowProperties);
            component.Instance->SetEventCallback(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnLocal));

            _Event.Push(new ComponentPushEvent(this))->Bind<GLFWComponent>(component);
            _Event.Proceed(_Event);

            m_Running = true, m_Initialized = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnAppUpdate));
        if (!_Event.Handled) return;
    }

    void InterfaceGLFW::OnLocal(Event& _Event)
    {
        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<Window::WindowCloseEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnWindowClose));
    }

    bool InterfaceGLFW::OnAppUpdate(AppUpdateEvent& _Event)
    {
        if (m_Running)
        {
            GLFWComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<GLFWComponent>(&component);
            _Event.Proceed(_Event);

            component->Instance->OnUpdate();
        }

        if (!m_Running)
        {
            GLFWComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<GLFWComponent>(&component);
            _Event.Proceed(_Event);

            component->Instance.reset();
        }

        return m_Running;
    }

    bool InterfaceGLFW::OnWindowClose(Window::WindowCloseEvent& _Event)
    {
        m_Running = false;

        return true;
    }

}