#include "albos_platform.h"


internal void GameOutputSound(game_sound_ouput_buffer *Buffer, int16 ToneHz) {
  local_persist real32 tSine;
  int16 ToneVolume = 300;
  int WavePeriod = Buffer->SamplesPerSecond / ToneHz;
  int16 *SampleOut = Buffer->Samples;
  for(int SampleIndex = 0; SampleIndex < Buffer->SampleCount; SampleIndex++) {
    real32 SineValue = sinf(tSine);
    int16 SampleValue = (int16)(SineValue * ToneVolume);
    *SampleOut++ = SampleValue;
    *SampleOut++ = SampleValue;

    tSine += (2.0f * PI32 * 1.0f) / (real32)WavePeriod;
  }
}

internal void RenderGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset) {
  uint8 *Row = (uint8*) Buffer->Memory;
  for(int Y = 0; Y < Buffer->Height; Y++) {
    uint32 *Pixel = (uint32 *) Row;
    for(int X = 0; X < Buffer->Width; X++) {
      uint8 Blue = X + BlueOffset;
      uint8 Green = Y + GreenOffset;
      uint8 Red = 255;
      *Pixel++ = ((Red << 16)|(Green << 8)|Blue);
    }
    Row += Buffer->Pitch;
  }
}

internal void GameUpdateAndRender(game_offscreen_buffer *BitMapBuffer,
				  game_sound_ouput_buffer *SoundBuffer) {
  local_persist int BlueOffset = 0;
  local_persist int GreenOffset = 0;
  local_persist int ToneHz = 256;
  RenderGradient(BitMapBuffer, BlueOffset, GreenOffset);
  ++BlueOffset;
  ++GreenOffset;
  GameOutputSound(SoundBuffer, ToneHz);
}

