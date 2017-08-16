// Author: Sean Pesce
// Header file for exported data (used by overlay plugins)

#pragma once


#ifndef _SP_D3D9_LIB_EXPORTS_H_
	#define _SP_D3D9_LIB_EXPORTS_H_

#include "stdafx.h"
#include "d3d9.h"
#include <string>

#define _d3d9_dev_ get_d3d9_device()

#ifndef _SP_D3D9O_TEXT_COLOR_ENUM_
	#define _SP_D3D9O_TEXT_COLOR_ENUM_
	#ifdef _SP_D3D9O_TF_USE_ID3DX_FONT_
	// Total number of supported text colors
	#define _SP_D3D9O_TEXT_COLOR_COUNT_ 11
	// Denotes supported text colors
	enum SP_D3D9O_TEXT_COLOR_ENUM {
		SP_D3D9O_TEXT_COLOR_WHITE,
		SP_D3D9O_TEXT_COLOR_BLACK,
		SP_D3D9O_TEXT_COLOR_RED,
		SP_D3D9O_TEXT_COLOR_ORANGE,
		SP_D3D9O_TEXT_COLOR_YELLOW,
		SP_D3D9O_TEXT_COLOR_GREEN,
		SP_D3D9O_TEXT_COLOR_CYAN,
		SP_D3D9O_TEXT_COLOR_BLUE,
		SP_D3D9O_TEXT_COLOR_PURPLE,
		SP_D3D9O_TEXT_COLOR_PINK,
		SP_D3D9O_TEXT_COLOR_CYCLE_ALL
	};
	#else
	// Total number of supported text colors
	#define _SP_D3D9O_TEXT_COLOR_COUNT_ 10
	// Denotes supported text colors
	enum SP_D3D9O_TEXT_COLOR_ENUM {
		SP_D3D9O_TEXT_COLOR_WHITE,
		SP_D3D9O_TEXT_COLOR_BLACK,
		SP_D3D9O_TEXT_COLOR_RED,
		SP_D3D9O_TEXT_COLOR_ORANGE,
		SP_D3D9O_TEXT_COLOR_YELLOW,
		SP_D3D9O_TEXT_COLOR_GREEN,
		SP_D3D9O_TEXT_COLOR_CYAN,
		SP_D3D9O_TEXT_COLOR_BLUE,
		SP_D3D9O_TEXT_COLOR_PURPLE,
		SP_D3D9O_TEXT_COLOR_PINK
	};
	#endif // _SP_D3D9O_TF_USE_ID3DX_FONT_
#endif // _SP_D3D9O_TEXT_COLOR_ENUM_


//////////////////// Exported library data ////////////////////

__declspec(dllexport) std::string d3d9o_dll_filename;
__declspec(dllexport) unsigned long long default_msg_duration;


//////////////////// Exported library functions ////////////////////

__declspec(dllexport) IDirect3DDevice9 *get_d3d9_device();
__declspec(dllexport) unsigned int register_hotkey_function(unsigned int vk_hotkey, int(*function)());
__declspec(dllexport) int register_console_command(const char *command, void(*function)(std::vector<std::string>, std::string *), const char *help_message);
__declspec(dllexport) int print(const char *message);
__declspec(dllexport) bool print_console(const char *message);
__declspec(dllexport) bool print_text_feed(const char *message, unsigned long long duration, bool include_timestamp);
__declspec(dllexport) bool print_text_feed(const char *message, unsigned long long duration, bool include_timestamp, SP_D3D9O_TEXT_COLOR_ENUM text_color);



#endif // _SP_D3D9_LIB_EXPORTS_H_