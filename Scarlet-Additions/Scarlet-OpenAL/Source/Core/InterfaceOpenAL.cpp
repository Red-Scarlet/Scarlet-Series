#include "InterfaceOpenAL.h"
#include <ScarletAudioFX.h>

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
            
            AudioFX::AudioBufferCallback = AudioFX::CallbackTable<AudioFX::AudioBuffer>::Create();
            {
                Function<Ref<AudioFX::AudioBuffer>(const String& _Name)> _AudioBuffer = [](const String& _Name) { return CreateRef<OpenALBuffer>(_Name); };
                auto _AudioBufferBind = std::bind(_AudioBuffer, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioBuffer> _AudioBufferWrapper;
                _AudioBufferWrapper.Bind<decltype(_AudioBufferBind), const String&>(_AudioBufferBind);
                AudioFX::AudioBufferCallback->Push(_AudioBufferWrapper);
            }

            AudioFX::AudioDeviceCallback = AudioFX::CallbackTable<AudioFX::AudioDevice>::Create();
            {
                Function<Ref<AudioFX::AudioDevice>(const String& _Name)> _AudioDevice = [](const String& _Name) { return CreateRef<OpenALDevice>(_Name); };
                auto _AudioDeviceBind = std::bind(_AudioDevice, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioDevice> _AudioDeviceWrapper;
                _AudioDeviceWrapper.Bind<decltype(_AudioDeviceBind), const String&>(_AudioDeviceBind);
                AudioFX::AudioDeviceCallback->Push(_AudioDeviceWrapper);
            }

            AudioFX::AudioListenerCallback = AudioFX::CallbackTable<AudioFX::AudioListener>::Create();
            {
                Function<Ref<AudioFX::AudioListener>(const String& _Name)> _AudioListener = [](const String& _Name) { return CreateRef<OpenALListener>(_Name); };
                auto _AudioListenerBind = std::bind(_AudioListener, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioListener> _AudioListenerWrapper;
                _AudioListenerWrapper.Bind<decltype(_AudioListenerBind), const String&>(_AudioListenerBind);
                AudioFX::AudioListenerCallback->Push(_AudioListenerWrapper);
            }

            AudioFX::AudioSourceCallback = AudioFX::CallbackTable<AudioFX::AudioSource>::Create();
            {
                Function<Ref<AudioFX::AudioSource>(const String& _Name)> _AudioSource = [](const String& _Name) { return CreateRef<OpenALSource>(_Name); };
                auto _AudioSourceBind = std::bind(_AudioSource, std::placeholders::_1);
                AudioFX::CallbackWrapper<AudioFX::AudioSource> _AudioSourceWrapper;
                _AudioSourceWrapper.Bind<decltype(_AudioSourceBind), const String&>(_AudioSourceBind);
                AudioFX::AudioSourceCallback->Push(_AudioSourceWrapper);
            }

            m_Initialized = true;
        }
    }

}