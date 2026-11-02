#pragma once

#include "../PixelPCH.h"
#include "Core.h"
#include "Log.h"

namespace Pixel
{
	class FileIO
	{
    public:
		static std::string readStringFromFile(const std::string& filepath)
		{
            std::string result;
            std::ifstream fileData;
            fileData.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                fileData.open(filepath);
                std::stringstream fileStream;
                fileStream << fileData.rdbuf();
                fileData.close();
                result = fileStream.str();
            }
            catch (const std::ifstream::failure& e)
            {
                PIX_CORE_ERROR("Couldn't read file at '{0}': {1}", filepath, e.what());
            }
            return result;
		}
	};
}
	



