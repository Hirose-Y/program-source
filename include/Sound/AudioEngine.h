#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Sound/SoundSource.h"

class SoundBuffer;

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    // 初期化
    bool Init();

    // 破棄
    void Shutdown();

    void Update();

    // リスナーの位置を設定（3D音響用）
    void SetListenerPosition(float x, float y, float z);

    // リスナーの向きを設定（3D音響用）
    // at = 前方向, up = 上方向
    void SetListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ);

    // WAVファイルを読み込んで OpenAL バッファに変換
    // 同じファイルはキャッシュして再利用する
    ALuint LoadSound(const std::string& filename);

    // 指定された音声ファイルを一度だけ再生する
    void PlaySound(const std::string& filename);

private:
    std::unique_ptr<ALCdevice, decltype(&alcCloseDevice)> device;
    std::unique_ptr<ALCcontext, decltype(&alcDestroyContext)> context;
    std::map<std::string, ALuint> buffers;
    std::vector<std::unique_ptr<SoundSource>> activeSources;
};

#endif /* AUDIOENGINE_H */
