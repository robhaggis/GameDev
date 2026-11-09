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
            std::string result = "";
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
                //PIX_CORE_ERROR("Couldn't read file at '{0}': {1}", filepath, e.what());
            }
            return result;
		}

        static void getAllFilesInDirectory(std::vector<std::string>* allFiles, const std::string& dirpath)
        {
            //This struct is to distinguish a file from a directory
            struct stat sb;

            //Loop directory until all items are exhausted
            for (const auto& entry : std::filesystem::directory_iterator(dirpath)) 
            {
                //Convert path to const char*
                std::filesystem::path outfilename = entry.path();
                std::string outfilename_str = outfilename.string();
                const char* path = outfilename_str.c_str();

                //If path is a non-directory, add to result
                if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
                {
                    allFiles->emplace_back(path);
                }
            }

        }

        //Extracts the filename from the path provided, optionally with the file extension also included
        static std::string extractFileNameFromPath(std::string filepath, bool alsoReturnFileExtension = false)
        {
            //Extract just the filename from the path
            size_t lastSlash = filepath.find_last_of("/\\");
            std::string base = (lastSlash == std::string::npos) ? filepath : filepath.substr(lastSlash + 1);

            if (alsoReturnFileExtension) return base;

            size_t lastDot = base.find_last_of('.');
            std::string result = (lastDot == std::string::npos || lastDot == 0) ? base : base.substr(0, lastDot);
            return result;
        }
	};
} 
	



