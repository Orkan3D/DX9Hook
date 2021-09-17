// Author: Sean Pesce

#include "stdafx.h"

SpD3D9SwapChain::SpD3D9SwapChain(IDirect3DSwapChain9 **ppIDirect3DSwapChain9, SpD3D9Device *device)
{
    m_pD3D9SwapChain = *ppIDirect3DSwapChain9;
    this->device = device;
    present_calls = &(device->swap_chain_present_calls);
    *ppIDirect3DSwapChain9 = this;
}


ULONG SpD3D9SwapChain::AddRef()
{
    return m_pD3D9SwapChain->AddRef();
}


HRESULT SpD3D9SwapChain::QueryInterface(REFIID riid, void **ppvObject)
{
    // Check if original dll can provide interface, then send this address
    *ppvObject = NULL;

    HRESULT hres = m_pD3D9SwapChain->QueryInterface(riid, ppvObject);

    if (hres == S_OK)
    {
        *ppvObject = this;
    }

    return hres;
}


ULONG SpD3D9SwapChain::Release()
{
    extern SpD3D9SwapChain *gl_pSpD3D9SwapChain;

    ULONG count = m_pD3D9SwapChain->Release();

    if (count == 0)
    {
        //m_pD3D9_swap_chain = NULL;
        gl_pSpD3D9SwapChain = NULL;
        delete this;
    }

    return count;
}


HRESULT SpD3D9SwapChain::GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->GetBackBuffer(BackBuffer, Type, ppBackBuffer));
}


HRESULT SpD3D9SwapChain::GetDevice(IDirect3DDevice9 **ppDevice)
{
    HRESULT hres = m_pD3D9SwapChain->GetDevice(ppDevice);

    _SP_D3D9_CHECK_FAILED_(hres);
    if (!FAILED(hres))
    {
        // Return address of device wrapper instead
        (*ppDevice) = device;
    }

    return hres;
}


HRESULT SpD3D9SwapChain::GetDisplayMode(D3DDISPLAYMODE *pMode)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->GetDisplayMode(pMode));
}


HRESULT SpD3D9SwapChain::GetFrontBufferData(IDirect3DSurface9 *pDestSurface)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->GetFrontBufferData(pDestSurface));
}


HRESULT SpD3D9SwapChain::GetPresentParameters(D3DPRESENT_PARAMETERS *pPresentationParameters)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->GetPresentParameters(pPresentationParameters));
}


HRESULT SpD3D9SwapChain::GetRasterStatus(D3DRASTER_STATUS *pRasterStatus)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->GetRasterStatus(pRasterStatus));
}


HRESULT SpD3D9SwapChain::Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion, DWORD dwFlags)
{
    _SP_D3D9_CHECK_AND_RETURN_FAILED_(m_pD3D9SwapChain->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags));
}
