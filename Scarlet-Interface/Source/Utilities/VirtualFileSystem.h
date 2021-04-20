#pragma once

#include "Core/Common.h"
#include "DirectoryTypes.h"

namespace ScarletInterface {

	class VirtualFileSystem
	{
	public:
		VirtualFileSystem();
		virtual ~VirtualFileSystem() = default;

		void AddEntry(const Directory& _Where, const Directory& _Entry);
		void SetRoot(Directory _Directory) { m_RootDirectory = _Directory; }
		Directory* GetRoot() { return &m_RootDirectory; }
		Directory* GetSub(const Directory& _Where);

		Vector<Directory> GetSubTypes(const char* _Type);

	private:
		Directory m_RootDirectory;

	public:
		static Ref<VirtualFileSystem> Create()
		{ return CreateRef<VirtualFileSystem>(); }
	};

}