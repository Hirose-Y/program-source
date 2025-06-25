#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include <AL/al.h>

class SoundSource
{
public:
    SoundSource();
    ~SoundSource();

    void Play(ALuint buffer);
    void Stop();
    void SetLooping(bool loop);
    void SetPosition(float x, float y, float z);
    void SetGain(float gain);

    bool IsPlaying() const;

private:
    ALuint source;
};

#endif /* SOUNDSOURCE_H */
