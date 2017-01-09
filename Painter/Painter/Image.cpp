#include "Image.h"

Image::Image(const std::string &fileName)
{
	image = cv::imread(fileName);
}

int Image::getw()
{
	return image.cols;
}

int Image::geth()
{
	return image.rows;
}

void Image::Show(const std::string &windowName)
{
	cv::imshow(windowName, image);
}

void Image::Write(const std::string &fileName)
{
	cv::imwrite(fileName, image);
}

void Image::Read(const std::string &fileName)
{
	image = cv::imread(fileName);
}

// fitness function
int Image::CalcDifference(const Image & rhs) const
{
	cv::Mat res;
	cv::absdiff(this->image, rhs.image, res);

	cv::Scalar sum = cv::sum(res);
	return sum[0] + sum[1] + sum[3];
}
