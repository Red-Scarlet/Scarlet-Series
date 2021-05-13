#include "InterfaceModule.h"

namespace ScarletInterface {

    InterfaceModule::InterfaceModule()
    {
    }

    InterfaceModule::InterfaceModule(const String& _Name)
        : m_Name(_Name)
    {
    }

    InterfaceModule::~InterfaceModule()
    {
    }

    void InterfaceModule::SetName(const String& _Name)
    {
        m_Name = _Name;
    }

    const String& InterfaceModule::GetName() const
    {
        return m_Name;
    }

}