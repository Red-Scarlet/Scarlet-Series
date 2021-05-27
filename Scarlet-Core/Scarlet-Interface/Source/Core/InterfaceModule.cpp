#include "InterfaceModule.h"

namespace ScarletInterface {

    InterfaceModule::InterfaceModule(const InterfaceInfo& _Info)
        : m_Info(_Info)
    {
    }

    InterfaceModule::~InterfaceModule()
    {
    }

    void InterfaceModule::OnGlobal(Event& _Event)
    {
    }

    void InterfaceModule::OnEditor(Event& _Event)
    {
    }

    const InterfaceInfo& InterfaceModule::GetInfo() const
    {
        return m_Info;
    }

    const bool& InterfaceModule::IsReady() const
    {
        return m_ReadyModule;
    }


}