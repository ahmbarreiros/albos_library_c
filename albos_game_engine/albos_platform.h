#if !defined(ALBOS_PLATFORM_H)
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

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
  int HalfTransitionCount;
  bool32 EndedDown;
};

struct game_controller_input {
  bool32 IsAnalog;

  real32 StartX;
  real32 MaxX;
  real32 MinX;
  real32 EndX;

  real32 StartY;
  real32 MaxY;
  real32 MinY;
  real32 EndY;

  union {
    game_button_state Buttons[12];
    struct {
      game_button_state Up;
      game_button_state Down;
      game_button_state Left;
      game_button_state Right;
      game_button_state Start;
      game_button_state Back;
      game_button_state LeftShoulder;
      game_button_state RightShoulder;
    };
  };
};

struct game_input {
  game_controller_input Controllers[8];
};


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


internal void GameUpdateAndRender(game_input *Input,
				  game_offscreen_buffer *BitMapBuffer,
				  game_sound_ouput_buffer *SoundBuffer);

#define ALBOS_PLATFORM_H
#endif
