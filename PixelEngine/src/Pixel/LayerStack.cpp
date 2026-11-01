#include "PixelPCH.h"
#include "LayerStack.h"

Pixel::LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

Pixel::LayerStack::~LayerStack()
{
	for (Layer* l : m_Layers)
	{
		delete l;
	}
}

void Pixel::LayerStack::PushLayer(Layer * layer)
{
	m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	PIX_CORE_INFO("Added new layer '{0}' to the layer stack", layer->GetName());
}

void Pixel::LayerStack::PushOverlay(Layer * overlay)
{
	m_Layers.emplace_back(overlay);
	PIX_CORE_INFO("Added new overlay '{0}' to the layer stack", overlay->GetName());
}

void Pixel::LayerStack::PopLayer(Layer * layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if(it != m_Layers.end())
	{
		m_Layers.erase(it);
		m_LayerInsert--;
		PIX_CORE_INFO("Removed layer '{0}' from the layer stack", layer->GetName());
	}
	else
	{
		PIX_CORE_WARN("Couldn't find layer '{0}' in the the layer stack", layer->GetName());
	}
}

void Pixel::LayerStack::PopOverlay(Layer * overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		PIX_CORE_INFO("Removed overlay '{0}' from the layer stack", overlay->GetName());
	}
	else
	{
		PIX_CORE_WARN("Couldn't find overlay '{0}' in the the layer stack", overlay->GetName());
	}
}
