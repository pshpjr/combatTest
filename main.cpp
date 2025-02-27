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

	raylib::Image image("resources/player.png"); // Load image data into CPU memory (RAM)
	raylib::Texture2D texture(image); // Create texture from image data

	SetTargetFPS(60);

	// Main game loop
	while (!window.ShouldClose()) // Detect window close button or ESC key
	{
		// Update
		// TODO: Update your variables here
		raylib::Image image2 = texture.GetTextureData();
		image2.ColorTint(RED);
		texture.Unload();
		texture = raylib::Texture2D(image2);

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		// texture.Draw(10, 10, WHITE); // Original draw call
		Vector2 origin{ (float)texture.GetWidth() / 2, (float)texture.GetHeight() / 2 };
		Rectangle sourceRec{ 0.0f, 0.0f, (float)texture.GetWidth(), (float)texture.GetHeight() };
		Vector2 position{ 100, 100 };
		DrawTexturePro(texture, sourceRec, Rectangle{ position.x, position.y, texture.GetWidth() * 2, texture.GetHeight() * 2 }, Vector2{ (float)texture.GetWidth(), (float)texture.GetHeight() }, 45.0f, WHITE);

		EndDrawing();
	}

	// De-Initialization
	texture.Unload(); // Texture unloading

	return 0;
}
