#include "Managers/SoundManager.h"
#include "Sound/AudioEngine.h"

SoundManager::SoundManager()
: engine(std::make_unique<AudioEngine>())
{

}

SoundManager::~SoundManager()
{
    engine->Shutdown();
}

bool SoundManager::Initialize()
{
    if(!engine->Init()) return false;

    return true;
}

void SoundManager::PlaySE(const std::string& name) {
    engine->PlaySound("Assets/SE/" + name);
}

void SoundManager::PlayBGM(const std::string& name) {
    currentBGM = name;
    engine->PlaySound("Assets/BGM/" + name); // 今はPlaySoundで仮対応
}

void SoundManager::StopBGM() {
    // 必要ならAudioEngine側にStop機能追加
}

void SoundManager::SetMasterVolume(float volume) {
    // AudioEngineにSetMasterVolume()があればラップ
}
