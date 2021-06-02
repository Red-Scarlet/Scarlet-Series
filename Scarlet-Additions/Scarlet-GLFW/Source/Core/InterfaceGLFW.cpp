#include "InterfaceGLFW.h"

#include <Events/InterfaceEvent.h>
#include "Platform/Windows/WindowsWindow.h"
#include "Components/GLFWComponent.h"

namespace GLFW {

    // Can Handle Engine/Module Manager Events.
    void InterfaceGLFW::OnGlobal(Event& _Event)
    {
        if (!m_Initialized)
        {       
            _Event.Push(new InterfaceRequirementEvent(this))->Set({
                "Scarlet-Window"
            });
            if (_Event.Proceed(_Event) == false) return;

            {
                Function<Ref<Window::WindowContext>(const Window::WindowProps& _Props)> _WindowContext = [](const Window::WindowProps& _Props) { return CreateRef<WindowsWindow>(_Props); };
                auto _WindowContextBind = std::bind(_WindowContext, std::placeholders::_1);
                CallbackWrapper _WindowContextWrapper;
                _WindowContextWrapper.Bind<Window::WindowContext, decltype(_WindowContextBind), const Window::WindowProps&>(_WindowContextBind);
                Window::WindowContext::PushWrapper(_WindowContextWrapper);
            }

            {
                _Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
                _Event.Proceed(_Event);

                for (Interface i : m_Set)
                {
                    Window::WindowComponent* component = {};
                    _Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
                    _Event.Proceed(_Event);

                    if (component)
                    {
                        Window::WindowProps WindowProperties;
                        WindowProperties.Title = "ScarletGLFW";

                        component->API = "Scarlet-GLFW";
                        component->Instance = Window::WindowContext::Create(WindowProperties);
                        component->Instance->SetEventCallback(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnLocal));
                    }
                    
                }

                _Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
                _Event.Push(new SignaturePushEvent(this))->Bind<GLFWComponent>();
                _Event.Proceed(_Event);
            }

            _Event.Push(new ComponentPushEvent(this))->Bind<GLFWComponent>({});
            _Event.Proceed(_Event);

            m_Running = true, m_Initialized = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnAppUpdate));
        if (!_Event.Handled) return;

        // Example
        //OnEditor();
    }

    // This just comes after the global
    void InterfaceGLFW::OnEditor(Event& _Event)
    {
        //_Event.Push(new EditorDrawEvent(this))->Bind(m_FrameRateLabel);
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
            _Event.Push(new SignaturePopEvent(this))->Bind<GLFWComponent>();
            _Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
            _Event.Proceed(_Event);

            for (Interface i : m_Set)
            {
                Window::WindowComponent* component = {};
                _Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
                _Event.Proceed(_Event);

                if (component) component->Instance->OnUpdate();
            }

            _Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
            _Event.Push(new SignaturePushEvent(this))->Bind<GLFWComponent>();
            _Event.Proceed(_Event);
        }
        else
        {
            _Event.Push(new SignaturePopEvent(this))->Bind<GLFWComponent>();
            _Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
            _Event.Proceed(_Event);

            for (Interface i : m_Set)
            {
                Window::WindowComponent* component = {};
                _Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
                _Event.Proceed(_Event);

                if (component) component->Instance.reset();
            }

            _Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
            _Event.Push(new SignaturePushEvent(this))->Bind<GLFWComponent>();
            _Event.Proceed(_Event);
        }


        return m_Running;
    }

    bool InterfaceGLFW::OnWindowClose(Window::WindowCloseEvent& _Event)
    {
        m_Running = false;

        return true;
    }

}