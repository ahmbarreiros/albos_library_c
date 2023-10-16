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

internal void GameUpdateAndRender(game_input *Input,
				  game_offscreen_buffer *BitMapBuffer,
				  game_sound_ouput_buffer *SoundBuffer) {
  local_persist int BlueOffset = 0;
  local_persist int GreenOffset = 0;
  local_persist int ToneHz = 256;

  game_controller_input *Input0 = &Input->Controllers[0];

  if(Input0->IsAnalog) {
    // NOTE: Analog tuning
    BlueOffset += (int)4.0f*(Input0->EndX);
    ToneHz = 256 + (int)(128.0f*(Input0->EndY));
  } else {
    // NOTE: Digital tuning
  }

  if(Input0->Down.EndedDown) {
    GreenOffset++;
  }
  
  RenderGradient(BitMapBuffer, BlueOffset, GreenOffset);
  GameOutputSound(SoundBuffer, ToneHz);
}

