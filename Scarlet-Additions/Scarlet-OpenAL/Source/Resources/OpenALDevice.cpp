#include "OpenALDevice.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <thread>
#include <filesystem>

#include "common/albyte.h"

#include "AL/al.h"
#include "AL/alext.h"
#include "alc/alcmain.h"
#include "alhelpers.h"

#include "Vorbis/codec.h"
#include "Vorbis/vorbisfile.h"

namespace OpenAL {

	OpenALDevice::OpenALDevice(const String& _Name)
	{
		if (InitAL(m_Device, nullptr, 0) != 0)
			std::cout << "Audio device error!\n";

		std::cout << "Audio Device Info:" << std::endl;
		std::cout << "Name: " << m_Device->DeviceName << std::endl;
		std::cout << "Sample Rate: " << m_Device->Frequency << std::endl;
		std::cout << "Max Sources: " << m_Device->SourcesMax << std::endl;
		std::cout << "Mono: " << m_Device->NumMonoSources << std::endl;
		std::cout << "Stereo: " << m_Device->NumStereoSources << std::endl;
	}

	OpenALDevice::~OpenALDevice()
	{
		CloseAL();
	}

	void OpenALDevice::Play(const uint32& _SourceHandle)
	{
		alSourcePlay(_SourceHandle);
	}
}