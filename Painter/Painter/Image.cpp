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
	//double sum_test = 0;

	//for (int i = 0; i < res.rows; i += 1) {
	//	for (int j = 0; j < res.cols; j += 1) {
	//		//std::cout << res.at<cv::Vec3b>(i, j) << std::endl;
	//		sum_test += res.at<cv::Vec3b>(i, j)[0];
	//		sum_test += res.at<cv::Vec3b>(i, j)[1];
	//		sum_test += res.at<cv::Vec3b>(i, j)[2];
	//		if (sum_test <= 0) {
	//			std::cout << "booooooooooom" << std::endl;
	//		}
	//	}
	//}
	//std::cout << sum << std::endl;
	return sum[0] + sum[1] + sum[2];
}
