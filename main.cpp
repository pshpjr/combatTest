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
	image.Resize(100, 50);
	raylib::Texture2D texture(image); // Create texture from image data
	Vector2 lb = {150, 150};
	Vector2 ru = {250, 200};
	SetTargetFPS(60);
	float rotation = 0;
	bool color = true;
	// Main game loop
	while (!window.ShouldClose()) // Detect window close button or ESC key
	{
		// Update
		// TODO: Update your variables here


		// Draw
		BeginDrawing();

		window.ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		//texture.Draw(location.x, location.y, WHITE);
		//location.y += 1;
		//location.x += 1;
		rotation++;
		Vector2 origin = { (float)texture.GetWidth() / 2, (float)texture.GetHeight() / 2 };
		DrawTextureEx(texture, location, rotation, Vector2{1,1}, WHITE);

		EndDrawing();
	}

	// De-Initialization
	texture.Unload(); // Texture unloading

	return 0;
}
