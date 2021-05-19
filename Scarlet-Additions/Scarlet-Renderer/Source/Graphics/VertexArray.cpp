#include "VertexArray.h"

namespace Renderer {

	//Ref<CallbackTable<VertexArray>> VertexArrayCallback = nullptr;

	Ref<VertexArray> VertexArray::Create(const String& _Name)
	{
		if (VertexArrayCallback->Empty()) return nullptr;
		return VertexArrayCallback->Create(_Name);
	}

}