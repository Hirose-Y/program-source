#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include <AL/al.h>
#include <string>

class SoundBuffer
{
public:
    // OpenALバッファの作成
    static ALuint LoadWavToBuffer(const std::string& filename);
};

#endif /* SOUNDBUFFER_H */
