#include "Sound/AudioEngine.h"
#include <iostream>
#include <algorithm>
#include <thread>

#include "Sound/SoundBuffer.h"
#include "Sound/SoundSource.h"

AudioEngine::AudioEngine()
: device(nullptr, alcCloseDevice), context(nullptr, alcDestroyContext)
{

}

AudioEngine::~AudioEngine()
{
    Shutdown();
}

bool AudioEngine::Init()
{
    // デフォルトデバイス（音の出力先※スピーカーなど）を開く
    device = std::unique_ptr<ALCdevice, decltype(&alcCloseDevice)>( 
        alcOpenDevice(nullptr), alcCloseDevice );
    if (!device) {
        std::cerr << "Failed to open OpenAL device." << std::endl;
        return false;
    }

    // コンテキスト（再生環境）を作成し、現在の操作対象に設定
    context = std::unique_ptr<ALCcontext, decltype(&alcDestroyContext)>( 
        alcCreateContext(device.get(), nullptr), alcDestroyContext);
    if (!context || !alcMakeContextCurrent(context.get())) {
        std::cerr << "Failed to create or set OpenAL context." << std::endl;
        return false;
    }
    return true;
}

void AudioEngine::Update()
{
    // 再生が終わった SoundSource を削除
    activeSources.erase(
        std::remove_if(activeSources.begin(), activeSources.end(),
            [](const std::unique_ptr<SoundSource>& src) {
                return !src->IsPlaying();
            }),
        activeSources.end());
}

void AudioEngine::Shutdown()
{
    // 読み込んだバッファをすべて削除
    for (auto& [_, buffer] : buffers) {
        alDeleteBuffers(1, &buffer);
    }
    buffers.clear();

    // コンテキストとデバイスを削除
    if (context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context.get());
        context = nullptr;
    }
    if (device) {
        alcCloseDevice(device.get());
        device = nullptr;
    }
}

void AudioEngine::SetListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioEngine::SetListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ)
{
    float orientation[6] = { atX, atY, atZ, upX, upY, upZ };
    alListenerfv(AL_ORIENTATION, orientation);
}

ALuint AudioEngine::LoadSound(const std::string& filename)
{
    // キャッシュの確認
    auto it = buffers.find(filename);
    if (it != buffers.end()) {
        return it->second;
    }

    // 初回の読み込み
    ALuint buffer = SoundBuffer::LoadWavToBuffer(filename);
    if (buffer != 0) {
        buffers[filename] = buffer;
    }
    return buffer;
}

void AudioEngine::PlaySound(const std::string& filename)
{
    ALuint buffer = LoadSound(filename);
    if (buffer == 0) return;

    auto source = std::make_unique<SoundSource>();
    source->Play(buffer);

    // activeSourcesに保持（スコープ外で消えないように）
    activeSources.emplace_back(std::move(source));
}
