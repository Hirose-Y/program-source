#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include "Sound/SoundBuffer.h"
#include <iostream>
#include <cstdint>

ALuint SoundBuffer::LoadWavToBuffer(const std::string& filename) {
    unsigned int channels;
    unsigned int sampleRate;
    drwav_uint64 totalPCMFrameCount;
    int16_t* pcmData = drwav_open_file_and_read_pcm_frames_s16(
        filename.c_str(), &channels, &sampleRate, &totalPCMFrameCount, nullptr);

    if (!pcmData) {
        std::cerr << "Failed to load WAV file: " << filename << std::endl;
        return 0;
    }

    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 :
                    (channels == 2) ? AL_FORMAT_STEREO16 : 0;
    if (format == 0) {
        std::cerr << "Unsupported channel count: " << channels << std::endl;
        drwav_free(pcmData, nullptr);
        return 0;
    }

    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, pcmData, static_cast<ALsizei>(totalPCMFrameCount * channels * sizeof(int16_t)), sampleRate);
    drwav_free(pcmData, nullptr);
    return buffer;
}
