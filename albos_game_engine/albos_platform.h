#if !defined(ALBOS_PLATFORM_H)


struct game_sound_ouput_buffer {
  int16* Samples;
  int16 SampleCount;
  int16 SamplesPerSecond;
};

struct game_offscreen_buffer {
  void* Memory;
  int Width;
  int Height;
  int Pitch;
};


struct game_button_state {
  
}


typedef struct platform_window platform_window;
platform_window *PlatformOpenWindow(char* Title,
				    int Width,
				    int Height);
void PlatformCloseWindow(platform_window *Window);

typedef struct platform_sound_device platform_sound_device;
platform_sound_device *PlatformOpenSoundDevice(platform_window *Window, int Volume);
void PlatformPlaySoundDevice();
void PlatformCloseSoundDevice(platform_sound_device *SoundDevice);

typedef struct platform_input_device platform_input_device;


internal void GameUpdateAndRender(game_offscreen_buffer *BitMapBuffer,
				  game_sound_ouput_buffer *SoundBuffer);

#define ALBOS_PLATFORM_H
#endif
