
#include <nim.h>


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

std::string fullpath(std::string filepath)
{
	if (std::filesystem::exists(filepath))
	{
		return std::move(filepath);
	}
	std::stringstream abpath;
	abpath << NIM_DIR << "/" << filepath;
	if(std::filesystem::exists(abpath.str()))
		return std::move(abpath.str());
	return std::string();
}


ImageData* imageRead(std::string imagepath)
{
	if (imagepath.empty())
	{
		std::cout << "The File Doesn't Exist\n";
		return nullptr;
	}
	std::string dir, name, format;
	char c;
	int j = imagepath.size() - 1;

	for (int i = j; i >= 0; i--)
	{
		if (imagepath[i] == '.' && i < j)
		{
			format = imagepath.substr(i);
			j = i -1;
			break;
		}
	}
	if (format.empty())
	{
		printf("Unknown Image Type\n");
		return nullptr;
	}
	IMAGE_TYPE type;
	if (format == ".jpg")
		type = JPG;
	else if (format == ".png")
		type = PNG;
	else
	{
		printf("Unknown Image Format\n");
		return nullptr;
	}
	for (int i = j; i >= 0; i--)
	{
		if (imagepath[i] == '/')
		{
			name = imagepath.substr(i + 1, j - i);
			j = i;
			break;
		}
	}
	if (name.empty())
		return nullptr;

	dir = imagepath.substr(0, j);

	if (dir.empty())
		return nullptr;

	int width, height, channel;
	unsigned char* image = stbi_load(imagepath.c_str(), &width, &height, &channel, 0);
	//std::cout << "Width = " << width << " Height = " << height << " Channel = " << channel << "\n";

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

	//std::cout << "Original Image Size = " << arr.size() * sizeof(uint8_t) << " Bytes" << std::endl;
	stbi_image_free(image);

	return new ImageData(dir, name, type, width, height, channel, arr);
}

void imageWrite(ImageData* image, IMAGE_TYPE format)
{
	if (!image)
	{
		printf("The Image data is NULL\n");
		return;
	}
	
	if (format == JPG)
	{
		if (!stbi_write_jpg(image->getpath().c_str(), image->getwidth(), image->getheight(), image->getchannels(), image->getData(), 90))
			printf("Unable to write Image\n");
	}
	else if(format ==  PNG)
	{
		if (!stbi_write_png(image->getpath().c_str(), image->getwidth(), image->getheight(), image->getchannels(), image->getData(), image->getwidth() * image->getchannels()))
			printf("Unable to Write Image\n");
	}
	else
	{
		printf("Unknown format. Unable to write file\n");
		return;
	}
	return;
}


// ImageData
ImageData::ImageData(std::string imagedir, std::string imagename, IMAGE_TYPE imageformat, int width, int height, int channel, std::vector<uint8_t> pixels)
	:	image_dir(imagedir), image_name(imagename), image_format(imageformat), image_width(width), image_height(height), channels(channel), image_pixels(pixels)
{ }

ImageData::ImageData(ImageData& other)
	: image_dir(other.image_dir), image_name(other.image_name), image_format(other.image_format), image_width(other.image_width), image_height(other.image_height), channels(other.channels), image_pixels(std::move(other.image_pixels))
{ }

ImageData::~ImageData()
{

}

ImageData* ImageData::grayscale()
{
	if (channels == 1)
		return this;
	if (channels == 3)
	{
		std::string s = image_name + "_grayscale";
		ImageData* temp = new ImageData(image_dir, s, image_format, this->image_width, this->image_height, 1, std::vector<uint8_t>(this->image_pixels.size() / 3));

		for (int y = 0; y < image_height; y++)
		{
			for (int x = 0; x < image_width; x++)
			{
				int index = y * image_height + x;
				temp->image_pixels[index] = (0.21 * image_pixels[index * channels]) + (0.72 * image_pixels[index * channels + 1]) + (0.07 * image_pixels[index * channels + 2]);
			}
		}
		
		return temp;
	}
	else
	{
		std::printf("There are Errors in Image format\n");
		return this;
	}
}

std::string ImageData::getextension()
{
	if (this->image_format == PNG)
		return ".png";
	else if (this->image_format == JPG)
		return ".jpg";
	else
		return ".txt";
}