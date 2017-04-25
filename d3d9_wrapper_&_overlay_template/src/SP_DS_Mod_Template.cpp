// Author: Sean Pesce

#include "stdafx.h"
#include "SP_DS_Mod_Template.h"


// Main loop for the mod thread
void mod_loop()
{
	get_ds_window(); // Get the Dark Souls window handle
	while (gl_pmyIDirect3DDevice9 == NULL)
	{
		Sleep(500);
	}
	gl_pmyIDirect3DDevice9->text_overlay.text_format = user_pref_overlay_text_pos;
	gl_pmyIDirect3DDevice9->text_overlay.text_style = user_pref_overlay_text_style;
	gl_pmyIDirect3DDevice9->SP_DX9_set_text_height(user_pref_overlay_text_size);
	gl_pmyIDirect3DDevice9->text_overlay.enabled = user_pref_overlay_text_enabled;
	gl_pmyIDirect3DDevice9->print_to_overlay_feed(_SP_DS_OL_TXT_INTRO_MESSAGE_, 0, false);

	while (mod_loop_enabled)
	{
		if (GetForegroundWindow() == ds_game_window) { // Check if Dark Souls game window is active

			get_async_keyboard_state(key_state); // Capture all current async key states

			if (hotkey_is_down(hotkey_toggle_overlay_text))
			{
				// Toggle overlay text
				gl_pmyIDirect3DDevice9->text_overlay.enabled = !gl_pmyIDirect3DDevice9->text_overlay.enabled;
				Sleep(_SP_DS_KEYPRESS_WAIT_TIME_);
			}
			else if (gl_pmyIDirect3DDevice9->text_overlay.enabled && hotkey_is_down(hotkey_next_overlay_text_pos))
			{
				// @TODO: Replace this block of code with mod functionality
				next_overlay_text_position(gl_pmyIDirect3DDevice9->text_overlay.text_format);
				Beep(800, 100);
				Sleep(_SP_DS_KEYPRESS_WAIT_TIME_);
			}
			else if (gl_pmyIDirect3DDevice9->text_overlay.enabled && hotkey_is_down(hotkey_next_overlay_text_style))
			{
				// @TODO: Replace this block of code with mod functionality
				next_overlay_text_style(gl_pmyIDirect3DDevice9->text_overlay.text_style);
				Beep(600, 100);
				Sleep(_SP_DS_KEYPRESS_WAIT_TIME_);
			}

			// @TODO: Other hotkeys should also be checked and handled here

			Sleep(1);
		}
		else
		{
			// Dark Souls game window is not active
			Sleep(100);
		}

		
	}
}

// Obtains the window handle for the Dark Souls game window
void get_ds_window()
{
	bool found_ds_window = false;

	while (!found_ds_window)
	{
		if (!EnumWindows(try_ds_window, (LPARAM)&found_ds_window))
		{
			// Handle error
		}
		Sleep(30);
	}
}

// Checks if a given window is the Dark Souls game window, and if so, saves the window handle
BOOL CALLBACK try_ds_window(HWND hwnd, LPARAM lParam)
{
	bool *found_ds_window = (bool*)lParam;
	DWORD pid;

	GetWindowThreadProcessId(hwnd, &pid); // Get Dark Souls process ID

	if (pid == GetCurrentProcessId())
	{
		// hwnd was created by Dark Souls process
		char window_class[128];
		
		if (!RealGetWindowClass(hwnd, window_class, 128))
		{
			// Handle error
		}
		window_class[127] = '\0';

		if (strcmp(window_class, _SP_DS_WINDOW_CLASS_) == 0)
		{
			// hwnd is the Dark Souls game window
			ds_game_window = hwnd;
			*found_ds_window = true;
		}
	}
	return 1;
}

// Switches the overlay text to the next preset position
void next_overlay_text_position(DWORD current_position)
{
	switch (current_position)
	{
	case _SP_TEXT_TOP_LEFT_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_TOP_CENTER_;
		break;
	case _SP_TEXT_TOP_CENTER_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_TOP_RIGHT_;
		break;
	case _SP_TEXT_TOP_RIGHT_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_CENTER_LEFT_;
		break;
	case _SP_TEXT_CENTER_LEFT_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_CENTER_CENTER_;
		break;
	case _SP_TEXT_CENTER_CENTER_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_CENTER_RIGHT_;
		break;
	case _SP_TEXT_CENTER_RIGHT_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_BOTTOM_LEFT_;
		break;
	case _SP_TEXT_BOTTOM_LEFT_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_BOTTOM_CENTER_;
		break;
	case _SP_TEXT_BOTTOM_CENTER_:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_BOTTOM_RIGHT_;
		break;
	case _SP_TEXT_BOTTOM_RIGHT_:
	default:
		gl_pmyIDirect3DDevice9->text_overlay.text_format = _SP_TEXT_TOP_LEFT_;
		break;
	}
}

// Switches to the next text overlay style
void next_overlay_text_style(int current_style)
{
	switch (current_style)
	{
	case SP_DX9_BORDERED_TEXT:
		gl_pmyIDirect3DDevice9->text_overlay.text_style = SP_DX9_SHADOWED_TEXT;
		gl_pmyIDirect3DDevice9->print_to_overlay_feed(_SP_DS_OL_TXT_SHADOW_STYLE_MESSAGE_, 1000, true);
		break;
	case SP_DX9_SHADOWED_TEXT:
		gl_pmyIDirect3DDevice9->text_overlay.text_style = SP_DX9_PLAIN_TEXT;
		gl_pmyIDirect3DDevice9->print_to_overlay_feed(_SP_DS_OL_TXT_PLAIN_STYLE_MESSAGE_, 1000, true);
		break;
	case SP_DX9_PLAIN_TEXT:
	default:
		gl_pmyIDirect3DDevice9->text_overlay.text_style = SP_DX9_BORDERED_TEXT;
		gl_pmyIDirect3DDevice9->print_to_overlay_feed(_SP_DS_OL_TXT_OUTLINE_STYLE_MESSAGE_, 1000, true);
		break;
	}
}