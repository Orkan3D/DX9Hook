// Author: Sean Pesce
// Original d3d9.dll wrapper base by Michael Koch

#pragma once

#define SP_D3D9_EXPORT_COUNT_ 1


//////////////////////// WRAPPER DLL FUNCTIONS ////////////////////////
// Exported function
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);


//////////////////////// CONSTANTS & ENUMS ////////////////////////

// Enumerator whose values specify whether a toggleable setting is enabled or disabled:
enum SP_OL_TXT_ENABLED_ENUM {
    OL_TXT_DISABLED,
    OL_TXT_ENABLED
};
// Enumerator whose values specify horizontal and vertical positions of overlay feed text:
enum SP_OL_TXT_POS_ENUM {
    OL_TXT_POS_LEFT,
    OL_TXT_POS_HCENTER,
    OL_TXT_POS_RIGHT,
    OL_TXT_POS_TOP,
    OL_TXT_POS_VCENTER,
    OL_TXT_POS_BOTTOM
};

// Acceptable values that a user can specify for text position in the settings file:
const char *SP_OL_TXT_POS_VALS[6] = { "LEFT", "CENTER", "RIGHT", "TOP", "CENTER", "BOTTOM" }; // If specified string isn't one of these values, the default value is used
// Acceptable values that a user can specify for text style in the settings file:
const char *SP_OL_TXT_STYLE_VALS[3] = { "OUTLINE", "SHADOW", "PLAIN" }; // If specified string isn't one of these values, the default value is used

// Default initialization setting values:
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_ENABLED_ OL_TXT_ENABLED
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_AUDIO_ENABLED_ OL_TXT_DISABLED
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_VERBOSE_OUTPUT_ENABLED_ OL_TXT_DISABLED
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_HORIZONTAL_POS_ SP_OL_TXT_POS_VALS[OL_TXT_POS_HCENTER]
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_VERTICAL_POS_ SP_OL_TXT_POS_VALS[OL_TXT_POS_BOTTOM]
#define _SP_D3D9_DEFAULT_VAL_OL_TXT_STYLE_ SP_OL_TXT_STYLE_VALS[SP_D3D9O_OUTLINED_TEXT]


//////////////////////// VARIABLES & DATA ////////////////////////

// Initialization data
HANDLE mod_thread;		// Mod thread handle
DWORD mod_thread_id;	// Mod thread ID
std::string d3d9_dll_chain; // Filename of the d3d9.dll wrapper to chain with (if any)
bool d3d9_dll_chain_failed; // Indicated that a d3d9.dll wrapper chain was specified, but failed to load
unsigned int generic_dll_count; // Number of generic DLLs loaded at runtime
std::string hostname;
std::string local_username;
std::string game_exe_dir;
