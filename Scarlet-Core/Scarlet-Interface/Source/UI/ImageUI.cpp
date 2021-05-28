#include "ImageUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<ImageUI>> ImageUI::s_Callback = CallbackTable<ImageUI>::Create();

	void ImageUI::PushWrapper(const CallbackWrapper<ImageUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<ImageUI> ImageUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}