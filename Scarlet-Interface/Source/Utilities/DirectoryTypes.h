#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	struct Directory
	{
	public:
		const char* Name;
		const char* Ext;
		const char* Path;
		Vector<Directory> Sub;

		operator bool() const { return Path != ""; }
		bool operator== (const Directory& other) const { return Path == other.Path; }
		bool operator!= (const Directory& other) const { return Path != other.Path; }
	};

}