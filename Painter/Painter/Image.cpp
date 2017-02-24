#include "Image.h"

Image::Image(const std::string &fileName)
{
	image = cv::imread(fileName);
	image.convertTo(image, CV_8UC3);
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
	cv::Mat tmp;
	image.convertTo(tmp, CV_8UC3);
	cv::imshow(windowName, tmp);
}

void Image::Write(const std::string &fileName)
{
	cv::Mat tmp;
	image.convertTo(tmp, CV_8UC3);
	cv::imwrite(fileName, tmp);
}

void Image::Read(const std::string &fileName)
{
	image = cv::imread(fileName);
	image.convertTo(image, CV_8UC3);
}

// fitness function
int Image::CalcDifference(const Image & rhs) const
{
	cv::Mat res;
	cv::absdiff(image, rhs.image, res);
	
	cv::Scalar sum = cv::sum(res);

	//std::cout << sum << std::endl;
	return sum[0] + sum[1] + sum[2];
}
