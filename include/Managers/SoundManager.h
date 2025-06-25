#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <memory>

class AudioEngine;

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    bool Initialize();
    
    void PlaySE(const std::string& name);
    void PlayBGM(const std::string& name);
    void StopBGM();

    void SetMasterVolume(float volume);

private:
    std::unique_ptr<AudioEngine> engine;
    std::string currentBGM;
};

#endif /* SOUNDMANAGER_H */
