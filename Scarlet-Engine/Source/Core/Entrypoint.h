#pragma once

#include "Core/Common.h"
#include "Core/Application.h"

extern Scarlet::Application* CreateApplication();

#ifdef SCARLET_DIST
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
	Scarlet::Log::Init();
	SCARLET_CORE_WARN("Initialized Log!");
	SCARLET_CORE_WARN("Entrypoint Initialized!");

	auto app = CreateApplication();

	app->Run();
	app->Stop();

	Scarlet::Log::Shutdown();
	delete app;
}