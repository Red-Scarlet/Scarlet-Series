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
        virtual ~InterfaceModule();

        virtual void OnGlobal(Event& _Event) = 0;
        virtual void OnLocal(Event& _Event) = 0;

        void SetName(const String& _Name);
        const String& GetName() const;

        void SetSignature(const ModuleSignature& _Signature);
        const ModuleSignature& GetSignature() const;

        Set<Interface> m_InterfaceSet;

    private:
        String m_Name;
        Interface m_Interface;
        ModuleSignature m_Signature;

    };

}