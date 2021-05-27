#pragma once

#include "Core/Common.h"
#include <ScarletInterface.h>

namespace Scarlet {
    
    using namespace ScarletInterface;

    class InterfaceHandlerPimpl;

    class InterfaceHandler
    {
    public:
        static InterfaceHandler& Instance();

        InterfaceModule* LoadInterface(const String& _Path);
        void UnloadInterface(InterfaceModule* _Interface);
        void EventInterface(Event& _Event, InterfaceModule* _Interface);

    private:
        InterfaceHandler();
        ~InterfaceHandler();

        InterfaceHandlerPimpl* m_Implementation;
    };

}