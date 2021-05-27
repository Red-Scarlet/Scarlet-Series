#pragma once

#include "Core/Common.h"
#include <fstream>
#include <filesystem>

namespace ScarletInterface {

	namespace fs = std::filesystem;

	struct FileUtils
	{
	public:
		static String ReadFile(const char* filepath)
		{
			FILE* file = fopen(filepath, "r");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			String result(data);
			delete[] data;
			return result;
		}

		static bool CheckExist(const String& _Location)
		{
			fs::path p = _Location;
			fs::file_status s = fs::file_status{};
			return fs::status_known(s) ? fs::exists(s) : fs::exists(p);
		}

	};

}