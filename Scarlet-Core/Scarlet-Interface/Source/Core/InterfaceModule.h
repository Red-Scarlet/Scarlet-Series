#pragma once
#include "Core/Common.h"
#include "Core/InterfaceTypes.h"
#include "Events/Event.h"

namespace ScarletInterface {

    struct SCARLET_INTERFACE_API InterfaceInfo
    {
    public:
        String Name = "Default";
        String Desc = "Description";
        String Version = "1.0.0";
        Vector<String> Requirements;
    };

    class SCARLET_INTERFACE_API InterfaceModule
    {
    public:
        friend class ModuleManager;
        friend class InterfaceRequirementEvent;

    public:
        InterfaceModule(const InterfaceInfo& _Info = InterfaceInfo());
        virtual ~InterfaceModule();

        virtual void OnGlobal(Event& _Event);
        virtual void OnEditor(Event& _Event);

        const InterfaceInfo& GetInfo() const;
        const bool& IsReady() const;

    public: // TODO: Engine side
        void SetCallbacks(Event& _Event);

    public:
        InterfaceInfo m_Info;
        Interface m_Interface;
        Set<Interface> m_Set;
        bool m_ReadyModule = false;
        bool m_SetCallbacks = false;
    };

}