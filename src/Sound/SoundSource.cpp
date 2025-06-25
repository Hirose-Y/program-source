#include "Sound/SoundSource.h"

SoundSource::SoundSource() {
    alGenSources(1, &source);
}

SoundSource::~SoundSource() {
    alDeleteSources(1, &source);
}

void SoundSource::Play(ALuint buffer) {
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
}

void SoundSource::Stop() {
    alSourceStop(source);
}

void SoundSource::SetLooping(bool loop) {
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void SoundSource::SetPosition(float x, float y, float z) {
    alSource3f(source, AL_POSITION, x, y, z);
}

void SoundSource::SetGain(float gain) {
    alSourcef(source, AL_GAIN, gain);
}

bool SoundSource::IsPlaying() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}
