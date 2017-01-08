#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

int main()
{
	cv::Mat img;
	img = cv::imread("test.jpg", 1);
	cv::imshow("test", img);
	cv::waitKey(0);

	return 0;
}
