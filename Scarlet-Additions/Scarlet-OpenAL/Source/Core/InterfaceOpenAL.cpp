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
        if (!m_Initialized)
        {
            _Event.Push(new SignaturePushEvent(this))->Bind<OpenALComponent>();
            _Event.Push(new ComponentPushEvent(this))->Bind<OpenALComponent>({});
            _Event.Proceed(_Event);
            
            {
                Function<Ref<AudioFX::AudioBuffer>(const String& _Name)> _AudioBuffer = [](const String& _Name) { return CreateRef<OpenALBuffer>(_Name); };
                auto _AudioBufferBind = std::bind(_AudioBuffer, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioBuffer> _AudioBufferWrapper;
                _AudioBufferWrapper.Bind<decltype(_AudioBufferBind), const String&>(_AudioBufferBind);
                AudioFX::AudioBuffer::PushWrapper(_AudioBufferWrapper);
            }

            {
                Function<Ref<AudioFX::AudioDevice>(const String& _Name)> _AudioDevice = [](const String& _Name) { return CreateRef<OpenALDevice>(_Name); };
                auto _AudioDeviceBind = std::bind(_AudioDevice, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioDevice> _AudioDeviceWrapper;
                _AudioDeviceWrapper.Bind<decltype(_AudioDeviceBind), const String&>(_AudioDeviceBind);
                AudioFX::AudioDevice::PushWrapper(_AudioDeviceWrapper);
            }

            {
                Function<Ref<AudioFX::AudioListener>(const Mathematics::Transform& _Transform)> _AudioListener = [](const Mathematics::Transform& _Transform) { return CreateRef<OpenALListener>(_Transform); };
                auto _AudioListenerBind = std::bind(_AudioListener, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioListener> _AudioListenerWrapper;
                _AudioListenerWrapper.Bind<decltype(_AudioListenerBind), const Mathematics::Transform&>(_AudioListenerBind);
                AudioFX::AudioListener::PushWrapper(_AudioListenerWrapper);
            }

            {
                Function<Ref<AudioFX::AudioSource>(const Mathematics::Transform& _Transform)> _AudioSource = [](const Mathematics::Transform& _Transform) { return CreateRef<OpenALSource>(_Transform); };
                auto _AudioSourceBind = std::bind(_AudioSource, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioSource> _AudioSourceWrapper;
                _AudioSourceWrapper.Bind<decltype(_AudioSourceBind), const Mathematics::Transform&>(_AudioSourceBind);
                AudioFX::AudioSource::PushWrapper(_AudioSourceWrapper);
            }

            m_Initialized = true;
        }

        if (!_Event.Handled) return;
    }

}