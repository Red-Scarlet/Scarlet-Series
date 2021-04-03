#define ENTRYPOINT
#include <Scarlet.h>
#include <ScarletOpenGL.h>

class SandboxApp : public Scarlet::Application
{
public:
	SandboxApp() 
		: Scarlet::Application()
	{
		this->PushModule<OpenGL::InterfaceGL>();
	}

	~SandboxApp()
	{
	}

};

Scarlet::Application* CreateApplication()
{
	return new SandboxApp();
}