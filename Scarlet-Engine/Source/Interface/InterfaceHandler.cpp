#include "Scarletpch.h"
#include "InterfaceHandler.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tchar.h>
#include <filesystem>

namespace Scarlet {

    typedef InterfaceModule* (*fnCreateInterface)(void);
    typedef void (*fnDestroyInterface)(void);
    typedef void (*fnEventInterface)(Event& _Event);
    
    typedef Map<String, InterfaceModule*> PluginMap;
    typedef Map<String, HMODULE> LibraryMap;

    class InterfaceHandlerPimpl
    {
    public:
        PluginMap m_Plugins;
        LibraryMap m_Libs;
    };
    
    InterfaceHandler::InterfaceHandler()
    {
        SCARLET_PROFILE_FUNCTION();

        m_Implementation = new InterfaceHandlerPimpl();
    }
    
    InterfaceHandler::~InterfaceHandler()
    {
        SCARLET_PROFILE_FUNCTION();

        delete m_Implementation;
    }
    
    InterfaceHandler& InterfaceHandler::Instance()
    {
        SCARLET_PROFILE_FUNCTION();

        static InterfaceHandler interfaceHandler;
        return interfaceHandler;
    }
    
    InterfaceModule* InterfaceHandler::LoadInterface(const String& _Path)
    {
        SCARLET_PROFILE_FUNCTION();

        String name = _Path.substr(_Path.find_last_of("/\\") + 1, _Path.length());

        InterfaceModule* interfaceModule = nullptr;
        PluginMap::iterator iter = m_Implementation->m_Plugins.find(name);
        if (iter == m_Implementation->m_Plugins.end())
        {
            String originalPath = std::filesystem::current_path().string();
            String path = _Path.substr(0, _Path.find_last_of("/\\"));
            std::wstring wname = std::wstring(name.begin(), name.end());
            SetCurrentDirectory(std::wstring(path.begin(), path.end()).c_str());

            HMODULE hModule = LoadLibraryW(wname.c_str());
            if (hModule != nullptr) {
                fnCreateInterface CreateInterface = (fnCreateInterface)GetProcAddress(hModule, "CreateInterface");
                if (CreateInterface != nullptr)  {
                    interfaceModule = CreateInterface();
                    if (interfaceModule != nullptr) {
                        interfaceModule->m_Info.Name = name;
                        m_Implementation->m_Plugins.insert(PluginMap::value_type(name, interfaceModule));
                        m_Implementation->m_Libs.insert(LibraryMap::value_type(name, hModule ));
                    } else FreeLibrary(hModule);
                } else FreeLibrary(hModule);
            }

            SetCurrentDirectory(std::wstring(originalPath.begin(), originalPath.end()).c_str());
        } else interfaceModule = iter->second;

        return interfaceModule;
    }
    
    void InterfaceHandler::UnloadInterface(InterfaceModule* _Interface)
    {
        SCARLET_PROFILE_FUNCTION();

        if (_Interface != nullptr)
        {
            LibraryMap::iterator iter = m_Implementation->m_Libs.find(_Interface->GetInfo().Name);
            if( iter != m_Implementation->m_Libs.end() )
            {
                m_Implementation->m_Plugins.erase(_Interface->GetInfo().Name);
            
                HMODULE hModule = iter->second;
                fnDestroyInterface DestroyInterface = (fnDestroyInterface)GetProcAddress(hModule, "DestroyInterface");
                if (DestroyInterface != nullptr) DestroyInterface();
                else std::cout << "ERROR: Unable to find symbol \"DestroyPlugin\" in library \"" << _Interface->GetInfo().Name << std::endl;
                FreeLibrary(hModule);
                m_Implementation->m_Libs.erase(iter);
            }
            else std::cout << "WARNING: Trying to unload a plugin that is already unloaded or has never been loaded." << std::endl;

            _Interface = nullptr;
        }
    }
    
    void InterfaceHandler::EventInterface(Event& _Event, InterfaceModule* _Interface)
    {
        SCARLET_PROFILE_FUNCTION();

        if (_Interface != nullptr)
        {
            LibraryMap::iterator iter = m_Implementation->m_Libs.find(_Interface->GetInfo().Name);
            if (iter != m_Implementation->m_Libs.end())
            {
                HMODULE hModule = iter->second;
                fnEventInterface EventInterface = (fnEventInterface)GetProcAddress(hModule, "EventInterface");
                if (EventInterface != nullptr) EventInterface(_Event);
                else std::cout << "ERROR: Unable to find symbol \"EventPlugin\" in library \"" << _Interface->GetInfo().Name << std::endl;
            }else std::cout << "WARNING: Trying to unload a plugin that is already unloaded or has never been loaded." << std::endl;
        }
    }
}