#pragma once;

#include "Core/Common.h"
#include "Core/InterfaceModule.h"
#include "Events/Event.h"

#define INTERFACE_ENTRYPOINT(x)                                             \
namespace ScarletInterface {                                                \
                                                                            \
    extern "C" SCARLET_INTERFACE_API InterfaceModule* CreateInterface();    \
    extern "C" SCARLET_INTERFACE_API void DestroyInterface();               \
    extern "C" SCARLET_INTERFACE_API void EventInterface(Event& _Event);    \
                                                                            \
    x* g_x = nullptr;                                                       \
                                                                            \
    extern "C" SCARLET_INTERFACE_API InterfaceModule* CreateInterface()     \
    {                                                                       \
        g_x = new x();                                                      \
        return g_x;                                                         \
    }                                                                       \
                                                                            \
    extern "C" SCARLET_INTERFACE_API void DestroyInterface()                \
    {                                                                       \
        delete g_x;                                                         \
        g_x = nullptr;                                                      \
    }                                                                       \
                                                                            \
    extern "C" SCARLET_INTERFACE_API void EventInterface(Event& _Event)     \
    {                                                                       \
        g_x->OnGlobal(_Event);                                              \
    }                                                                       \
                                                                            \
}                                       