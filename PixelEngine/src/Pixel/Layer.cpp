#include "PixelPCH.h"
#include "Layer.h"

Pixel::Layer::Layer(const std::string& name)
	:m_DebugName(name), m_IsEnabled(true)
{
	
}

Pixel::Layer::~Layer()
{
	delete m_Renderer;
	delete m_AssetManager;
}



