#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	enum class SCARLET_INTERFACE_API AudioFileFormat
	{
		AudioNone = 0, AudioOgg, AudioMP3
	};

	class SCARLET_INTERFACE_API OpenALBuffer : public AudioFX::AudioBuffer
	{
	public:
		OpenALBuffer(const String& _Filepath);
		~OpenALBuffer();

		virtual void Bind(const uint32_t& _SourceHandle) override;

	private:
		void LoadAudioSourceOgg(const String& _Filename);
		void LoadAudioSourceMP3(const String& _Filename);

	private:
		uint32 m_Buffer = 0;
	};


}