/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "editor.h"

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "raymath.h"

#include <vector>

int main ()
{
	//const int screen_width = 1280 / 2;
	const int screen_width = 1280;
	const int screen_height = 800;
	//const int screen_height = 800 / 2;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screen_width, screen_height, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	DrawText("Hello Raylib", 200, 200, 20, WHITE);

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//Shape* shape = new Circle(Vector2{ 400, 400 });
	Editor editor;
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		editor.Update();

		// drawing
		BeginDrawing();

		ClearBackground(BLACK);

		editor.Draw();

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
