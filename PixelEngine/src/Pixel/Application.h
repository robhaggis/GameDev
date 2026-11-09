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

		WindowData* getInput() { return &m_InputData; }

		void InitResources(std::string pathToTextures, std::string pathToShaders);
		Shader* GetShader(std::string name);

		
		Texture* GetTexture(std::string name);


	private:
		void AddShader(std::string name, std::string vertPath, std::string fragPath);
		void AddTexture(std::string name, std::string filepath);
		std::unique_ptr<Window> m_Window;
		WindowData m_InputData;
		bool m_isRunning = true;
		LayerStack m_LayerStack{};
		AssetManager m_assetManager{};
		Renderer* m_Renderer;

	};

	//To be defined in client app
	Application* CreateApplication(ui32 width, ui32 height, const char* title);
}

