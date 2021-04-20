#pragma once

#include "Core/Common.h"
#include "Core/Application.h"
#include "Utilities/Instrumentor.h"

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

    SCARLET_PROFILE_BEGIN_SESSION("Startup", "ScarletProfile-Startup.json");
    auto app = CreateApplication();
    SCARLET_PROFILE_END_SESSION();

    SCARLET_PROFILE_BEGIN_SESSION("Runtime", "ScarletProfile-Runtime.json");
    app->Run();
    SCARLET_PROFILE_END_SESSION();

    SCARLET_PROFILE_BEGIN_SESSION("Shutdown", "ScarletProfile-Shutdown.json");
    app->Stop();
    SCARLET_PROFILE_END_SESSION();

    Scarlet::Log::Shutdown();
    delete app;
}