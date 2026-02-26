
#include <nim.h>
//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_FAILURE_USERMSG
//#include <stb_image.h>

std::string fullpath(const char* file)
{
	std::stringstream abpath;
	abpath << NIM_DIR << "/" << file;
	return std::move(abpath.str());
}