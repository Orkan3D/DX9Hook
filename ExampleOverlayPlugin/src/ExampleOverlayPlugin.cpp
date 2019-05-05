//

#include "ExampleOverlayPlugin.h"


DWORD WINAPI deferred_tasks(LPVOID lpParam);



/*
    Called from DllMain when the plugin DLL is first loaded into memory (PROCESS_ATTACH case).
    NOTE: This function runs in the same thread as DllMain, so code implemented here will halt
    game loading. Code in this function should be limited to tasks that absolutely MUST be
    executed before the game loads. For less delicate startup tasks, use on_process_attach_async()
    or initialize_plugin().
*/
void on_process_attach()
{
    
}



/*
    Called from DllMain when the plugin DLL is first loaded into memory (PROCESS_ATTACH case).
    This function runs in a separate thread from DllMain, so code implemented here does NOT
    pause game loading. Code that must be executed before the game loads should be implemented
    in on_process_attach() instead of this function.
*/
DWORD WINAPI on_process_attach_async(LPVOID lp_param)
{
    while (!_d3d9_dev)
    {
        Sleep(500);
    }

    // Print example message to in-game console
    print_console("[Example Overlay Plugin] Hello world!");



    return 0;
}



// Called from DllMain when the plugin DLL is unloaded (PROCESS_DETACH case)
void on_process_detach()
{
    // Exit tasks should be performed here

}



//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Exported functions ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    The functions below are exported from this DLL and imported
    by the DirectX9 overlay when loading this DLL as a plugin.

    These functions are called during important events throughout
    the execution of the program, allowing the developer(s) to run
    code that takes advantage of these processes (such as rendering
    DirectX elements and reading player input).
*/


/*
    Called exactly once after DirectX9 overlay is initialized.
*/
__declspec(dllexport) void __stdcall initialize_plugin()
{
    // Start thread for deferred tasks
    if (!CreateThread(NULL, 0, deferred_tasks, NULL, 0, NULL))
    {
        // Error creating new thread
    }


    // Other initialization tasks can be performed here

}



/*
    Continuously called from the main thread loop in the overlay DLL.
*/
__declspec(dllexport) void __stdcall main_loop()
{
    // Use this function for code that must be called repeatedly, such as checking flags or waiting for values to change

    
}



/*
    Called from initialize_plugin() after the DLL is loaded and initialized. This function is for
    tasks that can only be executed AFTER certain events have occurred, but don't need to be
    executed BEFORE any specific time or event.
*/
DWORD WINAPI deferred_tasks(LPVOID lpParam)
{
    
    return 0;
}



/*
    Called every frame inside of a BeginScene()/EndScene() pair.

        Microsoft documentation for IDirect3DDevice9 Interface:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb174336(v=vs.85).aspx

*/
__declspec(dllexport) void __stdcall draw_overlay(std::string *text_feed_info_header)
{
    /*
        Allows drawing of additional overlay elements and live text feed info header elements.
        An appropriate stateblock for overlay drawing is applied before this function is called.

        NOTE: Use the _d3d9_dev macro to obtain the game's IDirect3DDevice9 for drawing new elements.

        WARNING: This function is called from inside the DirectX9 Device Present() function. Keep
        code in this function as optimized as possible to avoid lowering FPS.
    */
    
    // Draw a red square in the top left corner of the screen:
    static const D3DRECT square = { 0, 0, 200, 200 };
    _d3d9_dev->Clear(2, &square, D3DCLEAR_TARGET, D3DXCOLOR(0x00FF0000), 0, 0);

    // Draw white example text in the top left corner of the screen:
    CD3DFont font = CD3DFont("Arial", 12, D3DFONT_BOLD);
    font.InitializeDeviceObjects(_d3d9_dev);
    font.RestoreDeviceObjects();
    font.BeginDrawing();
    font.DrawText(50, 50, 0x00000000, "Hello world!", D3DFONT_COLORTABLE, 0); // Draw text
    font.EndDrawing();

}



/*
    Called every frame from the Present() member function of either the D3D9 device or SwapChain (depends on the game's rendering method; Dark Souls uses Device).
    If called from IDirect3DDevice9::Present (rather than IDirect3DSwapChain9::Present), dwFlags is always zero.

        Microsoft documentation for IDirect3DDevice9::Present():
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb174423(v=vs.85).aspx

*/
__declspec(dllexport) void __stdcall present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion, DWORD dwFlags)
{
    /*
        NOTE: Use the _d3d9_dev macro to obtain the game's IDirect3DDevice9 for drawing new elements.

        WARNING: This function is called from inside the DirectX9 Device Present() function. Keep
        code in this function as optimized as possible to avoid performance issues.
    */
    
    
}



/*
    Called from the EndScene() member function of the D3D9 device.
    Note: This function isn't necessarily called exactly once per frame (could be more, less, or not at all).

        Microsoft documentation for IDirect3DDevice9::EndScene():
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb174375(v=vs.85).aspx

*/
__declspec(dllexport) void __stdcall end_scene()
{
    /*
        NOTE: Use the _d3d9_dev macro to obtain the game's IDirect3DDevice9 for drawing new elements.

        WARNING: This function is called from inside the DirectX9 Device EndScene() function. Keep
        code in this function as optimized as possible to avoid performance issues.
    */


    // Drawing can be done here, but it is preferable to draw in the draw_overlay() or present() functions.
}



/*
    Called every time GetRawInputData() is called with a non-null pData argument.

    Use this function to read player input, if needed.

        Microsoft documentation for GetRawInputData:
        https://msdn.microsoft.com/en-us/library/windows/desktop/ms645596(v=vs.85).aspx

    @return     True if the given input message should be cancelled before being sent to
                the game, thereby disabling game input. Otherwise, returns false.
*/
__declspec(dllexport) bool __stdcall get_raw_input_data(RAWINPUT *pData, PUINT pcbSize)
{
    // Mouse cursor position
    static POINT cursor_position; // Static variable; saved between calls

    // Determine input device type
    switch (pData->header.dwType)
    {
        case RIM_TYPEMOUSE:

            // Handle mouse input

            // Mouse button press
            switch (pData->data.mouse.usButtonFlags)
            {
                case RI_MOUSE_LEFT_BUTTON_DOWN:

                    break;

                case RI_MOUSE_LEFT_BUTTON_UP:

                    break;

                case RI_MOUSE_RIGHT_BUTTON_DOWN:

                    break;

                case RI_MOUSE_RIGHT_BUTTON_UP:

                    break;

                case RI_MOUSE_MIDDLE_BUTTON_DOWN:

                    break;

                case RI_MOUSE_MIDDLE_BUTTON_UP:

                    break;

                case RI_MOUSE_WHEEL:
                    if (pData->data.mouse.usButtonData == 120)
                    {
                        // Scrolling up
                    }
                    else if (pData->data.mouse.usButtonData == 65416)
                    {
                        // Scrolling down
                    }
                    break;

                    // Additional mouse buttons
                case RI_MOUSE_BUTTON_4_DOWN:
                case RI_MOUSE_BUTTON_4_UP:
                case RI_MOUSE_BUTTON_5_DOWN:
                case RI_MOUSE_BUTTON_5_UP:
                    break;
            } // switch (pData->data.mouse.usButtonFlags)

            // Mouse movement
            switch (pData->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
            {
                case MOUSE_MOVE_ABSOLUTE:
                    // Mouse movement data is based on absolute position
                    cursor_position.x = pData->data.mouse.lLastX;
                    cursor_position.y = pData->data.mouse.lLastY;
                    break;
                case MOUSE_MOVE_RELATIVE:
                    // Mouse movement data is relative (based on last known position)
                    cursor_position.x += pData->data.mouse.lLastX;
                    cursor_position.y += pData->data.mouse.lLastY;

                    // Keep cursor on-screen
                    RECT window_rect;
                    if (!GetClientRect(_game_window, &window_rect))
                    {
                        // Handle error
                        break;
                    }
                    if (cursor_position.x < 0) // Too far left
                    {
                        cursor_position.x = 0;
                    }
                    else if (cursor_position.x > window_rect.right) // Too far right
                    {
                        cursor_position.x = window_rect.right;
                    }
                    if (cursor_position.y < 0) // Too far up
                    {
                        cursor_position.y = 0;
                    }
                    else if (cursor_position.y > window_rect.bottom) // Too far down
                    {
                        cursor_position.x = window_rect.bottom;
                    }
                    break;
            }

            break; // case RIM_TYPEMOUSE

        case RIM_TYPEKEYBOARD:
            // Handle keyboard input

            // Determine type of keyboard input
            switch (pData->data.keyboard.Message)
            {
                case WM_KEYDOWN: // A nonsystem key is a key that is pressed when the ALT key is not pressed

                    // Determine which key was pressed
                    switch (pData->data.keyboard.VKey)
                    {
                        // Handle key press

                        default:
                            break;
                    }

                case WM_SYSKEYDOWN: // A system key is a key that is pressed when the ALT key is also down

                    // Determine which syskey was pressed
                    switch (pData->data.keyboard.VKey)
                    {
                        // Handle key press (when ALT is down)

                        default:
                            break;
                    }
                    break; // case  WM_KEYDOWN || WM_SYSKEYDOWN

                case WM_KEYUP:

                    // Determine which key was released
                    switch (pData->data.keyboard.VKey)
                    {
                        // Handle key release (key is no longer being pressed)

                        default:
                            break;
                    }
                    break; // case WM_KEYUP
            } // switch (pData->data.keyboard.Message)
            break; // case RIM_TYPEKEYBOARD

        case RIM_TYPEHID:

            // Handle input from some other type of hardware input device

            break; // case RIM_TYPEHID
    } // switch (pData->header.dwType)

    // False = don't disable game input (allow this input to reach the game)
    return false;
}
