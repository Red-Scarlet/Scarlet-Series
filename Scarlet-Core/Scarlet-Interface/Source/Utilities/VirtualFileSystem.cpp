#include "VirtualFileSystem.h"

namespace ScarletInterface {

	VirtualFileSystem::VirtualFileSystem()
	{
	}

	static Directory* Get(Directory* _Directory, const Directory& _Where)
	{
		for (Directory& directory : _Directory->Sub)
		{
			if (directory.Path == _Where.Path)
				return &directory;
			else {
				Directory* found = Get(&directory, _Where);
				if (found) return found;
			}
		}

		return nullptr;
	}

	void VirtualFileSystem::AddEntry(const Directory& _Where, const Directory& _Entry)
	{
		Directory* parent = Get(&m_RootDirectory, _Where);
		if (parent) {
			parent->Sub.push_back(_Entry);
		} else m_RootDirectory.Sub.push_back(_Entry);
	}

	Directory* VirtualFileSystem::GetSub(const Directory& _Where)
	{
		Directory* parent = Get(&m_RootDirectory, _Where);
		if (parent) return parent;
		else return &m_RootDirectory;
	}

	static Vector<Directory> GetTypes(Directory _Directory, const char* _Ext)
	{
		Vector<Directory> directories;

		for (Directory& directory : _Directory.Sub)
		{
			Vector<Directory> subdirectories = GetTypes(directory, _Ext);
			std::copy(subdirectories.begin(), subdirectories.end(), std::back_inserter(directories));
			if (directory.Ext == _Ext) directories.push_back(directory);
		}

		return directories;
	}

	Vector<Directory> VirtualFileSystem::GetSubTypes(const char* _Ext)
	{
		Vector<Directory> directories = GetTypes(m_RootDirectory, _Ext);
		return directories;
	}


}