#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <filesystem>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

inline decltype(auto) convertHex(unsigned short MSB, unsigned short LSB)
{
	return ((MSB << 8)) | (0x00ff & LSB);
}

int main(void)
{
	namespace fs = std::experimental::filesystem;
	constexpr int SRTM_VERSION = 1201;
	char *memblock = new char[2];
	unsigned short elevation[SRTM_VERSION][SRTM_VERSION];

	constexpr const char *targetDir = "./SRTM_image/";
	fs::create_directories(targetDir);

	for (const auto& p : fs::directory_iterator("./SRTM_dataset"))
	{
		fstream hgtFile(p.path().string(), ios::in | ios::binary | ios::ate);
		hgtFile.seekg(0, ios::beg);

		for (int r = 0; r < SRTM_VERSION; r++)
		for (int c = 0; c < SRTM_VERSION; c++)
		{
			hgtFile.read(memblock, 2);
			elevation[r][c] = convertHex(memblock[0], memblock[1]);
		}

		Mat src(Size(SRTM_VERSION, SRTM_VERSION), CV_16UC1, (void*)&elevation[0][0]);
		const std::string targetPath = targetDir + p.path().stem().string() + std::string(".png");
		imwrite(targetPath, src);
	}


	return 0;
}