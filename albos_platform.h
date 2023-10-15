#if !defined(ALBOS_PLATFORM_H)

typedef struct platform_window platform_window;
platform_window *PlatformOpenWindow(char* Title,
				    int Width,
				    int Height);
void PlatformCloseWindow(platform_window *Window);

typedef struct platform_sound_device platform_sound_device;
platform_sound_device *PlatformOpenSoundDevice(int Volume, platform_window *Window);
void PlatformPlaySoundDevice();
void PlatformCloseSoundDevice(platform_sound_device *SoundDevice);

#define ALBOS_PLATFORM_H
#endif
