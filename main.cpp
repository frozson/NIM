
#include <nim.h>
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <external/stb_image.h>

std::string fullpath(const char * file)
{
	std::stringstream abpath;
	abpath << NIM_DIR << "/" << file;
	return std::move(abpath.str());
}

// Please pass on the absolute path in case it fails to load them.
// Note: Use fullpath() to get the absolute path.
int show(const char * file)
{
	std::fstream f(file);
	if (!f.good())
	{
		std::cout << "Wrong File Path or FILE is NOT GOOD\n";
		return 1;
	}

	const int screenWidth = 1280;
	const int screenHeight = 720;
	InitWindow(screenWidth, screenHeight, "Raylib");
	SetTargetFPS(30);

	Texture2D texture = LoadTexture(file);
	Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
	Vector2 aspect = { (float)screenWidth / source.width, (float)screenHeight / source.height };
	float scale_factor = std::min(aspect.x, aspect.y);
	Rectangle dest = { 0.0f, 0.0f, source.width * scale_factor , source.height * scale_factor };
	dest.x = ((float)screenWidth - dest.width) / 2;
	dest.y = ((float)screenHeight - dest.height) / 2;
	Vector2 origin = { 0.0f , 0.0f };
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
		//DrawTexture(texture, (int)dest.x, (int)dest.y, WHITE);
		EndDrawing();
	}
	UnloadTexture(texture);
	CloseWindow();
	return 0;
}

int main()
{
	std::string abspath = fullpath("sample assets/Frozson.png");
	
	int width, height, channel;
	unsigned char* image = stbi_load(abspath.c_str(), &width, &height, &channel, 0);
	std::cout << "Width = " << width << " Height = " << height << " Channel = " << channel << "\n";

	//show(abspath.c_str());

	std::vector<uint8_t> arr(width * height * channel);
	int index;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			index = (y * height + x) * channel;
			arr[index] = (uint8_t)image[index];
			arr[index + 1] = (uint8_t)image[index + 1];
			arr[index + 2] = (uint8_t)image[index + 2];
		}
	}

	std::cout << "Original Image Size = " << arr.size() * sizeof(uint8_t) << " Bytes" << std::endl;
	stbi_image_free(image);
	show(abspath.c_str());

	return 0;
}