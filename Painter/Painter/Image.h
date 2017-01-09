#pragma once

#include <string>
#include <opencv2/opencv.hpp>

class Image
{
private:
	cv::Mat image;

public:
	Image() {}
	Image(const std::string &fileName);

	int getw();
	int geth();
	void Show(const std::string &windowName);
	void Write(const std::string &fileName);
	void Read(const std::string &fileName);

	// fitness function
	int CalcDifference(const Image & rhs) const;
};