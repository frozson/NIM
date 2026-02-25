#pragma once
// NIM.h : Include file for standard system include files,
// or project specific include files.

/*
	NIM is acronym of Neural Imaging Module
	NIM is made for processing image into neural network and let it produce the image data on runtime
	The goal is maintain a clear and non-pixalated or bluried image when zoomed in
*/


#include <iostream>


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
