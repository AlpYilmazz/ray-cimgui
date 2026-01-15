// #include "justengine.h"
#include "raylib.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

#include "raycimgui.h"

// DPI scaling functions
float ScaleToDPIF(float value)
{
	return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value)
{
    return (int)(GetWindowScaleDPI().x * value);
}

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 800;

	// do not set the FLAG_WINDOW_HIGHDPI flag, that scales a low res framebuffer up to the native resolution.
	// use the native resolution and scale your geometry.
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - Docking");
	SetTargetFPS(144);
	rligSetup(true);

	bool run = true;

	bool showDemoWindow = true;

	// if the linked ImGui has docking, enable it.
	// this will only be true if you use the docking branch of ImGui.
#ifdef IMGUI_HAS_DOCK
	igGetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

	// Main game loop
	while (!WindowShouldClose() && run)    // Detect window close button or ESC key, or a quit from the menu
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// draw something to the raylib window below the GUI.
		DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenHeight() * 0.45f, DARKGREEN);

		// start ImGui content
		rligBegin();

        ImGuiIO* io = igGetIO_Nil();
        io->WantCaptureMouse;
        io->WantCaptureKeyboard;

		// if you want windows to dock to the viewport, call this.
#ifdef IMGUI_HAS_DOCK
		igDockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
#endif

		// show a simple menu bar
		if (igBeginMainMenuBar())
		{
			if (igBeginMenu("File", true))
			{
				if (igMenuItem_Bool("Quit", NULL, false, true))
					run = false;

				igEndMenu();
            }

			if (igBeginMenu("Window", true))
            {
                if (igMenuItem_Bool("Demo Window", NULL, showDemoWindow, true))
					showDemoWindow = !showDemoWindow;

                igEndMenu();
            }
			igEndMainMenuBar();
		}

		// show some windows
	
		if (showDemoWindow)
			igShowDemoWindow(&showDemoWindow);

		if (igBegin("Test Window", 0, 0))
		{
			igTextUnformatted("Another window", 0);
		}
		igEnd();

		// end ImGui Content
		rligEnd();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	rligShutdown();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}