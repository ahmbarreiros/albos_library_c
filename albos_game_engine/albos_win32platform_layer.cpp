#include <stdint.h>
#include <math.h>

// NOTE: Formas especificadas para keyword static
#define  global_variable static // Váriaveis inicializadas com 0
#define  internal static // Funções internas para o arquivo
#define  local_persist static // Inicializada apenas na primeira vez tipada

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

typedef int32 bool32;
// NOTE: Constantes
#define PI32 3.14159265359f


#include "albos_platform.cpp"

// NOTE: Bibliotecas incluídas - Futuramente o objetivo é remover a maior parte dessas
#include <windows.h>
#include <stdlib.h>

#include <xinput.h>
#include <dsound.h>



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

#include "albos_win32platform_layer.h"

// NOTE: Váriaveis globais 
global_variable real32 GlobalRunning;
global_variable HINSTANCE GlobalInstance;
global_variable win32_backbuffer GlobalBackbuffer;
global_variable LPDIRECTSOUNDBUFFER GlobalSecondaryBuffer;



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
				   DWORD BytesToWrite,
				   game_sound_ouput_buffer *SourceBuffer) {
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
    DWORD Region1SampleCount = Region1Size / SoundOutput->BytesPerSample;
    int16 *DestSample = (int16 *)Region1;
    int16 *SourceSample = SourceBuffer->Samples;
    
    for(DWORD SampleIndex = 0; SampleIndex < Region1SampleCount; SampleIndex++) {
      *DestSample++ = *SourceSample++;
      *DestSample++ = *SourceSample++;
      ++SoundOutput->RunningSampleIndex;
    }
    DWORD Region2SampleCount = Region2Size / SoundOutput->BytesPerSample;
    DestSample = (int16 *)Region2;
    for(DWORD SampleIndex = 0; SampleIndex < Region2SampleCount; SampleIndex++) {
      *DestSample++ = *SourceSample++;
      *DestSample++ = *SourceSample++;
      ++SoundOutput->RunningSampleIndex;
    }

    GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
  }
}

internal void Win32ClearBuffer(win32_sound_output *SoundOutput) {
  VOID *Region1;
  DWORD Region1Size;
  VOID *Region2;
  DWORD Region2Size;

  if(SUCCEEDED(GlobalSecondaryBuffer->Lock(0,
					   SoundOutput->SecondaryBufferSize,
					   &Region1,
					   &Region1Size,
					   &Region2,
					   &Region2Size,
					   0))) {
    
    uint8 *DestSample = (uint8 *)Region1;
    
    for(DWORD SampleIndex = 0; SampleIndex < Region1Size; SampleIndex++) {
      *DestSample++ = 0;
    }
    DestSample = (uint8 *)Region2;
    for(DWORD SampleIndex = 0; SampleIndex < Region2Size; SampleIndex++) {
      *DestSample++ = 0;
    }
    GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
  }
}


platform_window* PlatformOpenWindow(char* Title,
				    int Width,
				    int Height) {
  platform_window *Result = (platform_window*)malloc(sizeof(platform_window));
  WNDCLASSA WindowClass = {};
  Win32ResizeDIBSection(&GlobalBackbuffer,
			Width,
			Height);
  
  WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
  WindowClass.lpfnWndProc = Win32Wndproc;
  WindowClass.hInstance = GlobalInstance;
  WindowClass.lpszClassName = "WindowClass";
  
  if(RegisterClassA(&WindowClass)) {
    Result->Handle = CreateWindowExA(
				    0,
				    WindowClass.lpszClassName,
				    Title,
				    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
				    CW_USEDEFAULT,
				    CW_USEDEFAULT,
				    CW_USEDEFAULT,
				    CW_USEDEFAULT,
				    0,
				    0,
				    GlobalInstance,
				    0
				    );
    
  }
  return Result;
}

void PlatformCloseWindow(platform_window *Window) {
  if(Window) {
    DestroyWindow(Window->Handle);
    free(Window);
  }
}

platform_sound_device* PlatformOpenSoundDevice(platform_window *Window) {
  platform_sound_device *Result = (platform_sound_device*)malloc(sizeof(platform_sound_device));
  win32_sound_output SoundOutput = {};
  
  SoundOutput.SamplesPerSecond = 40000;
  SoundOutput.RunningSampleIndex = 0;
  SoundOutput.BytesPerSample = sizeof(int16) * 2;
  SoundOutput.SecondaryBufferSize = SoundOutput.SamplesPerSecond * SoundOutput.BytesPerSample;
  SoundOutput.LatencySampleCount = SoundOutput.SamplesPerSecond / 15;
  
  Win32InitDSound(Window->Handle, SoundOutput.SamplesPerSecond, SoundOutput.SecondaryBufferSize);
  Win32ClearBuffer(&SoundOutput);
  
  GlobalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
  Result->Handle = SoundOutput;

  return Result;
}

void PlatformPlaySoundDevice(platform_sound_device *SoundDevice) {
  Win32FillSoundBuffer(&SoundDevice->Handle, SoundDevice->ByteToLock, SoundDevice->BytesToWrite, &SoundDevice->Buffer);
}

void PlatformCloseSoundDevice(platform_sound_device *SoundDevice) {
  if(SoundDevice) {
    free(SoundDevice);
  }
}

platform_input_device *PlatformOpenInputDevice() {
  platform_input_device *Result = (platform_input_device*)malloc(sizeof(platform_input_device));
  XINPUT_STATE ControllerState;
  ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));
  Result->Handle = ControllerState;
  return Result;
}

void PlatformCloseInput(platform_input_device *InputDevice) {
  if(InputDevice) {
    free(InputDevice);
  }
}

internal void Win32ProccessXInputDigitalButton(DWORD XInputButtonState,
					       game_button_state *OldState,
					       DWORD ButtonBit,
					       game_button_state *NewState) {
  NewState->EndedDown = ((XInputButtonState & ButtonBit) == ButtonBit);
  NewState->HalfTransitionCount = (OldState->EndedDown != NewState->EndedDown) ? 1 : 0;
}

int WINAPI WinMain(
		   HINSTANCE Instance,
		   HINSTANCE PrevInstance,
		   LPSTR     CmdLine,
		   int       ShowCmd
		   ) {
  GlobalInstance = Instance;
  platform_window *Window = PlatformOpenWindow("Platform Layer",
					       1280,
					       720);
  if(Window->Handle) {
    
    HDC DeviceContext = GetDC(Window->Handle);
    platform_sound_device *SoundDevice = PlatformOpenSoundDevice(Window);    
    int16 *Samples = (int16 *)VirtualAlloc(0,
					   40000*2*sizeof(int16),
					   MEM_COMMIT|MEM_RESERVE,
					   PAGE_READWRITE);
    game_input Input[2] = {};
    game_input *NewInput = &Input[0];
    game_input *OldInput = &Input[1];
    
    platform_input_device* InputDevice = PlatformOpenInputDevice();
    
    GlobalRunning = true;
    while(GlobalRunning) {
      MSG Message;
	
      // TODO: CHECK IF WINDOW OR 0
      while(PeekMessageA(&Message, Window->Handle, 0, 0, PM_REMOVE)) { 
	if(Message.message == WM_QUIT) {
	  GlobalRunning = false;
	}
	TranslateMessage(&Message);
	DispatchMessage(&Message);
      }

      int MaxControllerCount = XUSER_MAX_COUNT;
      if(MaxControllerCount > ArrayCount(NewInput->Controllers)) {
	MaxControllerCount = ArrayCount(NewInput->Controllers);
      }
      for(DWORD ControllerIndex = 0; ControllerIndex < MaxControllerCount; ControllerIndex++) {
	game_controller_input *OldController = &OldInput->Controllers[ControllerIndex];
	game_controller_input *NewController = &NewInput->Controllers[ControllerIndex];

	ZeroMemory(&InputDevice->Handle, sizeof(XINPUT_STATE));

	if(XInputGetState(ControllerIndex, &InputDevice->Handle) == ERROR_SUCCESS) {
	  // NOTE: Controller available
	  // TODO: Check if its better creating a pointer to ControllerState.Gamepad
	  XINPUT_GAMEPAD *Pad = &InputDevice->Handle.Gamepad;
	      
	  real32 Up = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
	  real32 Right = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	  real32 Down = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	  real32 Left = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);

	  NewController->IsAnalog = true;
	  NewController->StartX = OldController->EndX;
	  NewController->StartY = OldController->EndY;
	  
	  real32 X;
	  if(Pad->sThumbLX < 0) {
	    X = (real32)Pad->sThumbLX / 32768.0f;
	  } else {
	    X = (real32)Pad->sThumbLX / 32767.0f;
	  }
	  NewController->MinX = NewController->MaxX = NewController->EndX = X;

	  real32 Y;
	  if(Pad->sThumbLY < 0) {
	    Y = (real32)Pad->sThumbLY / 32768.0f;
	  } else {
	    Y = (real32)Pad->sThumbLY / 32767.0f;
	  }
	  NewController->MinY = NewController->MaxY = NewController->EndY = Y;

	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->LeftShoulder,
					   XINPUT_GAMEPAD_LEFT_SHOULDER,
					   &NewController->LeftShoulder);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->RightShoulder,
					   XINPUT_GAMEPAD_RIGHT_SHOULDER,
					   &NewController->RightShoulder);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Down,
					   XINPUT_GAMEPAD_A,
					   &NewController->Down);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Left,
					   XINPUT_GAMEPAD_B,
					   &NewController->Left);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Right,
					   XINPUT_GAMEPAD_X,
					   &NewController->Right);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Up,
					   XINPUT_GAMEPAD_Y,
					   &NewController->Up);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Start,
					   XINPUT_GAMEPAD_START,
					   &NewController->Start);
	  Win32ProccessXInputDigitalButton(Pad->wButtons,
					   &OldController->Back,
					   XINPUT_GAMEPAD_BACK,
					   &NewController->Back);

	} else {
	  // TODO: Controller not available
	}
      }
      DWORD PlayCursor = 0;
      DWORD WriteCursor = 0;
      DWORD BytesToWrite = 0;
      DWORD ByteToLock = 0;
      DWORD TargetCursor = 0;
      bool32 SoundIsValid = false;
      if(SUCCEEDED(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor,
							     &WriteCursor))) {
	ByteToLock = (SoundDevice->Handle.RunningSampleIndex * SoundDevice->Handle.BytesPerSample) % SoundDevice->Handle.SecondaryBufferSize;
	TargetCursor = ((PlayCursor + (SoundDevice->Handle.LatencySampleCount * SoundDevice->Handle.BytesPerSample)) % SoundDevice->Handle.SecondaryBufferSize);
    
	if(ByteToLock > TargetCursor) {
	  BytesToWrite = SoundDevice->Handle.SecondaryBufferSize - ByteToLock;
	  BytesToWrite += TargetCursor;
	} else {
	  BytesToWrite = TargetCursor - ByteToLock;
	}
	SoundIsValid = true;
      }

      SoundDevice->ByteToLock = ByteToLock;
      SoundDevice->BytesToWrite = BytesToWrite;
      SoundDevice->Buffer.SampleCount = SoundDevice->BytesToWrite / SoundDevice->Handle.BytesPerSample;
      SoundDevice->Buffer.Samples = Samples;
      SoundDevice->Buffer.SamplesPerSecond = SoundDevice->Handle.SamplesPerSecond;
	
      game_offscreen_buffer BitMapBuffer = {};
      BitMapBuffer.Memory = GlobalBackbuffer.Memory;
      BitMapBuffer.Width = GlobalBackbuffer.Width;
      BitMapBuffer.Height = GlobalBackbuffer.Height;
      BitMapBuffer.Pitch = GlobalBackbuffer.Pitch;

      GameUpdateAndRender(NewInput, &BitMapBuffer, &SoundDevice->Buffer);

      // TODO: Sound is with a little bit of delay when tabbing?
      if(SoundIsValid) {
	PlatformPlaySoundDevice(SoundDevice);
      }

	
      win32_window_dimension Dimension = Win32GetWindowDimension(Window->Handle);
      Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext, Dimension.Width, Dimension.Height);
    }
    PlatformCloseSoundDevice(SoundDevice);
    PlatformCloseWindow(Window);
    PlatformCloseInput(InputDevice);
  }
  

  return 0;
}

