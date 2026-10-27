#pragma once

#include "Pixel/Core.h"
#include "Pixel/Log.h"

namespace Pixel
{
	class PIXEL_API Window
	{
	protected:
		Window(ui32 width, ui32 height);
		virtual ~Window();

	public:
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void clear() = 0;

		inline const ui32 getWidth() { return m_Width; }
		inline const ui32 getHeight() { return m_Height; }

	private:
		ui32 m_Width;
		ui32 m_Height;

	};
}


