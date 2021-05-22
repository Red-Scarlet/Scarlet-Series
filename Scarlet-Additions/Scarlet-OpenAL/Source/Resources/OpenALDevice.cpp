#include "OpenALDevice.h"

namespace OpenAL {

	OpenALDevice::OpenALDevice(const String& _Name)
	{
		m_Device = alcOpenDevice(nullptr); // nullptr = get default device
		if (!m_Device)
			throw("failed to get sound device");

		m_Context = alcCreateContext(m_Device, nullptr);  // create context
		if (!m_Context)
			throw("Failed to set sound context");

		if (!alcMakeContextCurrent(m_Context))   // make context current
			throw("failed to make context current");

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(m_Device, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(m_Device, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(m_Device) != AL_NO_ERROR)
			name = alcGetString(m_Device, ALC_DEVICE_SPECIFIER);
		printf("Opened \"%s\"\n", name);
	}

	OpenALDevice::~OpenALDevice()
	{
		if (!alcMakeContextCurrent(nullptr))
			throw("failed to set context to nullptr");

		alcDestroyContext(m_Context);
		if (m_Context)
			throw("failed to unset during close");

		if (!alcCloseDevice(m_Device))
			throw("failed to close sound device");
	}
}