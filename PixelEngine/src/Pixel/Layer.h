#pragma once

#include "Pixel/Core.h"


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

		inline const std::string& GetName() const  { return m_DebugName;}
	
	protected:
		std::string m_DebugName;
		bool m_IsEnabled;
	};
}



