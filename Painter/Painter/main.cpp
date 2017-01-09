#include <iostream>
#include <cstdlib>
#include <ctime>
#include <opencv2/opencv.hpp>

int main()
{
	srand(time(NULL));

	//GA mona;
	//if (!mona.initial("monalisa.jpg")) return 1;
	//mona.Start();
	////    mona.start2_4();
	////mona.generateInitSoluction();

	//cvWaitKey(0);

	cv::Mat img;
	img = cv::imread("test.jpg", 1);

	cv::Mat test(img.rows, img.cols, CV_32SC3, cv::Scalar(10, 10, 10)), test2;
	img.convertTo(img, CV_32SC3);
	test.convertTo(test, CV_32SC3);
	cv::subtract(img, test, test2);

	cv::Mat res;
	cv::absdiff(img, test2, res);

	cv::Scalar sum = cv::sum(res);
	for (int i = 0; i < 4; i += 1)
		std::cout << (int)sum.val[i] << std::endl;
	
	
	cv::imshow("test", img);

	cv::waitKey(0);

	return 0;
}
