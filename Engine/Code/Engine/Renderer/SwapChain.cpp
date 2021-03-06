#include "Engine/Renderer/SwapChain.hpp"
#include "Engine/Renderer/RenderContext.hpp"
#include "Engine/Core/D3D11Common.hpp"
#define UNUSED(x) (void)(x);

SwapChain::SwapChain( RenderContext* owner , IDXGISwapChain* handle ):m_owner(owner),m_handle(handle)
{

}

SwapChain::~SwapChain()
{
	delete m_backbuffer;
	m_backbuffer = nullptr;

	DX_SAFE_RELEASE( m_handle );
}

void SwapChain::Present( int vsync /*= 0 */ )
{
	m_handle->Present( 0 , 0 );
	UNUSED( vsync );
}

Texture* SwapChain::GetBackBuffer()
{
	if ( m_backbuffer != nullptr )
	{
		return m_backbuffer;
	}

	ID3D11Texture2D* texHandle = nullptr;

	m_handle->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , ( void** ) & texHandle );

	m_backbuffer = new Texture( m_owner , texHandle );

	return m_backbuffer;
}

