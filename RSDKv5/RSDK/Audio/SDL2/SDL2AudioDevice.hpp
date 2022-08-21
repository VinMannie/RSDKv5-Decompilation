#define LockAudioDevice()   SDL_LockAudio()
#define UnlockAudioDevice() SDL_UnlockAudio()

namespace RSDK
{
class AudioDevice : public AudioDeviceBase
{
public:
    static bool32 Init();
    static void Release();

    static void ProcessAudioMixing(void *stream, int32 length);

    static void FrameInit() {}

    inline static void HandleStreamLoad(ChannelInfo *channel, bool32 async)
    {
        // haha i will maliciously disable threading for web users just to piss them off with stutters
        // (just kidding it's because threads don't exist in js) 
        #ifndef __EMSCRIPTEN__
        if (async)
            SDL_CreateThread((SDL_ThreadFunction)LoadStream, "LoadStream", (void *)channel);
        else
        #endif
            LoadStream(channel);
    }

private:
    static SDL_AudioDeviceID device;
    static SDL_AudioSpec deviceSpec;

    static uint8 contextInitialized;

    static void InitAudioChannels();
    static void InitMixBuffer() {}

    static void AudioCallback(void *data, uint8 *stream, int32 len);
};
} // namespace RSDK