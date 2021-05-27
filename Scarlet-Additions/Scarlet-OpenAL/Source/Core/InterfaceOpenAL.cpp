#include "InterfaceOpenAL.h"
#include <ScarletAudioFX.h>
#include <Events/InterfaceEvent.h>

#include "Components/OpenALComponent.h"
#include "Resources/OpenALBuffer.h"
#include "Resources/OpenALDevice.h"
#include "Resources/OpenALListener.h"
#include "Resources/OpenALSource.h"

namespace OpenAL {

    // Can Handle Engine/Module Manager Events.
    void InterfaceOpenAL::OnGlobal(Event& _Event)
    {
        _Event.Push(new InterfaceRequirementEvent(this))->Set({
            "Scarlet-AudioFX"
        });
        if (_Event.Proceed(_Event) == false) return;

        if (!m_Initialized)
        {
            {
                _Event.Push(new SignaturePushEvent(this))->Bind<AudioFX::AudioFXComponent>();
                _Event.Proceed(_Event);

                for (Interface i : m_Set)
                {
                    AudioFX::AudioFXComponent* component = {};
                    _Event.Push(new ComponentComputeEvent(i))->Retrieve<AudioFX::AudioFXComponent>(&component);
                    _Event.Proceed(_Event);

                    if (component) component->API = "OpenAL";
                }

                _Event.Push(new SignaturePopEvent(this))->Bind<AudioFX::AudioFXComponent>();
                _Event.Push(new SignaturePushEvent(this))->Bind<OpenALComponent>();
                _Event.Push(new ComponentPushEvent(this))->Bind<OpenALComponent>({});
                _Event.Proceed(_Event);
            }

            _Event.Push(new SignaturePushEvent(this))->Bind<OpenALComponent>();
            _Event.Proceed(_Event);
            
            {
                Function<Ref<AudioFX::AudioBuffer>(const String& _Name)> _AudioBuffer = [](const String& _Name) { return CreateRef<OpenALBuffer>(_Name); };
                auto _AudioBufferBind = std::bind(_AudioBuffer, std::placeholders::_1);
                CallbackWrapper<AudioFX::AudioBuffer> _AudioBufferWrapper;
                _AudioBufferWrapper.Bind<decltype(_AudioBufferBind), const String&>(_AudioBufferBind);
                AudioFX::AudioBuffer::PushWrapper(_AudioBufferWrapper);
            }

            {
                Function<Ref<AudioFX::AudioDevice>(const String& _Name)> _AudioDevice = [](const String& _Name) { return CreateRef<OpenALDevice>(_Name); };
                auto _AudioDeviceBind = std::bind(_AudioDevice, std::placeholders::_1);
                CallbackWrapper<AudioFX::AudioDevice> _AudioDeviceWrapper;
                _AudioDeviceWrapper.Bind<decltype(_AudioDeviceBind), const String&>(_AudioDeviceBind);
                AudioFX::AudioDevice::PushWrapper(_AudioDeviceWrapper);
            }

            {
                Function<Ref<AudioFX::AudioListener>(const Mathematics::Transform& _Transform)> _AudioListener = [](const Mathematics::Transform& _Transform) { return CreateRef<OpenALListener>(_Transform); };
                auto _AudioListenerBind = std::bind(_AudioListener, std::placeholders::_1);
                CallbackWrapper<AudioFX::AudioListener> _AudioListenerWrapper;
                _AudioListenerWrapper.Bind<decltype(_AudioListenerBind), const Mathematics::Transform&>(_AudioListenerBind);
                AudioFX::AudioListener::PushWrapper(_AudioListenerWrapper);
            }

            {
                Function<Ref<AudioFX::AudioSource>(const Mathematics::Transform& _Transform)> _AudioSource = [](const Mathematics::Transform& _Transform) { return CreateRef<OpenALSource>(_Transform); };
                auto _AudioSourceBind = std::bind(_AudioSource, std::placeholders::_1);
                CallbackWrapper<AudioFX::AudioSource> _AudioSourceWrapper;
                _AudioSourceWrapper.Bind<decltype(_AudioSourceBind), const Mathematics::Transform&>(_AudioSourceBind);
                AudioFX::AudioSource::PushWrapper(_AudioSourceWrapper);
            }

            m_Running = true, m_Initialized = true;
        }

        EventDispatcher dispatcher(_Event);
        dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceOpenAL::OnAppUpdate));
        if (!_Event.Handled) return;
    }

    bool InterfaceOpenAL::OnAppUpdate(AppUpdateEvent& _Event)
    {
        return m_Running;
    }

}