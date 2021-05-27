#define ENTRYPOINT
#include <Scarlet.h>

//	ENTRYPOINT APPLICATION
//	Utilize this to write code directly into the engine-
//	-by passing the Shared Lib (DLL, SO) interface.
class EditorApp : public Scarlet::Application
{
public:
	EditorApp() : Scarlet::Application()
	{
	}

	~EditorApp()
	{
	}

};

Scarlet::Application* CreateApplication()
{
	return new EditorApp();
}