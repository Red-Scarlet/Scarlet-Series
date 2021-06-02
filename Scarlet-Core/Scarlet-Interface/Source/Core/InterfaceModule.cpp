#include "InterfaceModule.h"

#include "Components/CallbackComponent.h"
#include "Events/InterfaceEvent.h"
#include "UI/ButtonUI.h"
#include "UI/CheckboxUI.h"
#include "UI/ImageUI.h"
#include "UI/LabelUI.h"
#include "UI/PanelUI.h"
#include "UI/ScrollablePanelUI.h"
#include "UI/SliderUI.h"
#include "UI/TextboxUI.h"

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

    void InterfaceModule::SetCallbacks(Event& _Event)
    {
        if (m_SetCallbacks == false)
        {
            CallbackComponent* component = {};
            _Event.Push(new ComponentComputeEvent(this))->Retrieve<CallbackComponent>(&component);
            _Event.Proceed(_Event);

            for (auto pair : component->CallbackTables)
            {
                if(std::get<std::type_index>(pair) == typeid(ButtonUI))
                    ButtonUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(CheckboxUI))
                    CheckboxUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(ImageUI))
                    ImageUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(LabelUI))
                    LabelUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(PanelUI))
                    PanelUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(ScrollablePanelUI))
                    ScrollablePanelUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(SliderUI))
                    SliderUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
                if (std::get<std::type_index>(pair) == typeid(TextboxUI))
                    TextboxUI::s_Callback = std::get<Ref<CallbackTable>>(pair);
            }

            m_SetCallbacks = true;
        }

    }

}