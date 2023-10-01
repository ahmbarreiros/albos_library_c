// NOTE: Bibliotecas incluídas - Futuramente o objetivo é remover a maior parte dessas
#include <windows.h>
#include <stdint.h>
#include <xinput.h>
#include <dsound.h>
#include <math.h>

// NOTE: Formas especificadas para keyword static
#define  global_variable static // Váriaveis inicializadas com 0
#define  internal static // Funções internas para o arquivo
#define  local_variable static // Inicializada apenas na primeira vez tipada

// NOTE: Constantes
#define PI32 3.14159265359f

// NOTE: Tipos padronizados
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;


typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

// NOTE: Suporte para funções do xInput XInputGetState e XInputSetState
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE* pState)
#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)

typedef X_INPUT_GET_STATE(x_input_get_state);
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_GET_STATE(XInputGetStateStub) {
  return 0;
};

X_INPUT_SET_STATE(XInputSetStateStub) {
  return 0;
};

global_variable x_input_get_state *XInputGetState_ = XInputGetStateStub;
global_variable x_input_set_state *XInputSetState_ = XInputSetStateStub;

#define  XInputGetState XInputGetState_
#define  XInputSetState XInputSetState_

// NOTE: Suporte para função do dSound DirectSoundCreate
#define DIRECT_SOUND_CREATE(name) HRESULT WINAPI name(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
typedef DIRECT_SOUND_CREATE(direct_sound_create);

struct win32_backbuffer {
  void * Memory;
  BITMAPINFO Info;
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
  int ToneHz;
  int16 ToneVolume;
  uint32 RunningSampleIndex;
  int WavePeriod;
  int BytesPerSample;
  int SecondaryBufferSize;
  real32 tSine;
  int LatencySampleCount;
};

// NOTE: Váriaveis globais 
global_variable real32 GlobalRunning;

global_variable win32_backbuffer GlobalBackbuffer;
global_variable LPDIRECTSOUNDBUFFER GlobalSecondaryBuffer;

internal void RenderGradient(win32_backbuffer Buffer, int BlueOffset, int GreenOffset) {
  uint8 *Row = (uint8*) Buffer.Memory;
  for(int Y = 0; Y < Buffer.Height; Y++) {
    uint32 *Pixel = (uint32 *) Row;
    for(int X = 0; X < Buffer.Width; X++) {
      uint8 Blue = X + BlueOffset;
      uint8 Green = Y + GreenOffset;
      uint8 Red = 255;
      *Pixel++ = ((Red << 16)|(Green << 8)|Blue);
    }
    Row += Buffer.Pitch;
  }
}

internal void Win32LoadXInput() {

  HMODULE XInputLibrary = LoadLibrary("xinput1_4.dll");

  if(!XInputLibrary) {
    XInputLibrary = LoadLibrary("xinput9_1_0.dll");
  }
  if(!XInputLibrary) {
    XInputLibrary = LoadLibrary("xinput1_3.dll");
  }
  if(XInputLibrary) {
    XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
    if(!XInputGetState) {
      XInputGetState = XInputGetStateStub;
    }
    XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
    if(!XInputSetState) {
      XInputSetState = XInputSetStateStub;
    }
  } else {
    // TODO: NO XINPUTLIB   
  }
}

internal void Win32InitDSound(HWND Window, int32 SamplesPerSecond, int32 BufferSize) {
  HMODULE DSoundLibrary = LoadLibrary("dsound.dll");
  if(DSoundLibrary) {
    direct_sound_create *DirectSoundCreate = (direct_sound_create *)GetProcAddress(DSoundLibrary, "DirectSoundCreate");
    LPDIRECTSOUND DirectSound;
    if(DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &DirectSound, 0))) {
      WAVEFORMATEX WaveFormat = {};

      WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
      WaveFormat.nChannels = 2;
      WaveFormat.nSamplesPerSec = SamplesPerSecond;
      WaveFormat.wBitsPerSample = 16;
      WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
      WaveFormat.nAvgBytesPerSec = (WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign);
      WaveFormat.cbSize = 0;
      
      if(SUCCEEDED(DirectSound->SetCooperativeLevel(Window, DSSCL_PRIORITY))) {
	LPDIRECTSOUNDBUFFER PrimaryBuffer;
	DSBUFFERDESC BufferDescription = {};
	
	BufferDescription.dwSize = sizeof(BufferDescription);
	BufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

	if(SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription, &PrimaryBuffer, 0))) {
	  if(SUCCEEDED(PrimaryBuffer->SetFormat(&WaveFormat))) {
	    OutputDebugStringA("Primary Buffer");
	  } else {
	    // TODO: PRIMARY BUFFER FORMAT NOT SET
	  }
	} else {
	  // TODO: PRIMARY BUFFER NOT CREATED
	}
      } else {
	// TODO: DSOUND COOPERATIVE LEVEL NOT SET
      }
      
      DSBUFFERDESC BufferDescription = {};
	
      BufferDescription.dwSize = sizeof(BufferDescription);
      BufferDescription.dwFlags = 0;
      BufferDescription.dwBufferBytes = BufferSize;
      BufferDescription.lpwfxFormat = &WaveFormat;

      if(SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription, &GlobalSecondaryBuffer, 0))) {
	OutputDebugStringA("Secondary Buffer");
      } else {
	// TODO: SECONDARY BUFFER NOT CREATED
      }
    } else {
      // TODO: DSOUND NOT CREATED
    }
  } else {
    // TODO: DSOUNDLIB NOT SET
  } 
}

internal win32_window_dimension Win32GetWindowDimension(HWND Window) {
  win32_window_dimension Result;
  RECT ClientRect;
  GetClientRect(Window, &ClientRect);
  Result.Width = ClientRect.right - ClientRect.left;
  Result.Height = ClientRect.bottom - ClientRect.top;
  return Result;
}

internal void Win32ResizeDIBSection(win32_backbuffer *Buffer, int Width, int Height) {

  if(Buffer->Memory) {
    VirtualFree(
		Buffer->Memory,
		0,
		MEM_RELEASE
		);
  }

  Buffer->Width = Width;
  Buffer->Height = Height;
  
  Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
  Buffer->Info.bmiHeader.biWidth = Buffer->Width;
  Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
  Buffer->Info.bmiHeader.biPlanes = 1;
  Buffer->Info.bmiHeader.biBitCount = 32;
  Buffer->Info.bmiHeader.biCompression = BI_RGB;

  Buffer->BytesPerPixel = 4;
  int BitmapMemorySize = (Buffer->Width * Buffer->Height) * Buffer->BytesPerPixel;
  Buffer->Memory = VirtualAlloc(
				0,
				BitmapMemorySize,
				MEM_COMMIT|MEM_RESERVE,
				PAGE_READWRITE
				);
  Buffer->Pitch = Buffer->Width * Buffer->BytesPerPixel;
  //RenderGradient(*Buffer, 0, 0);
}

internal void Win32DisplayBufferInWindow(win32_backbuffer* Buffer,
				HDC DeviceContext,
				int WindowWidth,
				int WindowHeight
				) {
  StretchDIBits(
		DeviceContext,
		0, 0, WindowWidth, WindowHeight,
		0, 0, Buffer->Width, Buffer->Height,
		Buffer->Memory,
		&Buffer->Info,
		DIB_RGB_COLORS,
		SRCCOPY
		);
}

LRESULT CALLBACK Win32Wndproc(
			      HWND Window,
			      UINT Message,
			      WPARAM wParam,
			      LPARAM lParam
			      ) {
  LRESULT Result = 0;
  switch(Message) {
  case WM_CLOSE:
    {
      DestroyWindow(Window);
      GlobalRunning = false;
      OutputDebugStringA("WM_CLOSE\n");
    } break;
  case WM_DESTROY:
    {
      PostQuitMessage(0);
      GlobalRunning = false;
      OutputDebugStringA("WM_DESTROY\n");
    } break;
  case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
  case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    } break;
  case WM_SYSKEYDOWN:
  case WM_SYSKEYUP:
  case WM_KEYDOWN:
  case WM_KEYUP:
    {
      uint32 VKCode = wParam;
      real32 WasDown = ((lParam & (1 << 30)) != 0);
      real32 IsDown = ((lParam & (1 << 31)) == 0);
      if(WasDown != IsDown) {
	if(VKCode == 'W') {
	  OutputDebugStringA("W\n");
	} else if(VKCode == 'A') {
	  OutputDebugStringA("A\n");
	} else if(VKCode == 'S') {
	  OutputDebugStringA("S\n");
	} else if(VKCode == 'D') {
	  OutputDebugStringA("D\n");
	} else if(VKCode == 'Q') {
	  OutputDebugStringA("Q\n");
	} else if(VKCode == 'E') {
	  OutputDebugStringA("E\n");
	} else if(VKCode == VK_UP) {
	  OutputDebugStringA("UP\n");
	} else if(VKCode == VK_LEFT) {
	  OutputDebugStringA("LEFT\n");
	} else if(VKCode == VK_DOWN) {
	  OutputDebugStringA("DOWN\n");
	} else if(VKCode == VK_RIGHT) {
	  OutputDebugStringA("RIGHT\n");
	} else if(VKCode == VK_ESCAPE) {
	  OutputDebugStringA("Escape: ");
	  if(IsDown) {
	    OutputDebugStringA("IsDown ");
	  }
	  if(WasDown) {
	    OutputDebugStringA("WasDown ");
	  }
	  
	  OutputDebugStringA("\n");
	}else if(VKCode == VK_SPACE) {
	  OutputDebugStringA("space\n");
	}
      }
      real32 AltKeyWasDown = (lParam & (1 << 29));
      if(AltKeyWasDown && VKCode == VK_F4) {
	GlobalRunning = false;
      }
    } break;
  case WM_PAINT:
    {

      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      win32_window_dimension Dimension = Win32GetWindowDimension(Window);
      Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext, Dimension.Width, Dimension.Height);
      EndPaint(Window, &Paint);
      OutputDebugStringA("WM_PAINT\n");     
    } break;
  default:
    {
      OutputDebugStringA("DEFAULT\n");
      Result = DefWindowProc(Window, Message, wParam, lParam);
    } break;
  }
  return Result;
}

internal void Win32FillSoundBuffer(win32_sound_output* SoundOutput,
				   DWORD ByteToLock,
				   DWORD BytesToWrite) {
  VOID *Region1;
  DWORD Region1Size;
  VOID *Region2;
  DWORD Region2Size;

  if(SUCCEEDED(GlobalSecondaryBuffer->Lock(ByteToLock,
					   BytesToWrite,
					   &Region1,
					   &Region1Size,
					   &Region2,
					   &Region2Size,
					   0))) {
    int16 *SampleOut = (int16 *)Region1;
    DWORD Region1SampleCount = Region1Size / SoundOutput->BytesPerSample;
    for(DWORD SampleIndex = 0; SampleIndex < Region1SampleCount; SampleIndex++) {
      real32 SineValue = sinf(SoundOutput->tSine);
      int16 SampleValue = (int16)(SineValue * SoundOutput->ToneVolume);
      *SampleOut++ = SampleValue;
      *SampleOut++ = SampleValue;

      SoundOutput->tSine += (2.0f * PI32 * 1.0f) / (real32)SoundOutput->WavePeriod;
      ++SoundOutput->RunningSampleIndex;
    }
    DWORD Region2SampleCount = Region2Size / SoundOutput->BytesPerSample;
    SampleOut = (int16 *)Region2;
    for(DWORD SampleIndex = 0; SampleIndex < Region2SampleCount; SampleIndex++) {
      real32 SineValue = sinf(SoundOutput->tSine);
      int16 SampleValue = (int16)(SineValue * SoundOutput->ToneVolume);
      *SampleOut++ = SampleValue;
      *SampleOut++ = SampleValue;

      SoundOutput->tSine += (2.0f * PI32 * 1.0f) / (real32)SoundOutput->WavePeriod;
      ++SoundOutput->RunningSampleIndex;
    }

    GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
  }
}

int WINAPI WinMain(
		   HINSTANCE Instance,
		   HINSTANCE PrevInstance,
		   LPSTR     CmdLine,
		   int       ShowCmd
		   ) {
  WNDCLASSA WindowClass = {};

  Win32ResizeDIBSection(&GlobalBackbuffer, 1280, 720);
  
  WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
  WindowClass.lpfnWndProc = Win32Wndproc;
  WindowClass.hInstance = Instance;
  WindowClass.lpszClassName = "WindowClass";

  if(RegisterClassA(&WindowClass)) {
    HWND Window = CreateWindowExA(
			     0,
			     WindowClass.lpszClassName,
			     "Platform Layer",
			     WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			     CW_USEDEFAULT,
			     CW_USEDEFAULT,
			     CW_USEDEFAULT,
			     CW_USEDEFAULT,
			     0,
			     0,
			     Instance,
			     0
			     );
    if(Window) {
      
      HDC DeviceContext = GetDC(Window);
      
      int XOffset = 0;
      int YOffset = 0;

      win32_sound_output SoundOutput = {};
      SoundOutput.SamplesPerSecond = 40000;
      SoundOutput.ToneHz = 256;
      SoundOutput.ToneVolume = 200;
      SoundOutput.RunningSampleIndex = 0;
      SoundOutput.WavePeriod = SoundOutput.SamplesPerSecond / SoundOutput.ToneHz;
      SoundOutput.BytesPerSample = sizeof(int16) * 2;
      SoundOutput.SecondaryBufferSize = SoundOutput.SamplesPerSecond * SoundOutput.BytesPerSample;
      SoundOutput.LatencySampleCount = SoundOutput.SamplesPerSecond / 15;
      Win32InitDSound(Window, SoundOutput.SamplesPerSecond, SoundOutput.SecondaryBufferSize);
      Win32FillSoundBuffer(&SoundOutput, 0, SoundOutput.SecondaryBufferSize);
      GlobalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

      GlobalRunning = true;
      while(GlobalRunning) {
	MSG Message;
	
	// TODO: CHECK IF WINDOW OR 0
	while(PeekMessageA(&Message, Window, 0, 0, PM_REMOVE)) { 
	  if(Message.message == WM_QUIT) {
	    GlobalRunning = false;
	  }

	  for(DWORD ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ControllerIndex++) { 
	    XINPUT_STATE ControllerState;
	    ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));

	    if(XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS) {
	      // NOTE: Controller available
	      // TODO: Check if its better creating a pointer to ControllerState.Gamepad
	      XINPUT_GAMEPAD Pad = ControllerState.Gamepad;
	      
	      real32 Up = (Pad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	      real32 Right = (Pad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	      real32 Down = (Pad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	      real32 Left = (Pad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	      real32 Start = (Pad.wButtons & XINPUT_GAMEPAD_START);
	      real32 Back = (Pad.wButtons & XINPUT_GAMEPAD_BACK);
	      real32 LeftShoulder = (Pad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	      real32 RightShoulder = (Pad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	      real32 AButton = (Pad.wButtons & XINPUT_GAMEPAD_A);
	      real32 BButton = (Pad.wButtons & XINPUT_GAMEPAD_B);
	      real32 XButton = (Pad.wButtons & XINPUT_GAMEPAD_X);
	      real32 YButton = (Pad.wButtons & XINPUT_GAMEPAD_Y);

	      int16 ThumbX = Pad.sThumbLX;
	      int16 ThumbY = Pad.sThumbLY;
	      
	      YOffset += ThumbY / 4096;
	      XOffset += ThumbX / 4096;;

	      SoundOutput.ToneHz = 512 + (int)(256.0f*((real32)ThumbY / 30000.0f));
	      SoundOutput.WavePeriod = SoundOutput.SamplesPerSecond / SoundOutput.ToneHz;
	      
	    } else {
	      // TODO: Controller not available
	    }
	  }
	  
	  TranslateMessage(&Message);
	  DispatchMessage(&Message);

	  DWORD PlayCursor;
	  DWORD WriteCursor;
	  if(SUCCEEDED(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor,
								 &WriteCursor))) {
	    DWORD ByteToLock = (SoundOutput.RunningSampleIndex * SoundOutput.BytesPerSample) % SoundOutput.SecondaryBufferSize;
	    DWORD TargetCursor = ((PlayCursor + (SoundOutput.LatencySampleCount * SoundOutput.BytesPerSample)) % SoundOutput.SecondaryBufferSize);
	    DWORD BytesToWrite;
	    if(ByteToLock > TargetCursor) {
	      BytesToWrite = SoundOutput.SecondaryBufferSize - ByteToLock;
	      BytesToWrite += TargetCursor;
	    } else {
	      BytesToWrite = TargetCursor - ByteToLock;
	    }
	    Win32FillSoundBuffer(&SoundOutput, ByteToLock, BytesToWrite);
	  }
	}
	win32_window_dimension Dimension = Win32GetWindowDimension(Window);
	Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext, Dimension.Width, Dimension.Height);
	RenderGradient(GlobalBackbuffer, XOffset, YOffset);
	++XOffset;
	++YOffset;
      }
    }
  }
  
  return 0;
}
