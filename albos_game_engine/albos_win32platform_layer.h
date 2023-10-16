#if !defined(ALBOS_WIN32PLATFORM_LAYER_H)

struct win32_backbuffer {
  BITMAPINFO Info;
  void* Memory;
  int Width;
  int Height;
  int BytesPerPixel;
  int Pitch;
};


struct win32_window_dimension {
  int Width;
  int Height;
};


struct win32_sound_output {
  int SamplesPerSecond;
  uint32 RunningSampleIndex;
  int WavePeriod;
  int BytesPerSample;
  int SecondaryBufferSize;
  real32 tSine;
  int LatencySampleCount;
};


typedef struct platform_window {
  HWND Handle;
}platform_window;

typedef struct platform_sound_device {
  win32_sound_output Handle;
  game_sound_ouput_buffer Buffer;
  DWORD ByteToLock;
  DWORD BytesToWrite;
} platform_sound_device;

typedef struct platform_input_device {
  XINPUT_STATE Handle;
} platform_input_device;


#define ALBOS_WIN32PLATFORM_LAYER_H
#endif
