#include "PixelPCH.h"
#include "Layer.h"

Pixel::Layer::Layer(const std::string& name)
	:m_DebugName(name), m_IsEnabled(true), m_Renderer(nullptr)
{
	m_Renderer = new Renderer();
}

Pixel::Layer::~Layer()
{
	delete m_Renderer;
}



