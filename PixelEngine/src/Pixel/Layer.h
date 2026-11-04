#pragma once

#include "Pixel/Core.h"
#include "Renderer/Renderer.h"
#include "Pixel/AssetManager.h"
#include "Pixel/Window/Window.h"	//For access to the input data struct

namespace Pixel
{
	class PIXEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void processInput(WindowData* inputData) = 0;

		inline const std::string& GetName() const  { return m_DebugName;}
		inline const bool isEnabled() const { return m_IsEnabled; }
		inline void enable() { m_IsEnabled = true; }
		inline void disable() { m_IsEnabled = false; }

		inline void setAssetManager(AssetManager* manager) { m_AssetManager = manager; }

	
	protected:
		std::string m_DebugName;
		bool m_IsEnabled;
		Renderer* m_Renderer;
		AssetManager* m_AssetManager;
	};
}



