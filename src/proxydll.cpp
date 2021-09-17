// Author: Sean Pesce
// Original d3d9.dll wrapper base by Michael Koch

#include "stdafx.h"
#include "proxydll.h"

// Global variables
#pragma data_seg (".d3d9_shared")
SpD3D9Device*		gl_pSpD3D9Device;
SpD3D9Interface*	gl_pSpD3D9Interface;
SpD3D9SwapChain*	gl_pSpD3D9SwapChain;
DWORD				lasterr;
HINSTANCE			gl_hOriginalDll;
HINSTANCE			gl_hThisInstance;
#pragma data_seg ()

//char* const export_names[SP_D3D9_EXPORT_COUNT_] = { "D3DPERF_BeginEvent", "D3DPERF_EndEvent", "D3DPERF_GetStatus", "D3DPERF_QueryRepeatFrame", "D3DPERF_SetMarker", "D3DPERF_SetOptions", "D3DPERF_SetRegion", "DebugSetLevel", "DebugSetMute", "Direct3D9EnableMaximizedWindowedModeShim", "Direct3DCreate9", "Direct3DCreate9Ex", "Direct3DShaderValidatorCreate9", "PSGPError", "PSGPSampleTexture" };
//extern "C" UINT_PTR d3d9_original_procs[SP_D3D9_EXPORT_COUNT_] = { 0 };

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    void LoadOriginalDll();
    void InitInstance(HANDLE hModule);

    // To avoid compiler level 4 warnings 
    LPVOID lpDummy = lpReserved;
    lpDummy = NULL;

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            _SP_SP_D3D9_LOG_INIT_(_SP_D3D9_LOG_DEFAULT_FILE_); // Initialize log file(s)
            InitInstance(hModule);

            if (!gl_hOriginalDll)
            {
                // Get original DLL from system directory
                LoadOriginalDll();
                d3d9_dll_chain_failed = true;
            }
            break;
        case DLL_PROCESS_DETACH:
            if (gl_pSpD3D9Device != NULL)
            {
                delete gl_pSpD3D9Device;
                gl_pSpD3D9Device = NULL;
            }
            _SP_D3D9_LOG_EVENT_("Exit (Detached from process)\n\n");
            break;
        case DLL_THREAD_ATTACH:
            //_SP_D3D9_LOG_EVENT_("Thread %d start", GetCurrentThreadId());
            break;
        case DLL_THREAD_DETACH:
            //_SP_D3D9_LOG_EVENT_("Thread %d terminated", GetCurrentThreadId());
            break;
        default:
            break;
    }
    return TRUE;
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
    void LoadOriginalDll();

    if (!gl_hOriginalDll)
    {
        LoadOriginalDll(); // Looking for the real d3d9.dll
        d3d9_dll_chain_failed = true;
    }

    // Hooking IDirect3D Object from Original Library
    typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
    D3D9_Type o_Direct3DCreate9 = (D3D9_Type)GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");

    // Debug
    if (!o_Direct3DCreate9)
    {
        OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
        ::ExitProcess(0); // Exit the hard way
    }

    // Request pointer from Original Dll 
    IDirect3D9 *pIDirect3D9_orig = o_Direct3DCreate9(SDKVersion);

    // Create SpD3D9Interface object and store pointer to original object there.
    // Note: The object will delete itself once the Ref count is zero (similar to COM objects)
    gl_pSpD3D9Interface = new SpD3D9Interface(pIDirect3D9_orig);

    // Return pointer to hooking Object instead of the real one
    return (gl_pSpD3D9Interface);
}

void InitInstance(HANDLE hModule)
{
    OutputDebugString("PROXYDLL: InitInstance called.\r\n");

    // Initialization
    generic_dll_count = 0;
    gl_hOriginalDll = NULL;
    gl_hThisInstance = NULL;
    gl_pSpD3D9Interface = NULL;
    gl_pSpD3D9Device = NULL;
    gl_pSpD3D9SwapChain = NULL;

    // Storing Instance handle into global variable
    gl_hThisInstance = (HINSTANCE)hModule;
}

// Loads the original d3d9.dll from the system directory
void LoadOriginalDll(void)
{
    char buffer[MAX_PATH];

    //// Getting path to system dir and to d3d9.dll
    //::GetSystemDirectory(buffer, MAX_PATH);

    //// Append dll name
    //strcat_s(buffer, "\\d3d9.dll");

    strcpy(buffer, ".\\d3d9_o.dll");

    // Try to load the system's d3d9.dll, if pointer empty
    if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

    // Debug
    if (!gl_hOriginalDll)
    {
        OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
        ::ExitProcess(0); // Exit the hard way
    }
}
