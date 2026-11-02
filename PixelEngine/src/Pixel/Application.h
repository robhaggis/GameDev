#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "LayerStack.h"
#include "AssetManager.h"
#include "Texture.h"


namespace Pixel
{
	
	class PIXEL_API Application
	{

	public:
		Application(i32 width, i32 height, const char* title);
		virtual ~Application();

		void run();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		InputData* getInput() { return &m_InputData; }

		void AddShader(std::string name, std::string vertPath, std::string fragPath);
		Shader* GetShader(std::string name);

		void AddTexture(std::string name, std::string filepath);
		Texture* GetTexture(std::string name);


	private:
		std::unique_ptr<Window> m_Window;
		InputData m_InputData;
		bool m_isRunning = true;
		LayerStack m_LayerStack{};
		AssetManager m_assetManager{};

	};

	//To be defined in client app
	Application* CreateApplication(ui32 width, ui32 height, const char* title);
}

