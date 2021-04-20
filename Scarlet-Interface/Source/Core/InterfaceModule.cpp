#include "InterfaceModule.h"

namespace ScarletInterface {

    InterfaceModule::InterfaceModule()
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

    void InterfaceModule::SetSignature(const ModuleSignature& _Signature)
    {
        m_Signature = _Signature;
    }

    const ModuleSignature& InterfaceModule::GetSignature() const
    {
        return m_Signature;
    }

}