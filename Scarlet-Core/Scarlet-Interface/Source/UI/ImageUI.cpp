#include "ImageUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> ImageUI::s_Callback = CallbackTable::Create();

	void ImageUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<ImageUI> ImageUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<ImageUI>(_Name);
	}

}