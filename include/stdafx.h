// Author: Sean Pesce
// Original d3d9.dll wrapper base by Michael Koch

#pragma once

#ifndef _SP_D3D9_STDAFX_H_
    #define _SP_D3D9_STDAFX_H_

#define WIN32_LEAN_AND_MEAN		

//#define D3D_DEBUG_INFO 1


#include <Windows.h>

// Fixes for compatibility issues between SeQan and Windows API
#ifdef min
    #undef min
#endif // min
#ifdef max
    #undef max
#endif // max

#include <algorithm>
#include "d3d9.h"
#include "SpD3D9Interface.h"
#include "SpD3D9Device.h"
#include "SpD3D9SwapChain.h"

//////////////////////// Settings constants ////////////////////////
// Settings file data:
#define _SP_D3D9_SETTINGS_FILE_ ".\\d3d9_Mod.ini"	// Settings file name
//	Settings file sections
#define _SP_D3D9_SETTINGS_SECTION_KEYBINDS_ "Keybinds"
#define _SP_D3D9_SETTINGS_SECTION_PREFS_ "Preferences"
#define _SP_D3D9_SETTINGS_SECTION_ADV_SETTINGS_ "Advanced Settings"
#define _SP_D3D9_SETTINGS_SECTION_DEV_KEYBINDS_ "Developer Keybinds"
#define _SP_D3D9_SETTINGS_SECTION_DEV_PREFS_ "Developer Preferences"
//	Advanced settings section key names
#define _SP_D3D9_DLL_CHAIN_KEY_ "d3d9Chain"
#define _SP_D3D9_DLL_GENERIC_KEY_ "GenericDLL"
#ifdef _SP_DARK_SOULS_1_
    #define _SP_D3D9_DSPW_ADJUSTMENT_KEY_ "DspwOverlayAdjustment"
#endif // _SP_DARK_SOULS_1_
//	Keybinds section key names
#define _SP_D3D9_HOTKEY_TOGGLE_OL_TXT_KEY_ "ToggleOverlay"
#define _SP_D3D9_HOTKEY_NEXT_OL_TXT_POS_KEY_ "ChangeOverlayTextPosition"
#define _SP_D3D9_HOTKEY_NEXT_OL_TXT_STYLE_KEY_ "ChangeOverlayTextStyle"
#define _SP_D3D9_HOTKEY_TOGGLE_TEXT_FEED_INFO_BAR_KEY_ "ToggleInfoBar"
#define _SP_D3D9_HOTKEY_OPEN_CONSOLE_KEY_ "OpenConsole"
//	User preferences section key names
#define _SP_D3D9_OL_TXT_ENABLED_KEY_ "EnableOverlay"
#define _SP_D3D9_OL_TXT_SIZE_KEY_ "OverlayTextSize"
#define _SP_D3D9_OL_TXT_HORIZONTAL_POS_KEY_ "OverlayTextHorizontalPosition"
#define _SP_D3D9_OL_TXT_VERTICAL_POS_KEY_ "OverlayTextVerticalPosition"
#define _SP_D3D9_OL_TXT_STYLE_KEY_ "OverlayTextStyle"
#define _SP_D3D9_OL_TXT_AUDIO_ENABLED_KEY_ "EnableAudioFeedback"
#define _SP_D3D9_OL_TXT_ENABLE_FPS_KEY_ "DisplayFPS"
#define _SP_D3D9_OL_TXT_ENABLE_FRAME_COUNT_KEY_ "DisplayFrameCount"
#define _SP_D3D9_OL_TXT_ENABLE_TIME_KEY_ "DisplayTime"
#define _SP_D3D9_OL_TXT_ENABLE_DATE_KEY_ "DisplayDate"
//	Developer keybinds section key names
#define _SP_D3D9_HOTKEY_PRINT_OL_TXT_TEST_MSG_KEY_ "PrintTestMessage"
#define _SP_D3D9_HOTKEY_TOGGLE_AUDIO_FEEDBACK_KEY_ "ToggleAudioFeedback"
#define _SP_D3D9_HOTKEY_TOGGLE_VERBOSE_OUTPUT_KEY_ "ToggleVerboseOutput"
#define _SP_D3D9_HOTKEY_INCREASE_TXT_SIZE_KEY_ "IncreaseTextSize"
#define _SP_D3D9_HOTKEY_DECREASE_TXT_SIZE_KEY_ "DecreaseTextSize"
#define _SP_D3D9_HOTKEY_RESET_TXT_SIZE_KEY_ "ResetTextSize"
//	Developer preferences section key names
#define _SP_D3D9_OL_TXT_VERBOSE_OUTPUT_ENABLED_KEY_ "EnableVerboseOutput"

// Standard lifetime (in milliseconds) of an overlay text feed message
#define _SP_D3D9_OL_TEXT_FEED_MSG_LIFESPAN_ 2000
// Delay, in milliseconds, after a mod keybind is pressed, before the mod will continue listening for future keypresses
#define _SP_D3D9_KEYPRESS_WAIT_TIME_ 100
#define _SP_D3D9_DEFAULT_BEEP_DURATION_ 100

inline void D3D9_OutputLogEvent(const char* fmt, ...)
{
    char msg[4000];
    va_list ap;
    va_start(ap, fmt);
    _vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    OutputDebugStringA(msg);
}

#define _SP_D3D9_LOG_DEFAULT_FILE_ "_sp_d3d9_debug.log"
#define _SP_SP_D3D9_LOG_INIT_(file) __noop
#define _SP_D3D9_LOG_EV_MSG_BUFF_SIZE_ 128

#define _SP_D3D9_LOG_EVENT_(msg, ...) D3D9_OutputLogEvent(msg, ##__VA_ARGS__)
#define _SP_D3D9_LOG_SPEC_EVENT_(file, msg, ...) __noop

#ifdef _DEBUG
inline void* getCallerAddress()
{
    __asm
    {
        mov ecx, dword ptr ss : [ebp + 0] ;
        mov eax, dword ptr ss : [ecx + 4] ;
    }
}
#else
inline void* getCallerAddress()
{
    __asm
    {
        mov eax, dword ptr ss : [ebp + 4] ;
    }
}
#endif

#define D3D_DEBUG_INFO

#ifdef D3D_DEBUG_INFO
    #include <DxErr.h>
    #pragma comment(lib, "dxerr.lib")

    #define _SP_D3D9_CHECK_FAILED_(f) \
    { \
        HRESULT hres_tmp_ = f; \
        _SP_D3D9_LOG_EVENT_("[DXH] %s: %s", __FUNCTION__, DXGetErrorString(hres_tmp_)); \
        if(FAILED(hres_tmp_)) { \
            _SP_D3D9_LOG_EVENT_("[DXH]     Error String: %s\n", DXGetErrorDescriptionA(hres_tmp_)); \
        } else { \
        }\
    }

#define _SP_D3D9_CHECK_AND_RETURN_FAILED_(f) \
    { \
        HRESULT hres_tmp_ = f; \
        _SP_D3D9_LOG_EVENT_("[DXH] %s: %s (%i; @ %p)", __FUNCTION__, DXGetErrorString(hres_tmp_), hres_tmp_, getCallerAddress()); \
        if(FAILED(hres_tmp_)) { \
            _SP_D3D9_LOG_EVENT_("[DXH]     Error String: %s\n", DXGetErrorDescriptionA(hres_tmp_)); \
        } else { \
        }\
        return hres_tmp_; \
    }

#else
    //#define _SP_D3D9_CHECK_FAILED_(f) {HRESULT hres_tmp_;if(FAILED(hres_tmp_ = f)){_SP_D3D9_LOG_EVENT_("D3D9 ERROR - Occurred in:  thread %d;  %s (line %d)",GetCurrentThreadId(),__FUNCTION__,__LINE__);}}
    //#define _SP_D3D9_CHECK_AND_RETURN_FAILED_(f) {HRESULT hres_tmp_;if(FAILED(hres_tmp_ = f)){_SP_D3D9_LOG_EVENT_("D3D9 ERROR - Occurred in:  thread %d;  %s (line %d)",GetCurrentThreadId(),__FUNCTION__,__LINE__);}return hres_tmp_;}
    #define _SP_D3D9_CHECK_FAILED_(f) FAILED(f)
    #define _SP_D3D9_CHECK_AND_RETURN_FAILED_(f) return f;
#endif // D3D_DEBUG_INFO

#endif // _SP_D3D9_STDAFX_H_
