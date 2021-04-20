#define ENTRYPOINT
#include <Scarlet.h>

//	ENTRYPOINT APPLICATION
//	Utilize this to write code directly into the engine-
//	-by passing the SharedLib (DLL, SO) interface.
class SandboxApp : public Scarlet::Application
{
public:
	SandboxApp() : Scarlet::Application()
	{
	}

	~SandboxApp()
	{
	}

};

Scarlet::Application* CreateApplication()
{
	return new SandboxApp();
}