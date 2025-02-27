#pragma comment(lib,"raylibdll.lib")
#pragma comment(lib,"Winmm.lib")

#include <iostream>
#include <raylib-cpp.hpp>

int main()
{
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 450;

	raylib::Window window(screenWidth, screenHeight, "raylib-cpp: display image");

	raylib::Image image("resources/player.png", 0, 0, UNCOMPRESSED_R8G8B8A8); // Load image data into CPU memory (RAM)
	raylib::Texture2D texture(image); // Create texture from image data

	SetTargetFPS(60);

	// Main game loop
	while (!window.ShouldClose()) // Detect window close button or ESC key
	{
		// Update
		// TODO: Update your variables here

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		texture.Draw(10, 10, WHITE);


		EndDrawing();
	}

	// De-Initialization
	texture.Unload(); // Texture unloading

	return 0;
}
