#pragma once
#include "Core/Common.h"
#include "Core/InterfaceTypes.h"
#include "Events/Event.h"

namespace ScarletInterface {

    class SCARLET_INTERFACE_API InterfaceModule
    {
    public:
        friend class ModuleManager;

    public:
        InterfaceModule();
        InterfaceModule(const String& _Name);
        virtual ~InterfaceModule();

        virtual void OnGlobal(Event& _Event) {}
        virtual void OnLocal(Event& _Event) {}

        void SetName(const String& _Name);
        const String& GetName() const;

    public:
        String m_Name;
        Interface m_Interface;
        Set<Interface> m_Set;
        bool m_LoadedModule = false;
    };

}