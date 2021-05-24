#include "OpenALBuffer.h"

#include "AL/al.h"
#include "AL/alext.h"
#include "alc/alcmain.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"
#include "minimp3_ex.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

namespace OpenAL {

	static mp3dec_t* s_MP3Device = nullptr;

	static ALenum GetOpenALFormat(uint32_t channels)
	{
		// Note: sample size is always 2 bytes (16-bits) with
		// both the .mp3 and .ogg decoders that we're using
		switch (channels)
		{
		case 1:  return AL_FORMAT_MONO16;
		case 2:  return AL_FORMAT_STEREO16;
		}
		// assert
		return 0;
	}

	OpenALBuffer::OpenALBuffer(const String& _Filepath)
	{
		if (s_MP3Device == nullptr) {
			s_MP3Device = new mp3dec_t();
			mp3dec_init(s_MP3Device);
		}

		alGenBuffers(1, &m_Buffer);

		std::filesystem::path path = _Filepath;
		std::string extension = path.extension().string();

		if (extension == ".ogg")
			LoadAudioSourceOgg(_Filepath);
		if (extension == ".mp3")
			LoadAudioSourceMP3(_Filepath);
	}

	OpenALBuffer::~OpenALBuffer()
	{
		alDeleteBuffers(1, &m_Buffer);
	}

	void OpenALBuffer::Bind(const uint32_t& _SourceHandle)
	{
		alSourcei(_SourceHandle, AL_BUFFER, m_Buffer);
	}

	void OpenALBuffer::LoadAudioSourceOgg(const String& _Filename)
	{

	}

	void OpenALBuffer::LoadAudioSourceMP3(const String& _Filename)
	{
		mp3dec_file_info_t info;
		int loadResult = mp3dec_load(s_MP3Device, _Filename.c_str(), &info, NULL, NULL);
		uint32_t size = info.samples * sizeof(mp3d_sample_t);

		auto sampleRate = info.hz;
		auto channels = info.channels;
		auto alFormat = GetOpenALFormat(channels);
		float lengthSeconds = size / (info.avg_bitrate_kbps * 1024.0f);
		alBufferData(m_Buffer, alFormat, info.buffer, size, sampleRate);

		if (alGetError() != AL_NO_ERROR) std::cout << "Failed to setup sound source" << std::endl;
	}
}