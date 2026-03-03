#pragma once
// NIM.h : Include file for standard system include files,
// or project specific include files.

/*
	NIM is acronym of Neural Imaging Module
	NIM is made for processing image into neural network and let it produce the image data on runtime
	The goal is maintain a clear and non-pixalated or bluried image when zoomed in
*/


#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>

typedef struct
{
	int signature;
	short version;
	int width;
	int height;
	int offset;
} header_nim;

typedef struct
{
	int endian;
	int size;
} meta_nim;

typedef struct
{
	char data[1];
} data_nim;

std::string fullpath(std::string filepath);

typedef enum
{
	PNG,
	JPG
} IMAGE_TYPE;

typedef enum
{
	R8G8B8,
	GRAYSCALE,
} COLOR_FORMAT;

class ImageData
{
public:
	ImageData(std::string imagedir, std::string imagename, IMAGE_TYPE imageformat, int width, int height, int channel, std::vector<uint8_t> pixels);
	ImageData(ImageData& other);

	~ImageData();

	ImageData* grayscale();

	inline std::string getpath() { return std::string(image_dir + "/" + image_name + getextension()); }
	inline std::string getfilename() { return image_name; }
	inline IMAGE_TYPE getformat() { return image_format; }
	inline int getwidth() { return image_width; }
	inline int getheight() { return image_height; }
	inline int getchannels() { return channels; }
	inline int size() { return image_pixels.size(); }
	inline uint8_t* getData() { return image_pixels.data(); }

private:
	std::string getextension();

private:
	std::string image_dir;
	std::string image_name;
	IMAGE_TYPE image_format;
	int image_width;
	int image_height;
	int channels;
	std::vector<uint8_t> image_pixels;
};

// Please pass on the absolute path in case it fails to load them.
// Note: Use fullpath() to get the absolute path.
ImageData* imageRead(std::string imagepath);

void imageWrite(ImageData* image, IMAGE_TYPE format);
