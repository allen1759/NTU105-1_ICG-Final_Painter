#pragma once

#include <string>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "Circle.h"

class Image
{
private:
	cv::Mat image;

public:

	Image() {}
	Image(const std::string &fileName);

	int getw();
	int geth();
	bool isEmpty()
	{
		return image.empty();
	}
	void Show(const std::string &windowName);
	void Write(const std::string &fileName);
	void Read(const std::string &fileName);
	void setTo(cv::Scalar scalar)
	{
		image.setTo(scalar);
	}
	void copyTo(Image &rhs) const
	{
		image.copyTo(rhs.image);
		rhs.image.convertTo(rhs.image, CV_8UC3);
	}

	// fitness function
	int CalcDifference(const Image & rhs) const;

	cv::Vec3f GetColor(int x, int y)
	{
		// asjdfklasjfakds f;alsdk 
		return image.at<cv::Vec3b>(y, x);
	}

	cv::Mat GetSubImage(cv::Rect range)
	{
		cv::Mat ret = image(range);
		return ret;
	}

	void DrawCircle(Circle circle)
	{
		int left =  std::max(circle.x - circle.radius, 0);
		int right = std::min(circle.x + circle.radius, image.cols-1);
		int up = std::max(circle.y - circle.radius, 0);
		int down = std::min(circle.y + circle.radius, image.rows-1);

		cv::Mat image_roi = image(cv::Rect(left, up, right - left, down - up));
		cv::Mat circle_roi;
		image_roi.copyTo(circle_roi);

		// circle index x? y?
		cv::circle(circle_roi, cv::Point(circle.x - left, circle.y - up),
			circle.radius,
			cv::Scalar(circle.B, circle.G, circle.R),
			cv::FILLED);
		
		cv::addWeighted(image_roi, (255 - circle.A) / 255.0, circle_roi, circle.A / 255.0, 0, image_roi);
	}
};